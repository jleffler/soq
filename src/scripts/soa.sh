#!/bin/sh
#
# Create a skeletal file for an SO question

arg0="$(basename "$0" .sh)"
usestr='[-x extension][-p prefix] number [prefix]'
prefix='xyz'
extension='.c'
while getopts x:p: opt
do
    case "$opt" in
    (x) extension="$OPTARG";;
    (p) prefix="$OPTARG";;
    (*) echo "Usage: $arg00 $usestr" >&2; exit 1;;
    esac
done

shift $(($OPTIND - 1))

case "$#" in
(1) number="$1";;
(2) number="$1"; prefix="$2";;
(*) echo "Usage: $arg0 $usestr" >&2; exit 1;;
esac

cs='#'
ce=''
case "$extension" in
(.c|.cpp|c|cpp) cs='/*'; ce=' */';;
(.sql|sql)      cs='--'; ce='';;
esac

number=$(echo "$number" | sed 's/^/0000000/; s/.*\([0-9]\{8\}\)/\1/; s/^..../&-/')
echo "$cs SO $number$ce" > $(rfn -x "$extension" "$prefix")
