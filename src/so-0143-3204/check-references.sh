#!/bin/sh
#
# Check that there is a reference in $1 to each of the other arguments.
# Check that there is no reference to a file not in the other arguments.

status=0
source="$1"
shift

tmp1="$(mktemp ./refs.XXXXXX)"
tmp2="$(mktemp ./defs.XXXXXX)"

trap "rm -f $tmp1 $tmp2; exit 1" 0 1 2 3 13 15

grep -E -e '^### [-[:alnum:]_]+[.][mch]k?$' "$source" |
sed 's/^### //' | sort > "$tmp1"

dups=$(uniq -c "$tmp1" |
       sed -n -e '/^[[:space:]]*1[[:space:]]/d' \
              -e 's/^[[:space:]]*[0-9]\{1,\}[[:space:]]\{1,\}//p')
if [ -n "$dups" ]
then
    echo "$0: duplicated sections:" $dups >&2
    status=1
fi

sort -u -o "$tmp1" "$tmp1"

printf '%s\n' "$@" | sort -u > "$tmp2"

unref=$(comm -23 "$tmp1" "$tmp2")
if [ -n "$unref" ]
then
    echo "$0: sections not listed in files list:" $unref >&2
    status=1
fi

undef=$(comm -13 "$tmp1" "$tmp2")
if [ -n "$undef" ]
then
    echo "$0: files not listed in a section:" $undef >&2
    status=1
fi

rm -f $tmp1 $tmp2
trap 0
exit $status
