#!/bin/bash
#
# Check on progress of sorting for 'bigsort-test'.

shopt -s nullglob  # Expand 'sort*' to nothing when there are no sort* files left.

for i in $(range 1 600)
do
    if (x=(sort*); echo $(isodate; echo "${#x[@]}"); [ "${#x[@]}" = 0 ] && exit 1; exit 0)
    then sleep 30
    else break
    fi
done
