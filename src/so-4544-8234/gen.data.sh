#!/bin/sh
#
# Generate sinusoidal data by month with random perturbation

case "$#" in
(0) set -- $(date '+%Y');;
esac

for year in "$@"
do
    gen.sinusoid $year |
    colnum -c 8 |
    perturb -g 2.5 |
    mon.grouping $year |
    tee temp.data.$year
done

