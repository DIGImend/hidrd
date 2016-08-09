#!/bin/sh

echo running: "$0" "$1"

export CROSS_COMPILE=arm-linux-androideabi

#gcc-4.7 toolchain
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


export XML2_CONFIG=/./bin/xml2-config
export LIBXML2_CFLAGS=-I./include/libxml2
export LIBXML2_LIBS="-L./lib -lxml2 -lz -liconv"


# Don't mix up .pc files from your host and build target
export PKG_CONFIG_PATH=${prefix}/lib/pkgconfig

# You can clone the full Android sources to get bionic if you want.. I didn't
# want to so I just got linker.h from here: http://gitorious.org/0xdroid/bionic
# Note that this was only required to build boehm-gc with dynamic linking support.
export CFLAGS="${CFLAGS} --sysroot=${SYSROOT} -I${SYSROOT}/include -I${prefix}/include"
export CPPFLAGS="${CFLAGS}"
export LDFLAGS="${LDFLAGS} -L${SYSROOT}/lib -L${prefix}/lib"

./configure  --without-python $* --host=${CROSS_COMPILE} --with-sysroot=${SYSROOT} --prefix=${prefix} "$@"  --build=x86_64-pc-linux-gnu 
