#!/bin/sh
#
# Flatten a string (probably a program) for embedding in an SO comment

# Not UUoC - tr is a pure filter
cat "$@" | tr -s '[:space:]' ' ' | sed 's/^ //; s/ $//'
echo
