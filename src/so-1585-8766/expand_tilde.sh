#!/bin/bash
#
# SO 15858766 - Tilde expansion in quotes
# http://stackoverflow.com/questions/15858766
#
# Working function - painful, but can you simplify any of it?
# NB: Assumes that ~user does not expand to a name with double spaces or
#     tabs or newlines, etc.

expand_tilde()
{
    case "$1" in
    (\~)        echo "$HOME";;
    (\~/*)      echo "$HOME/${1#\~/}";;
    (\~[^/]*/*) local user=$(eval echo ${1%%/*})
                echo "$user/${1#*/}";;
    (\~[^/]*)   eval echo ${1};;
    (*)         echo "$1";;
    esac
}

# Test cases

name1="~/Documents/over  enthusiastic"
name2="~crl/Documents/double  spaced"
name3="/work/whiffle/two  spaces  are  better  than one"

expand_tilde "$name1"
expand_tilde "$name2"
expand_tilde "$name3"
expand_tilde "~"
expand_tilde "~/"
expand_tilde "~crl"
expand_tilde "~crl/"

x=$(expand_tilde "$name1")
echo "x=[$x]"
