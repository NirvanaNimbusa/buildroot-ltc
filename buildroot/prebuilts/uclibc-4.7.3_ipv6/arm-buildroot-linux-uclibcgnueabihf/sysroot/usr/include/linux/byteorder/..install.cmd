cmd_/nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/byteorder/.install := /bin/bash scripts/headers_install.sh /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/byteorder   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/byteorder/big_endian.h   /nfs/dev/buildroot-2014.02/output/build/linux-headers-3.10.32/include/uapi/linux/byteorder/little_endian.h ; for F in ; do echo "\#include <asm-generic/$$F>" > /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/byteorder/$$F; done; touch /nfs/dev/buildroot-2014.02/output/host/usr/arm-buildroot-linux-uclibcgnueabihf/sysroot/usr/include/linux/byteorder/.install