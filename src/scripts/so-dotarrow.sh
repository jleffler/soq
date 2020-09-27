#!/bin/sh
#
# Generate standardized message about dot and arrow operators for SO

usage()
{
    echo "Usage: $(basename "$0" .sh) [-a|-d] [variable member]" >&2
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

if [ $# -eq 0 ]
then
    if [ "x$separator" = "x->" ]
    then set -- ptr member
    else set -- structure member
    fi
elif [ $# -eq 1 ] || [ $# -gt 2 ]
then usage
fi

str1=$(echo "$@" | sed 's/[[:space:]]\{1,\}/ '"$separator"' /g')
str2=$(echo "$@" | sed 's/[[:space:]]\{1,\}/'"$separator"'/g')

# Beware back-ticks in unquoted here documents!
cat << EOF
Style guide: the dot \`.\` and arrow \`->\` operators bind very tightly
because they are [postfix operators](http://port70.net/~nsz/c/c11/n1570.html#6.5.2.3).
They should not be written with spaces around them.
Writing \`$str1\` is not idiomatic C and indicates that the coder
is a tyro (newbie).  Use \`$str2\`.
EOF
