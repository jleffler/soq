#!/bin/sh
#
# Standard spiel for use of stderr.[ch] in an answer.

directory=
files=()
while getopts d:f: arg
do
    case "$arg" in
    (d) directory="$OPTARG";;
    (f) files+=("$OPTARG");;
    (*) exit 1;;
    esac
done

shift $(($OPTIND - 1))

files+=("$@")

if [ "${#files[@]}" = 0 ]
then
    files=(stderr.c stderr.h)
fi
if [ -z "$directory" ]
then
    directory="src/libsoq"
fi

list=
for file in "${files[@]}"
do
    list="$list, \`$file\`"
done

if [ "${#files[@]}" = 1 ]
then names="file"
else names="files"
fi

list=$(echo "$list" | sed -e 's/^, //' -e 's/, \([^ ,]*\)$/ and \1/')

exec cat <<EOF | tr '\n' ' '
This code is available in my [SOQ](https://github.com/jleffler/soq)
(Stack Overflow Questions) repository on GitHub as $names
$list in the
[$directory](https://github.com/jleffler/soq/tree/master/$directory)
sub-directory.
EOF
