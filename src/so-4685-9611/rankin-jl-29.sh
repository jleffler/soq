#!/bin/bash
#
# SO 4685-9611 (https://stackoverflow.com/q/46859611)

# JL revision of second answer by David Rankin

arg0="$(basename "$0" .sh)"
case $# in
(1) datafile="$1";;
(*) echo "Usage: $arg0 file" >&2; exit 1;;
esac

[ -r "$datafile" ] || { echo "$arg0: file $datafile is not readable" >&2; exit 1; }

tmpfile="$(mktemp "$arg0-XXXXXX")"
trap 'rm -f "$tmpfile"; exit 1' 0 1 2 3 13 15  

while read -r l; do 
    tmp="${l%.*}"
    tld="${l#"$tmp".}"
    dom="${tmp##*.}"
    echo "$dom.$tld"
done < <(grep '..*[.]..*[.]..*[.]..*$' "$datafile") > "$tmpfile"

for i in $(sort -u "$tmpfile"); do 
    [ $(grep -c "$i" "$datafile") -gt '3' ] && echo "$i"
done

rm -f "$tmpfile"
trap 0
