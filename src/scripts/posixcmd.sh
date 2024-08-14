#!/bin/sh
#
# Echo URLs for POSIX commands

#baseurl="https://pubs.opengroup.org/onlinepubs/9699919799" # POSIX 2014

baseurl="https://pubs.opengroup.org/onlinepubs/9799919799" # POSIX 2024
bq='`'

for command in "$@"
do
    echo "[$bq$command$bq]($baseurl/utilities/$command.html)"
done
