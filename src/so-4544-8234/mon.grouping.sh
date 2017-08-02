#!/bin/sh
#
# Monthly grouping of data

# 30 days hath September, April, June and November.
# All the rest have 31 except for February alone.

awk '
BEGIN { mdays[ 1] = 31; mdays[ 2] = 28; mdays[ 3] = 31
        mdays[ 4] = 30; mdays[ 5] = 31; mdays[ 6] = 30
        mdays[ 7] = 31; mdays[ 8] = 31; mdays[ 9] = 30
        mdays[10] = 31; mdays[11] = 30; mdays[12] = 31
        mnum = 1
      }
      {
        if (mdays[mnum]-- == 0)
        {
            print ""; mnum++; mdays[mnum]--
        }
        printf "%7.2f", $0;
      }
END   { print "" }' "$@"
