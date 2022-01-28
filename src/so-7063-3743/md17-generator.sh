#!/bin/sh
#
# Data Generator for md41, md43

{ echo 10000; random -n 10000 -F '%[-1000:+1000]d'; } |
tee input.$(isodate -c) |
Trace -e -a -u -- md41 -v
