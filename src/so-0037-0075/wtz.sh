#!/bin/sh
# Command-line world clock
# SO 0037-0075

: ${WORLDCLOCK_ZONES:=$HOME/etc/worldclock.zones}
: ${WORLDCLOCK_FORMAT:='+%Y-%m-%d %H:%M:%S %Z'}

sed 's/#.*//; /^[[:space:]]*$/d' "$WORLDCLOCK_ZONES" |
while read zone
do echo $zone '!' $(TZ=$zone date "$WORLDCLOCK_FORMAT")
done |
awk -F '!' '{ printf "%-23s  %s\n", $1, $2;}' |
sort -b -r -k2,2 -k3,3
