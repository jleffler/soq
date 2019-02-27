#!/bin/sh
#
# Monthly grouping of data

# 30 days hath September, April, June and November.
# All the rest have 31 except for February alone.

case $# in
(1) year="$1"; shift;;
(*) year=$(date '+%Y');;
esac

awk -v year="$year" '
function is_leap_year(y) { if (y % 4 != 0 || (y % 100 == 0 && y % 400 != 0)) return 0; return 1; }
BEGIN { mdays[ 1] = 31; mdays[ 2] = 28; mdays[ 3] = 31
        mdays[ 4] = 30; mdays[ 5] = 31; mdays[ 6] = 30
        mdays[ 7] = 31; mdays[ 8] = 31; mdays[ 9] = 30
        mdays[10] = 31; mdays[11] = 30; mdays[12] = 31
        mnum = 1
        mdays[2] += is_leap_year(year)
        printf "%.4d %2d", year, mnum
      }
      {
        if (mdays[mnum]-- == 0)
        {
            print ""; mnum++; mdays[mnum]--
            printf "%.4d %2d", year, mnum
        }
        printf "%7.2f", $0;
      }
END   { print "" }' "$@"
