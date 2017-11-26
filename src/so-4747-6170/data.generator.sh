#!/bin/sh
#
# Generate random data for SO 4747-6170
# Crude argument handling

number=1000000
if [ $# -ge 1 ]
then number=$1; shift
fi

# Generated with seed: -S 0xE946DD5B 
random -n ${1:-1000000} "$@" \
    -T '%W%[0:9]d%W%03[0:999]d%3W%[0:9]d.%[0:9]d    %6[100000:999999]d  %[1000000:999999999]d' |
sed 's/^[^.]*/&  &/'
