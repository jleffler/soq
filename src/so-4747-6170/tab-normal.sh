#!/bin/sh
#
# Trim leading and trailimg spaces; normalize internal spaces; delete comments

sed -e 's/^[[:space:]]\{1,\}//' \
    -e 's/[[:space:]]\{1,\}$//'  \
    -e 's/[[:space:]]\{1,\}/ /g'  \
    -e '/^#/d' \
    "$@"
