#!/bin/bash
#
# SO 38494701

tmp=$(mktemp ./tmp.XXXXXX)
trap 'rm -f "$tmp" "$tmp".?; exit 1' 0 1 2 3 13 15

sed 's/[[:space:]].*//' "$@" | sort -u > $tmp.0

join_cmd()
{
    join -e 0 -a 1 -a 2 -o "$outcols" "$@" > "$tmp.2"
}

outcols="0,2.2"
# Generate list of all names
join_cmd "$tmp.0" <(sort "$1")
mv "$tmp.2" "$tmp.1"
shift
outcols="0,1.2,2.2"  

for sample in "$@"
do
    join_cmd "$tmp.1" <(sort "$sample")
    sed 's/[[:space:]]\([0-9][0-9]*\)$/,\1/' "$tmp.2" > "$tmp.1"
done

# Don't hard code the output file name — do that on the command line that
# invokes this script (same as you specify the input file names on the command line).
sed 's/,/    /g' "$tmp.1" # > integrate.file

rm -f "$tmp" "$tmp".?
trap 0 1 2 3 13 15
