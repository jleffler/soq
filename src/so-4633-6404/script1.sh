#!/bin/bash
#
# Requires GNU sed.

comm 1.sorted.txt 2.sorted.txt | /opt/gnu/bin/sed -f script1.sed
