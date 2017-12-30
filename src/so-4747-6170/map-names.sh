#!/bin/sh
#
# Map script names to descriptive names

sed -e 's/chepner-1.sh/Chepner 1 Shell/' \
    -e 's/pyscript.py/Python 7000/' \
    -e 's/jlscript.sh/Leffler Shell/' \
    -e 's/jlscript.pl/Perl 7000/' \
    -e 's/awkscript-256.sh/Awk 256/' \
    -e 's/awkscript.sh/Awk 7000/' \
    -e 's/opscript.sh/Lucas A Shell/' \
    -e 's/chepner-2.sh/Chepner 2 Shell/' \
    "$@"
