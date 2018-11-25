#!/bin/bash
#
# A light-weight study in using bash arrays
#
# Based on commentary answer to SO 2857-3599

or=""
args=()
for opt in "$@"
do
  args+=( $or -iname "*.$opt" )
  or="-o"
done
#printf "[%s]\n" "${args[@]}"
find . "${args[@]}"
