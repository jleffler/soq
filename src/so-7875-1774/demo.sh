#!/bin/sh

source=cmplx67

clean()
{
    rm -fr $source $source.o $source.dSYM
}

set -x
clean
ls -l
clang -o $source $source.c
ls -l
clean
clang -g -o $source $source.c
ls -l
clean
clang -g -c $source.c
clang -g -o $source $source.o
ls -l
clean
clang -g -c $source.c
clang -g -o $source $source.o -dsym-dir $source.dSYM
ls -l
clean
