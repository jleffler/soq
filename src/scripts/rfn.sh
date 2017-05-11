#!/bin/bash
#
# Create a random file name from a prefix, a double-digit prime number, and a suffix

case "$#" in
([01]) : OK;;
(*)     echo "Usage: $(basename "$0" .sh) [prefix]" >&2; exit 1;;
esac

case "$0" in
(*[-.]c)    suffix=".c";;
(*[-.]h)    suffix=".h";;
(*[-.]sh)   suffix=".sh";;
(*[-.]pl)   suffix=".pl";;
(*[-.]sql)  suffix=".sql";;
(*[-.]cpp)  suffix=".cpp";;
(*)         suffix="";
esac

name="${1:-xx}$(ddpr)$suffix"
echo "$name"
echo "$name" >&2
