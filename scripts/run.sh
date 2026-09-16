#!/bin/bash

if [ $# -lt 3 ]; then
  echo -e "\nUsage: run \$VERSION[e.g., v4.10] \$ARCH[e.g., i386, x86_64] \$IMAGE[e.g., buster, stretch, focal, bionic] -ssh \$SSHPORT[e.g., 10000] -dbg \$DBGPORT[e.g., 20000] -dev \$DEVICES[e.g., uv]\n"
  exit
fi

VERSION=$1
ARCH=$2
IMAGE=$3
SSHPORT=""
DBGPORT=""
DEVICES=""

shift 3

while [ -n "$1" ]; do
  case $1 in
    -ssh) SSHPORT=",hostfwd=tcp::$2-:22"; shift 2;;
    -dbg) DBGPORT="-S -gdb tcp::$2"; shift 2;;
    -dev) DEVICES="${DEVICES} -device $2"; shift 2;;
  esac
done

# guest /tmp/share
ROOT=${HOME}/Kernel
HDA=${ROOT}/image/${ARCH}/${IMAGE}.img
LINUX=${ROOT}/${VERSION}/${ARCH}
# LINUX=${ROOT}/git
SHARE=${ROOT}/share
KERNEL=${LINUX}/arch/x86/boot/bzImage

if [ ! -f ${KERNEL} ]; then
  echo "Compile the target kernel before using it..."
  exit
fi

qemu-system-x86_64 \
    -snapshot \
    -s \
    -m 4G \
    -smp 2 \
    -kernel ${KERNEL} \
    -append "nokaslr console=ttyS0 root=/dev/sda earlyprintk=serial net.ifnames=0" \
    -drive file=${HDA},format=raw \
    -nographic \
    -net user,host=10.0.2.10,hostfwd=tcp:127.0.0.1:10021-:22 \
    -net nic,model=e1000 \
    -fsdev local,security_model=passthrough,id=fsdev0,path=${LINUX} \
    -device virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostlinux \
    -fsdev local,security_model=passthrough,id=fsdev1,path=${SHARE} \
    -device virtio-9p-pci,id=fs1,fsdev=fsdev1,mount_tag=hostshare \
    -pidfile vm.pid \
    -cpu qemu64 \
    2>&1 | tee vm.log

