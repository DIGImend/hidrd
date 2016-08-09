#!/bin/sh

echo running: "$0" "$1"

export CROSS_COMPILE=aarch64-linux-android

#prefix
export  "$1"

# Apparently android-8 works fine, there are other versions, look them up
export SYSROOT=${prefix}/sysroot/usr
export CFLAGS="-fPIE -I${ANDROID_PREFIX}/include/python2.7 -DHAVE_IEEEFP_H=0 -DHAVE_SSIZE_T -DPY_FORMAT_SIZE_T=l -DPY_FORMAT_LONG_LONG=ll"
export CROSS_PATH=${prefix}/bin/${CROSS_COMPILE}
export PYTHON_INCLUDES=${prefix}/include/python2.7
export PYTHON_LIBS="-L${prefix}/lib/python2.7 -L${prefix}/lib"

# Non-exhaustive lists of compiler + binutils	
# Depending on what you compile, you might need more binutils than that
export CPP=${CROSS_PATH}-cpp
export AR=${CROSS_PATH}-ar
export AS=${CROSS_PATH}-as
export NM=${CROSS_PATH}-nm
export CC=${CROSS_PATH}-gcc
export CXX=${CROSS_PATH}-g++
export LD=${CROSS_PATH}-ld
export RANLIB=${CROSS_PATH}-ranlib


# Don't mix up .pc files from your host and build target
export PKG_CONFIG_PATH=${prefix}/lib/pkgconfig

# You can clone the full Android sources to get bionic if you want.. I didn't
# want to so I just got linker.h from here: http://gitorious.org/0xdroid/bionic
# Note that this was only required to build boehm-gc with dynamic linking support.
export CFLAGS="${CFLAGS} --sysroot=${SYSROOT} -I${prefix}/include -I${SYSROOT}/include "
export CPPFLAGS="${CFLAGS}"
export LDFLAGS="${LDFLAGS} -pie -L${SYSROOT}/lib -L${prefix}/lib"

./configure  "$@" $* --host=${CROSS_COMPILE}   --prefix=${prefix}  --build=x86_64-pc-linux-gnu 
