#!/bin/sh
#
# Generate standardized message about dot and arrow operators for SO

usage()
{
    echo "Usage: $(basename "$0" .sh) [-a|-d] variable member [...]" >&2
    exit 1
}

separator="->"
while getopts "ad" opt
do
    case "$opt" in
    (a) separator="->";;
    (d) separator=".";;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))

if [ $# = 1 ]
then usage
fi

if [ $# -lt 2 ]
then set -- ptr member
fi

str1=$(echo "$@" | sed 's/[[:space:]]\{1,\}/ '"$separator"' /g')
str2=$(echo "$@" | sed 's/[[:space:]]\{1,\}/'"$separator"'/g')

# Beware back-ticks in unquoted here documents!
cat << EOF
Style guide: the dot \`.\` and arrow \`->\` operators bind very tightly and should not be used with spaces around them.
Writing \`$str1\` is not idiomatic C; use \`$str2\`.
EOF
