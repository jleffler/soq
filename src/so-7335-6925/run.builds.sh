#!/bin/sh
#
# Run sequence of compilations

for program in gcc23 gcc37
do
    set -x
    rm -f $program
    make CC=gcc $program "$@"
    rm -f $program
    make CC=clang $program "$@"
    rm -f $program
    make CC=clang UFLAGS=-Weverything $program "$@"
done
