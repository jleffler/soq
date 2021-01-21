#!/bin/sh
#
# Analog to WSO for SSCCE and MCVE (and HTAQTSW)

usestr="Usage: $(basename $0 .sh) [-hl]"
usage()
{
    echo "$usestr" >&2
    exit 1
}
help()
{
    echo "$usestr"
    echo
    echo "  -h  Print this help message and exit"
    echo "  -l  Print long form message (extra URLs)"
    echo
    exit 0
}

long=no
while getopts hl arg
do
    case "$arg" in
    (h) help;;
    (l) long=yes;;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
if [ $# != 0 ]
then usage
fi

echo 'MCVE ([Minimal, Complete, Verifiable Example](https://stackoverflow.com/help/mcve)'
echo ' — or MRE or whatever name SO now uses)'

# Verified http not https 2020-08-03
echo 'or an'
echo 'SSCCE ([Short, Self-Contained, Correct Example](http://sscce.org/))'
echo ' — the same idea by a different name'

if [ "$long" = "yes" ]
then
    # Verified http not https 2020-08-03
    echo 'See also'
    echo '[How to Ask Questions the Smart Way](http://www.catb.org/~esr/faqs/smart-questions.html)'
    #echo 'and [Writing the perfect question](http://tinyurl.com/stack-hints)'
    echo 'and [Writing the perfect question](https://codeblog.jonskeet.uk/2010/08/29/writing-the-perfect-question/)'
fi
