#!/bin/bash
#
# SO 4685-9611 (https://stackoverflow.com/q/46859611)

# Transcript of second answer by David Rankin
# The use of (( to start two subshells is interesting.
# Presumably, the fact that the first ) is separated from the second
# tells the shell that it is not parsing an arithmetic expression
# ((...)).  There is a sound reason why the double sub-shell is used in
# the answer, though it isn't important when packaged as a free-standing
# script.

((
while read -r l; do 
    tmp="${l%.*}"
    tld="${l#"$tmp".}"
    dom="${tmp##*.}"
    echo "$dom.$tld"
done < <(grep '..*[.]..*[.]..*[.]..*$' yourfile.txt) ) > temp_file

for i in $(sort -u temp_file); do 
    [ $(grep -c "$i" yourfile.txt) -gt '3' ] && echo "$i"
done

rm temp_file)
