#!/bin/sh
#
# Echo URLs for Linux man pages on man7.org

baseurl="http://linux.die.net/man"
bq='`'

section=2
while getopts s: arg
do
    case "$arg" in
    (s) section="$OPTARG";;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
[ $# = 0 ] && usage

for name in "$@"
do
    echo "[$bq$name($section)$bq]($baseurl/$section/$name)"
done
