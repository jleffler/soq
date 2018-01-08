#!/bin/sh
#
# Refresh SOQ code from reference version

tmp=$(mktemp "${TMPDIR:-/tmp}/tmp.XXXXXXXXX")
trap "rm -f $tmp; exit 1" 0 1 2 3 13 15

for file in "$@"
do
    reffile="$HOME/lib/JL/$file"
    if [ ! -f "$reffile" ]
    then echo "Unmatched - $file"
    elif [ ! -f "$file" ]
    then echo "Introduce — $file"
         ${PERL:-perl} githeader.pl "$reffile" > "$file"
    elif ${PERL:-perl} githeader.pl "$reffile" > "$tmp"
         cmp -s "$file" "$tmp"
    then echo "Unchanged - $file"
    else echo "Refreshed - $file"
         cp "$tmp" "$file"
    fi
done

rm -f "$tmp"
trap 0
