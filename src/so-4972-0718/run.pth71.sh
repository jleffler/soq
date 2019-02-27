#!/bin/sh
#
# Run pth73 5 times for each of variants 0-4, passing any extra
# arguments to the program (e.g. -t)

${MAKE:=make} pth71

for variant in 0 1 2 3 4
do
    for repeat in 1 2 3 4 5
    do
        pth71 -$variant "$@"
    done
done

