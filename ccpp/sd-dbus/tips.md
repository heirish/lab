- check unix socket peer:
```
heirish@raspberrypi:~$ sudo lsof +E -p 15641 | grep bus
dbus-daem   751 messagebus   22u     unix 0xffff32bd278e5400      0t0 4918056 /run/dbus/system_bus_socket type=STREAM ->INO=4921709 15641,main,105u (CONNECTED)
main      15641       root  cwd       DIR              179,2     4096  261502 /home/heirish/myproj/ccpp/sd-dbus
main      15641       root  txt       REG              179,2   271736  267225 /home/heirish/myproj/ccpp/sd-dbus/build/main
main      15641       root  105u     unix 0xffff32bd278e5800      0t0 4921709 @82d71e71b96bafb7/bus/main/system type=STREAM ->INO=4918056 751,dbus-daem,22u (CONNECTED)


heirish@raspberrypi:~$ sudo ss -a -p | grep 4921709 | more
u_str ESTAB  0      0                                              /run/dbus/system_bus_socket 4918056                         * 4921709 users:(("dbus-daemon",pid=751,fd=22))

u_str ESTAB  0      0                                        @82d71e71b96bafb7/bus/main/system 4921709                         * 4918056 users:(("main",pid=15641,fd=105))
```
-call stack of sd_bus_open_syste, sd_bus_request_name
```
write(1, "start sd_bus_test\n", 18start sd_bus_test
)     = 18
//sd_bus_open_system
getrandom("\xf8\x4d\xc6\xbf\x85\x34\xb5\xe9", 8, GRND_INSECURE) = 8
futex(0xffffadf310d0, FUTEX_WAKE_PRIVATE, 2147483647) = 0
getpid()                                = 17393
socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK, 0) = 3
prctl(PR_GET_NAME, "main")              = 0
getrandom("\x29\x44\x50\x51\xa9\x41\xd2\xd3", 8, GRND_INSECURE) = 8
bind(3, {sa_family=AF_UNIX, sun_path=@"d3d241a951504429/bus/main/system"}, 35) = 0
getsockopt(3, SOL_SOCKET, SO_RCVBUF, [212992], [4]) = 0
setsockopt(3, SOL_SOCKET, SO_RCVBUF, [8388608], 4) = 0
getsockopt(3, SOL_SOCKET, SO_RCVBUF, [425984], [4]) = 0
setsockopt(3, SOL_SOCKET, SO_RCVBUFFORCE, [8388608], 4) = 0
getsockopt(3, SOL_SOCKET, SO_SNDBUF, [212992], [4]) = 0
setsockopt(3, SOL_SOCKET, SO_SNDBUF, [8388608], 4) = 0
getsockopt(3, SOL_SOCKET, SO_SNDBUF, [425984], [4]) = 0
setsockopt(3, SOL_SOCKET, SO_SNDBUFFORCE, [8388608], 4) = 0
connect(3, {sa_family=AF_UNIX, sun_path="/run/dbus/system_bus_socket"}, 30) = 0
getsockopt(3, SOL_SOCKET, SO_PEERCRED, {pid=1, uid=0, gid=0}, [12]) = 0
getsockopt(3, SOL_SOCKET, SO_PEERSEC, "unconfined", [64 => 10]) = 0
openat(AT_FDCWD, "/proc/sys/kernel/ngroups_max", O_RDONLY|O_CLOEXEC) = 4
read(4, "65536\n", 31)                  = 6
close(4)                                = 0
mmap(NULL, 266240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xffffadcdf000
getsockopt(3, SOL_SOCKET, SO_PEERGROUPS, 0xffffadcdf010, [262144 => 0]) = 0
getsockopt(3, SOL_SOCKET, SO_PEERPIDFD, [4], [4]) = 0
getpeername(3, {sa_family=AF_UNIX, sun_path="/run/dbus/system_bus_socket"}, [127 => 30]) = 0
fstat(3, {st_mode=S_IFSOCK|0777, st_size=0, ...}) = 0
getsockopt(3, SOL_SOCKET, SO_ACCEPTCONN, [0], [4]) = 0
getsockname(3, {sa_family=AF_UNIX, sun_path=@"d3d241a951504429/bus/main/system"}, [128 => 35]) = 0
sendmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="\0AUTH EXTERNAL\r\nDATA\r\n", iov_len=22}, {iov_base="NEGOTIATE_UNIX_FD\r\n", iov_len=19}, {iov_base="BEGIN\r\n", iov_len=7}], msg_iovlen=3, msg_controllen=0, msg_flags=0}, MSG_DONTWAIT|MSG_NOSIGNAL) = 48
getrandom("\x0a\x71\xe7\x34\x93\x06\x06\xdc\x54\xa7\x70\xf4\x45\x72\x8d\x14", 16, GRND_INSECURE) = 16
futex(0xffffadf31d38, FUTEX_WAKE_PRIVATE, 2147483647) = 0
write(1, "wait for exec sd_bus_request_name, press any key to continue....\n", 65wait for exec sd_bus_request_name, press any key to continue....
) = 65
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x1), ...}) = 0
read(0, 
"\n", 1024)                     = 1
//sd_bus_request_name
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="DATA\r\nOK 1a177f0e663a5594bd996b4c6738c3f5\r\nAGREE_UNIX_FD\r\n", iov_len=256}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 58
sendmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\1\0\1\0\0\0\0\1\0\0\0m\0\0\0\1\1o\0\25\0\0\0/org/freedesktop/DBus\0\0\0\3\1s\0\5\0\0\0Hello\0\0\0\2\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\6\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0", iov_len=128}], msg_iovlen=1, msg_controllen=0, msg_flags=0}, MSG_DONTWAIT|MSG_NOSIGNAL) = 128
recvmsg(3, {msg_namelen=0}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = -1 EAGAIN (Resource temporarily unavailable)
ppoll([{fd=3, events=POLLIN}], 1, {tv_sec=24, tv_nsec=997486000}, NULL, 8) = 1 ([{fd=3, revents=POLLIN}], left {tv_sec=24, tv_nsec=997470963})
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\2\1\1\n\0\0\0\1\0\0\0=\0\0\0\6\1s\0\5\0\0\0", iov_len=24}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 24
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base=":1.54\0\0\0\5\1u\0\1\0\0\0\10\1g\0\1s\0\0\7\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\5\0\0\0:1.54\0", iov_len=66}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 66
sendmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\1\0\1$\0\0\0\2\0\0\0\200\0\0\0\1\1o\0\25\0\0\0/org/freedesktop/DBus\0\0\0\3\1s\0\v\0\0\0RequestName\0\0\0\0\0\2\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\6\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\10\1g\0\2su\0", iov_len=144}, {iov_base="\33\0\0\0org.example.com.TestService\0\4\0\0\0", iov_len=36}], msg_iovlen=2, msg_controllen=0, msg_flags=0}, MSG_DONTWAIT|MSG_NOSIGNAL) = 180
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\4\1\1\n\0\0\0\2\0\0\0\215\0\0\0\1\1o\0\25\0\0\0", iov_len=24}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 24
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="/org/freedesktop/DBus\0\0\0\2\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\3\1s\0\f\0\0\0NameAcquired\0\0\0\0\6\1s\0\5\0\0\0:1.54\0\0\0\10\1g\0\1s\0\0\7\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\5\0\0\0:1.54\0", iov_len=146}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 146
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\4\1\1 \0\0\0\3\0\0\0\215\0\0\0\1\1o\0\25\0\0\0", iov_len=24}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 24
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="/org/freedesktop/DBus\0\0\0\2\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\3\1s\0\f\0\0\0NameAcquired\0\0\0\0\6\1s\0\5\0\0\0:1.54\0\0\0\10\1g\0\1s\0\0\7\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\33\0\0\0org.example.com.TestService\0", iov_len=168}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 168
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base="l\2\1\1\4\0\0\0\4\0\0\0=\0\0\0\6\1s\0\5\0\0\0", iov_len=24}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 24
recvmsg(3, {msg_name=NULL, msg_namelen=0, msg_iov=[{iov_base=":1.54\0\0\0\5\1u\0\2\0\0\0\10\1g\0\1u\0\0\7\1s\0\24\0\0\0org.freedesktop.DBus\0\0\0\0\1\0\0\0", iov_len=60}], msg_iovlen=1, msg_controllen=0, msg_flags=MSG_CMSG_CLOEXEC}, MSG_DONTWAIT|MSG_CMSG_CLOEXEC) = 60
write(1, "sd_bus_request_name succeed.\n", 29sd_bus_request_name succeed.
) = 29
```

- unix socket: systemd only listening on /run/dbus/system_bus_socket, and pass listen fd to dbus-daemon(dbus-daemon get it via sd_listen_fds), dbus-daemon accept connection to that listen if.
```
/**
 * Acquires one or more sockets passed in from systemd. The sockets
 * are set to be nonblocking.
 *
 * This will set FD_CLOEXEC for the sockets returned.
 *
 * @param fds the file descriptors
 * @param error return location for errors
 * @returns the number of file descriptors
 */
int
_dbus_listen_systemd_sockets (DBusSocket **fds,
                              DBusError   *error)
{
```
```
heirish@raspberrypi:~$ sudo lsof +E -p 1 | grep bus_socket
systemd      1             root   89u     unix 0xffff32bd045a2000      0t0       7890 /run/dbus/system_bus_socket type=STREAM (LISTEN)
dbus-daem  751       messagebus   15u     unix 0xffff32bd045af800      0t0       9995 /run/dbus/system_bus_socket type=STREAM ->INO=8010 1,systemd,129u (CONNECTED)
heirish@raspberrypi:~$ sudo lsof +E -p 1 | grep 8010
systemd      1             root  129u     unix 0xffff32bd014f4800      0t0       8010 @7902ea309f07ef8f/bus/systemd/bus-api-system type=STREAM ->INO=9995 751,dbus-daem,15u (CONNECTED)
dbus-daem  751       messagebus   15u     unix 0xffff32bd045af800      0t0       9995 /run/dbus/system_bus_socket type=STREAM ->INO=8010 1,systemd,129u (CONNECTED)
```
- dbus
```
heirish@raspberrypi:~$ cat /etc/dbus-1/system.d/org.example.com.TestService.conf
<!DOCTYPE busconfig PUBLIC
 "-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN"
 "http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>

  <policy user="root">
    <allow own="org.example.com.TestService"/>
  </policy>

  <policy context="default">
    <allow send_destination="org.freedesktop.DBus" />
  </policy>

</busconfig>
```
```
busctl list
busctl tree
dbus-send --system --dest=org.freedesktop.DBus   --type=method_call            --print-reply                 /org/freedesktop/DBus         org.freedesktop.DBus.Introspectable.Introspect
busctl introspect org.freedesktop.DBus /org/freedesktop/DBus
 sudo strace  -s9999 busctl --expect-reply=true call org.freedesktop.DBus /org/freedesktop/DBus org.freedesktop.DBus RequestName su "org.example.com.TestService" 0
 busctl monitor(或dbus-monitor --system) ->requestname時調用了hello/RequestName方法，然后NameOwnerChanged和NameAcquired都是signal
 sudo dbus-send --system             --dest=org.freedesktop.DBus   --type=method_call            --print-reply                 /org/freedesktop/DBus         org.freedesktop.DBus.RequestName string:"org.example.com.TestService" uint32:0
```
```
heirish@raspberrypi:~$ sudo dbus-monitor --system
signal time=1731835919.308494 sender=org.freedesktop.DBus -> destination=:1.91 serial=2 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameAcquired
   string ":1.91"
signal time=1731835919.308702 sender=org.freedesktop.DBus -> destination=:1.91 serial=4 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameLost
   string ":1.91"


method call time=1731835922.954899 sender=:1.92 -> destination=org.freedesktop.DBus serial=1 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=Hello
method return time=1731835922.955003 sender=org.freedesktop.DBus -> destination=:1.92 serial=1 reply_serial=1
   string ":1.92"
signal time=1731835922.955077 sender=org.freedesktop.DBus -> destination=(null destination) serial=194 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
   string ":1.92"
   string ""
   string ":1.92"
signal time=1731835922.955199 sender=org.freedesktop.DBus -> destination=:1.92 serial=2 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameAcquired
   string ":1.92"
method call time=1731835922.957174 sender=:1.92 -> destination=org.freedesktop.DBus serial=2 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=RequestName
   string "org.example.com.TestService"
   uint32 0
signal time=1731835922.957438 sender=org.freedesktop.DBus -> destination=(null destination) serial=195 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
   string "org.example.com.TestService"
   string ""
   string ":1.92"
signal time=1731835922.957562 sender=org.freedesktop.DBus -> destination=:1.92 serial=3 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameAcquired
   string "org.example.com.TestService"
method return time=1731835922.957631 sender=org.freedesktop.DBus -> destination=:1.92 serial=4 reply_serial=2
   uint32 1
signal time=1731835922.960651 sender=org.freedesktop.DBus -> destination=:1.92 serial=5 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameLost
   string "org.example.com.TestService"
signal time=1731835922.960801 sender=org.freedesktop.DBus -> destination=(null destination) serial=196 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
   string "org.example.com.TestService"
   string ":1.92"
   string ""
signal time=1731835922.962686 sender=org.freedesktop.DBus -> destination=:1.92 serial=6 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameLost
   string ":1.92"
signal time=1731835922.962764 sender=org.freedesktop.DBus -> destination=(null destination) serial=197 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
   string ":1.92"
   string ":1.92"
   string ""
^C
heirish@raspberrypi:~$ ^C
heirish@raspberrypi:~$ ^C
heirish@raspberrypi:~$
```

### references
- https://www.cnblogs.com/muahao/p/10333562.html
- https://www.cnblogs.com/zhoug2020/p/4516144.html