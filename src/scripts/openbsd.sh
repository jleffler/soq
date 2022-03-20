#!/bin/sh
#
# Echo URLs for OpenBSD man pages on man.openbsd.org

baseurl="http://man.openbsd.org"
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
    echo "[$bq$name($section)$bq]($baseurl/$name.$section)"
done
