#!/bin/sh
#
# Echo URLs for NetBSD man pages on man.netbsd.org

# Self-reported URL
# https://www.freebsd.org/cgi/man.cgi?query=perror&apropos=0&sektion=3&manpath=FreeBSD+14.0-current&arch=default&format=html
# Also works
# https://www.freebsd.org/cgi/man.cgi?query=perror&sektion=3

baseurl="http://www.freebsd.org/cgi/man.cgi"
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
    echo "[$bq$name($section)$bq]($baseurl?query=$name&sektion=$section)"
done
