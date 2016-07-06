#!/bin/sh
#
# Generate random data for QT19 (quad tree) program.

tmp=${TMPDIR:-/tmp}/qtg.$$

trap "rm -f $tmp.1; exit 1" 0 1 2 3 13 15

random -n ${1:-10} -T '%6:0[1:20]f   %6:2[-100:100]f %6:2[-100:100]f   %6:2[-10:10]f %6:2[-10:10]f' > "$tmp.1"
${QT19:-./qt19} "$tmp.1"

rm -f $tmp.1
trap 0 1 2 3 13 15
