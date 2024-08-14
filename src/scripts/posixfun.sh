#!/bin/sh
#
# Echo URLs for POSIX functions

#baseurl="https://pubs.opengroup.org/onlinepubs/9699919799" # POSIX 2014

baseurl="https://pubs.opengroup.org/onlinepubs/9799919799" # POSIX 2024
bq='`'

for function in "$@"
do
    echo "[$bq$function()$bq]($baseurl/functions/$function.html)"
done
