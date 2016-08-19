#!/bin/sh
SDIR=$(dirname $0)
export CFLAGS="$CFLAGS -Wno-error -Wno-format"
echo $CFLAGS
$SDIR/../configure --enable-debug
