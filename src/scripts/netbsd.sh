#!/bin/sh
#
# Echo URLs for NetBSD man pages on man.netbsd.org

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

baseurl="http://man.netbsd.org"
bq='`'

for name in "$@"
do
    echo "[$bq$name($section)$bq]($baseurl/$name.$section)"
done
