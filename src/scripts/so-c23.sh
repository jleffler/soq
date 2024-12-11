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
    echo '  -l Print extra information (~1675 characters)'
    echo '  -s Print short information (~550 characters; default)'
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
published in late October 2024.
# It costs 216 CHF (about 258 USD).

#It is available from the [ANSI Web
#Store](https://webstore.ansi.org/standards/iso/isoiec98992024)
#at 278 USD.

#As of 2024-12-01, it still has the
#[2018](https://webstore.ansi.org/standards/incits/incitsisoiec98992018r2024)
#standard available at 166.80 USD.

Multiple drafts for the C standard are available from the Open
Standards site of the C working group (JTC1/SC22/WG14).

#The draft
#[N3096](https://open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf) from
#2023-04-02.

The draft
[N3220](https://open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf) from
2024-02-22.

However,
# both N3096 and
N3220 have sections missing compared to the released C23 standard.

The draft
[N3229](https://open-std.org/jtc1/sc22/wg14/www/docs/n3299.pdf) from
2024-07-28 is very close to the final standard and has the
correct section numbers.

#The draft
#[N3301](https://open-std.org/jtc1/sc22/wg14/www/docs/n3301.pdf), also
#from 2024-07-28, has some of the first changes for C2Y.

#The official standard has a new sub-section 5.1 Introduction which
#modifies the other references in section 5 (old 5.1 -> 5.2, etc).
#Compared with N3220, the official standard also has new sub-sections
#6.3.1, 6.4.1, 7.6.1, 7.8.1, 7.11.1, 7.12.1, 7.13.1, 7.14.1, 7.16.1,
#7.20.1, 7.21.1, 7.22.1, 7.24.1, 7.30.1, 7.31.4.1, 7.31.6.1, 7.33.1.
#Compared with N3096, the official standard also has new sub-sections
#5.1, 5.2.2, 6.3.1, 6.4.1, 6.5.1, 6.7.1, 6.8.1, 6.9.1, 6.10.1, 7.2.1,
#7.6.1, 7.8.1, 7.11.1, 7.12.1, 7.13.1, 7.14.1, 7.16.1, 7.20.1, 7.21.1,
#7.22.1, 7.24.1, 7.30.1, 7.31.4.1, 7.31.6.1, 7.33.1

EOF

