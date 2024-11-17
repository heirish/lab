#include <cstring>
#include <iostream>
#include <systemd/sd-bus.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <chrono>
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std::chrono_literals;
template <typename T>
void  print(T t) {
  std::cout << t << std::endl;
}

template <typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t << ",";
    print(args...);
}

static std::mutex errmutex;
static std::condition_variable errhappen;
static std::atomic_bool us_test_running{true};

void notify_errhappen() {
    std::lock_guard<std::mutex> lock(errmutex);
    errhappen.notify_all();
}

void wait_errhapen() {
    std::unique_lock<std::mutex> lock(errmutex);
    errhappen.wait(lock);
}

void sd_bus_test() {
	sd_bus* bus;
    int ret = sd_bus_open_system((&bus));
    if (ret != 0) {
        fprintf(stderr, "sd_bus_default failed, errno:%d, msg:%s\n", ret, strerror(0-ret));
        return;
    }
    fprintf(stdout, "wait for exec sd_bus_request_name, press any key to continue....\n");
    //wait_errhapen();
    getchar();
    //ret = sd_bus_request_name(bus, "org.example.com.TestService", 0);
    //if (ret < 0) {
    //    fprintf(stderr, "sd_bus_request_name failed, errno:%d, msg:%s\n", ret, strerror(0-ret));
    //    goto error;
    //}
    //fprintf(stdout, "sd_bus_request_name succeed.\n");
    //us_test_running = false;
    //pause();
    sd_bus_close(bus);

error:
    us_test_running = false;
    sd_bus_close(bus);
}

void usocket_server_test(const char* socket_name) {
    assert(socket_name);
    unlink(socket_name);
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket failed.");
        return;
    }

    struct sockaddr_un addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_name, sizeof(addr.sun_path) -1);

    int ret = bind(fd, (const struct sockaddr*)&addr, sizeof(addr));
    if (ret == -1) {
        perror("bind failed.");
        close(fd);
        return;
    }

    ret = listen(fd, 20);
    if (ret == -1) {
        perror("listen failed.");
        close(fd);
        return;
    }

    int connections = 0;
    while(us_test_running) {
        int accepted_fd = accept(fd, NULL, NULL);
        if (accepted_fd == -1) {
            perror("accept failed.");
            continue;
        }

        std::string msg = "hello";
        ret = write(accepted_fd, msg.c_str(), msg.length());
        if (ret == -1) {
            perror("write error.");
        }
        close(accepted_fd);
        fprintf(stdout, "closed client socket connection:%d\n", connections++);
    }
    close(fd);
    unlink(socket_name);
}

void usocket_client_test(const char* socket_name) {
    assert(socket_name);
    while(us_test_running) {
        int fd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd == -1) {
            perror("socket failed.");
            notify_errhappen();
            continue;
        }

        struct sockaddr_un addr;
        memset(&addr, 0x00, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, socket_name,sizeof(addr.sun_path)-1);

        int ret = connect(fd, (const struct sockaddr*)&addr, sizeof(addr));
        if (ret == -1) {
            notify_errhappen();
            perror("connect failed.");
            //bug: not close fd;
            //continue;
        }

        //char buff[1024];
        //ret = read(fd, buff, sizeof(buff));
        //if (ret == -1)
        //{
        //    perror("read error.");
        //} else {
        //    fprintf(stdout, "received [%s] from unix socket server.", buff);
        //}

        //close(fd);
        std::this_thread::sleep_for(500ms);
    }
}

int main(int argc, char *argv[]) {
    std::cout << "hello raspberry pi" << std::endl;
    print(2,3,3.5f, "raspberry pi", true);

    //std::vector<std::thread> threads;
    //const char* socket_name = "ch1";
    //std::thread us_server = std::thread(usocket_server_test, socket_name);
    //threads.push_back(std::move(us_server));
    //for(int i=0; i<100; i++) {
    //    std::thread us_client = std::thread(usocket_client_test, socket_name);
    //    threads.push_back(std::move(us_client));
    //}

    fprintf(stdout, "start sd_bus_test\n");
   sd_bus_test();
   // std::thread bus_thread = std::thread(sd_bus_test);
    //threads.push_back(std::move(bus_thread));
    //if (bus_thread.joinable()) {
    //    bus_thread.join();
    //}

    //for(auto& t:threads) {
    //    if (t.joinable()) t.join();
    //}
}