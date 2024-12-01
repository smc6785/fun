#!/bin/baah

export LFS=/mnt/lfs
export LFS_TARGET=x86_64-lfs-linux-gnu
export LFS_DISK=/dev/name_of_storage_device

if ! grep -q "$LFS" /proc/mounts; then
  source setupdisk.sh "LFS_DISK"
  sudo mount "${LFS_DISK}2" "$LFS"
  # chmod +x lfs.sh
  sudo chown -v $USER "$LFS"
fi

mkdir -pv $LFS/sources
mkdir -pv $LFS/tools

# file system hierarchy(fsh) stuff
# a standard on unix system

mkdir -pv $LFS/boot
# - bootloader, bootloader config, kernel
# - initial rd stuff

mkdir -pv $LFS/etc
# - configuration files
# - system wide config, hardware config
# - extended text configuration
# - miscellaneous

mkdir -pv $LFS/bin
# - binaries, programs

mkdir -pv $LFS/lib
# - user programs/libraries
# - Linux tries to make programs to share libraries

mkdir -pv $LFS/sbin
# - system programs/binaries

mkdir -pv $LFS/usr
mkdir -pv $LFS/var

# proc, entries for running processes
# sys, communication to kernels
if echo $LFS_TARGET | grep -qs '64'; then
  mkdir -pv $LFS/lib64
fi

cd "$LFS/sources"
export PATH="$LFS/tools/bin:$PATH"

