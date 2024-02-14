#!/bin/bash

size=4096
while al $(perl -le 'print "XXXXXXX YYYYYYY\n" x '"$size") >/dev/null
do
    echo "$(($size * 16)) = $(($size * 16 / 1024)) KiB"
    size=$(($size + 128))
done
