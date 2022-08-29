#!/bin/sh
#
# Echo URLs for FreeBSD man pages on freebsd.org

# Self-reported URL
# https://www.freebsd.org/cgi/man.cgi?query=perror&apropos=0&sektion=3&manpath=FreeBSD+14.0-current&arch=default&format=html
# Also works
# https://www.freebsd.org/cgi/man.cgi?query=perror&sektion=3

arg0=$(basename "$0" .sh)
optstr="hs:"
usestr="Usage: $arg0 [-h] [-s section] name [...]"
help()
{
    echo "$usestr"
    echo ''
    echo '  -s section  Section number for manual entries (default 2)'
    echo '  -h          Print this help message and exit'
    echo ''
    exit 0
}
usage()
{
    echo "$usestr" >&2
    exit
}

section=2
while getopts "$optstr" arg
do
    case "$arg" in
    (h) help;;
    (s) section="$OPTARG";;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
[ $# = 0 ] && usage

baseurl="http://www.freebsd.org/cgi/man.cgi"
bq='`'

for name in "$@"
do
    echo "[$bq$name($section)$bq]($baseurl?query=$name&sektion=$section)"
done
