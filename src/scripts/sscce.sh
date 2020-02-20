#!/bin/sh
#
# Analog to WSO for SSCCE and MCVE (and HTAQTSW)

usage()
{
    echo "Usage: $(basename $0 .sh) [-l]" >&2
    exit 1
}

long=no
while getopts l arg
do
    case "$arg" in
    (l) long=yes;;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))
if [ $# != 0 ]
then usage
fi

echo 'MCVE ([Minimal, Complete, Verifiable Example](https://stackoverflow.com/help/mcve))'
echo '(or MRE or whatever name SO now uses)'

# Verified http not https 2019-05-15
echo 'or an'
echo 'SSCCE ([Short, Self-Contained, Correct Example](http://sscce.org/)).'

if [ "$long" = "yes" ]
then
    # Verified http not https 2019-05-15
    echo 'See also'
    echo '[How to Ask Questions the Smart Way](http://www.catb.org/~esr/faqs/smart-questions.html)'
    #echo 'and [Writing the perfect question](http://tinyurl.com/stack-hints)'
    echo 'and [Writing the perfect question](https://codeblog.jonskeet.uk/2010/08/29/writing-the-perfect-question/)'
fi
