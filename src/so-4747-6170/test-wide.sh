#!/bin/sh
#
# Test performance of different Perl scripts on wider rows of data

for i in $(range 99)
do
    for variant in 2 3 4
    do
        sh test-setup.sh
        timecmd -msr -- perl jlperl-$variant.pl presorted.wide
        sh test-check.sh
    done
done
