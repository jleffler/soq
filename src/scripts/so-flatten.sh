#!/bin/sh
#
# Flatten a string (probably a program) for embedding in an SO comment

cat "$@" | tr -s '[:space:]' ' '
echo
