#!/bin/sh
SDIR=$(dirname $0)
export CFLAGS="-Wno-format -Wno-error"
$SDIR/../configure --prefix=/mingw64 --enable-debug 
