#!/bin/sh
#
# Generate a reference to a section of the C11 standard on port70.net

arg0=$(basename "$0" .sh)
optstr="hp:s:t:"
usestr="Usage: $arg0 [-h] -s section [-t title] [-p paragraph]"
help()
{
    echo "$usestr"
    echo ''
    echo '  -p paragraph  Paragraph within the section'
    echo '  -s section    Section number for manual entries (default 2)'
    echo '  -t title      Title of the section'
    echo '  -h            Print this help message and exit'
    echo ''
    exit 0
}
usage()
{
    echo "$usestr" >&2
    exit 1
}
error()
{
    echo "$arg0: $*" >&2
    exit 1
}

section=''
title=''
paragraph=''
while getopts "$optstr" arg
do
    case "$arg" in
    (h) help;;
    (p) paragraph="$OPTARG";;
    (s) section="$OPTARG";;
    (t) title="$OPTARG";;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
[ $# != 0 ] && usage
[ -z "$section" ] && error "No section [-s section] specified"

baseurl='https://port70.net/~nsz/c/c11/n1570.html'

[ -n "$paragraph" ] && paragraph=" §$paragraph"
[ -n "$title" ] && title=" $title"

echo "[§$section$title$paragraph]($baseurl#$section)"
