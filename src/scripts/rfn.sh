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

count=0
while name="${1:-xx}$(ddpr)$suffix"; [ -f "$name" ]
do
    # Try a new name since that one exists.
    # There are 21 primes between 11 and 97.
    # No; 20 attempts doesn't guarantee that
    # all have been tried, but most have.
    if [ $((count++)) -gt 20 ]
    then
        echo "/dev/null"    # It is used in redirections; this is fairly safe
        echo "$0: too many attempts to create a name like $name" >&2
        exit 1
    fi
done

echo "$name"
echo "$name" >&2
