#!/usr/bin/bash
sudo apt-get update -y 
sudo apt-get install cmake
sudo apt-get install gdb
sudo apt-get install clang clangd -y

#install all the libraries which are required to compile and run a C++ program.
sudo apt-get install build-essential -y

###install manpages for c
sudo apt-get install glibc-doc libc-dev manpages manpages-dev
#for posix function
sudo apt-get install manpages-posix manpages-posix-dev

###kernel function
sudo apt-get install linux-doc libcorelinux-dev

##c++doc, cppman的文档可读性要好一些
##apt-cache search libstdc++ | grep doc
#audo apt-get install libstdc++-<version>-doc

####查找doc时，可以先用man -k <name> 查找存在对应doc的section,然后用man <section> <name>查看doc
#heirish@local:~$ man -k mutex_lock  <-----section 3和3posix都存在对应的doc
#pthread_mutex_lock (3) - operations on mutexes
#pthread_mutex_lock (3posix) - lock and unlock a mutex
#heirish@local:~$ man 3posix pthread_mutex_lock

#己经删除的manpage可能还可以通过man -k查出来
#sudo mandb #更新man page cache
