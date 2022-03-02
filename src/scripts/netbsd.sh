#!/bin/sh
#
# Echo URLs for NetBSD man pages on man.netbsd.org

baseurl="http://man.netbsd.org"
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
