#!/bin/bash
#
# Create makefiles in so-abcd-wxyz directories that lack them.

shopt -s nullglob
for d in so-*
do
    if [ ! -f $d/makefile ]
    then
    {
        echo $d | sed 's/so-\(....\)-\(....\)/# SO \1\2/'
        echo
        echo "include ../../etc/soq-head.mk"
        echo
        n=1
        for extn in c cpp py sh pl
        do
            for file in $d/*.$extn
            do
                echo "PROG$n = $(basename "$file" ".$extn")"
                : $((n=$n+1))
            done
        done
        echo
        printf "PROGRAMS ="
        for ((m = 1; m < n; m++))
        do
            printf ' ${PROG%d}' $m
        done
        printf '\n\n'
        echo 'all: ${PROGRAMS}'
        echo
        echo "include ../../etc/soq-tail.mk"
    } > $d/makefile
    fi
done
