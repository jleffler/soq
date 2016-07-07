#!/bin/sh

sysdir="./system-headers"
for header in "$@"
do
    mkdir -p "$sysdir/$(dirname $header)"
    echo "include <$header>" > "$sysdir/$header"
done
