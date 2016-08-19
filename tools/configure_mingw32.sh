#!/bin/sh
SDIR=$(dirname $0)
export CFLAGS="-g -O2 -Wno-format -Wno-error"
$SDIR/../configure --prefix=/mingw32 --enable-debug --host=mingw32
#--host=i686-mingw32
#--host=mingw32
#--host=i686-w64-mingw32
