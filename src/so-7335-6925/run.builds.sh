#!/bin/sh
#
# Run sequence of compilations

set -x
rm -f gcc23
make CC=gcc "$@"
rm -f gcc23
make CC=clang "$@"
rm -f gcc23
make CC=clang UFLAGS=-Weverything "$@"
