#!/bin/sh
#
# BSD sed OK; GNU sed OK

comm 1.sorted.txt 2.sorted.txt | sed -f script2.sed
