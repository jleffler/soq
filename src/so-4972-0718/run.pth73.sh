#!/bin/sh
#
# Run pth73 5 times for each of variants 0-4, passing any extra
# arguments to the program (e.g. -n 10 -c 15000 -w 5)

${MAKE:=make} pth73

for variant in 0 1 2 3 4
do
    for repeat in 1 2 3 4 5
    do
        pth73 -$variant "$@"
    done
done
