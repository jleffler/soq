#!/bin/bash
#
# Calculate days between two dates using GNU date command
# Allow for time zone switches

arg0=$(basename "$0" .sh)
DATE=/usr/gnu/bin/date

case $# in
1)  old="$1"; new=$($DATE +"%Y-%m-%d");;
2)  old="$1"; new="$2";;
*)  echo "Usage: $arg0 old [new]" >&2; exit 1;;
esac

case "$old" in
[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]) : OK;;
*) echo "$arg0: $old does not match YYYY-mm-dd" >&2; exit 1;;
esac

case "$new" in
[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]) : OK;;
*) echo "$arg0: $new does not match YYYY-mm-dd" >&2; exit 1;;
esac

if [[ "$old" > "$new" ]]
then t="$old"; old="$new"; new="$t"
fi

old_secs=$($DATE +'%s' -d "$old")
new_secs=$($DATE +'%s' -d "$new")
echo $(( ($new_secs - $old_secs) / 86400 ))

old_secs=$($DATE +'%s' -d "$old")
new_secs=$($DATE +'%s' -d "$new 12:00:00")
echo $(( ($new_secs - $old_secs) / 86400 ))
