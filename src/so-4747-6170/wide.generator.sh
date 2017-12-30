#!/bin/sh
#
# Generate random data for SO 4747-6170
# Crude argument handling

number=1000000
if [ $# -ge 1 ]
then number=$1; shift
fi

part1='%W%[0:9]d%W%03[0:999]d%3W%[0:9]d.%[0:9]d'
part2='%6[100000:999999]d'
part3='%9[1000000:999999999]d'
part4='%7[1000:9999999]d.%03[0:9]d'


# Generated with seed: -S 0xE946DD5B 
random -n $number "$@" \
    -T "$part1    $part2  $part3  $part2  $part3  $part4  $part4  $part4  $part4" |
sed 's/^[^.]*/&  &/'
