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

fn="()"
[ "$section" = 1 ] && fn=""

for name in "$@"
do
    echo "[$bq$name$fn$bq]($baseurl/$section/$name)"
done
