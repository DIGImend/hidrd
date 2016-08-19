#!/bin/sh
#
# File:   start_gdbd.sh
# Author: Anthony Campbell
#
# Created on 11-Aug-2016, 13:04:35
#
if [[ $# -eq 1 ]] ; then
    echo 'please app <instance id>'
    exit 0
fi
if [[ $# -eq 0 ]] ; then
    echo 'please app <instance id>'
    exit 0
fi

adb pull //system/xbin/daemonsu  $(dirname $0)/System  #is where app_process links
mv $(dirname $0)/System/daemonsu $(dirname $0)/System/app_process64
adb pull //system/bin/linker64  $(dirname $0)/System
adb forward tcp:5039 tcp:5039
adb shell   run-as com.claydonkey.hidrd  //data/app/com.claydonkey.hidrd-"$2"/lib/arm64/gdbserver.so tcp:5039 --attach $(adb shell ps | grep $1 | awk '{print $2}')
#adb shell   //data/local/tmp/gdbserver tcp:5039 --attach $(adb shell ps | grep $1 | awk '{print $2}')
#sleep 10
# /android64/bin/gdb   $(dirname $0)/System/app_process64
