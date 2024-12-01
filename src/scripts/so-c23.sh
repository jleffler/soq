#!/bin/sh
#
# Identify the C23 standard and drafts

arg0=$(basename "$0" .sh)
optstr="hls"
usestr="Usage: $arg0 [-hls]"
help()
{
    echo "$usestr"
    echo ''
    echo '  -h Print this help message and exit'
    echo '  -l Print extra information (~950 characters)'
    echo '  -s Print short information (~520 characters; default)'
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

length='short'
while getopts "$optstr" arg
do
    case "$arg" in
    (h) help;;
    (l) length="long";;
    (s) length="short";;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
[ $# != 0 ] && usage

if [ "$length" = 'short' ]
then filter="nbncl"
else filter="sed 's/#//'"
fi

eval $filter <<'EOF' | so-flatten

[ISO/IEC 9899:2024](https://www.iso.org/standard/82075.html) was
published in late October 2024 and it costs 216 CHF (about 258 USD).

It is available from the [ANSI Web
Store](https://webstore.ansi.org/standards/iso/isoiec98992024)
at 278 USD.

#As of 2024-12-01, it still has the
#[2018](https://webstore.ansi.org/standards/incits/incitsisoiec98992018r2024)
#standard available at 166.80 USD.

There are drafts for the C23 standard available as
[N3096](https://open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf) and
[N3220](https://open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf).
However, there are sections missing from both drafts compared to the
released C23 standard.

#The official standard has a new sub-section 5.1 Introduction which
#modifies the other references in section 5 (old 5.1 -> 5.2, etc).
#Similarly, there is a new section 6.5.1 General in the official standard
#and N3220, but not in N3096, which throws off the later section numbers.

EOF

