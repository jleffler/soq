#!/bin/sh
#
# Test all possible combinations of 01, 02, 12

for i in 01 02 12
do
    for j in 01 02 12
    do
        for k in 01 02 12
        do
            st19 $i $j $k
        done
    done
done
