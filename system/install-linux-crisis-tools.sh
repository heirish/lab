#!/usr/bin/bash
sudo apt-get update -y

#basic stats: ps, vmstat, uptime, top
sudo apt-get install procps

#system log, device info: dmesg, lsblk, lscpu
sudo apt-get install util-linux

#device stats: iostat, mpstat, pidstat, sar
sudo apt-get install sysstat

#preferred net tools: ip, ss, nstat, tc
sudo apt-get install iproute2

#NUMA stats: numastat
sudo apt-get install numactl

#Network sniffer: tcpdump
sudo apt-get install tcpdump

#profiler and PMU stats: perf, turbostat
sudo apt-get install linux-tools-common linux-tools-$(uname -r)

#canned eBPF tools: opensnoop, execsnoop, runqlat, softirqs, hardirqs, ext4slower, ext4dist, biotop, biosnoop, biolatency, tcptop, tcplife, trace, argdist
#funccount, profile, etc. command all with -bpfcc suffix
sudo apt-get install bpfcc-tools

#eBPF scripting:bpftrace, basic versions of opensnoop, execsnoop, runqlat, biosnoop, etc.
sudo apt-get install bpftrace

#Ftrace CLI: trace-cmd
sudo apt-get install trace-cmd

#net device stats: nicstat
sudo apt-get install nicstat

#net device info: ethtool
sudo apt-get install ethtool

#PMU/PMC top: tiptop
sudo apt-get install tiptop

#CPU details:cpuid
#sudo apt-get install cpuid

#CPU digging: rdmsr, wrmsr
#sudo apt-get install msr-tools