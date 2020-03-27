#!/bin/sh
#
# Echo URLs for POSIX commands

baseurl="https://pubs.opengroup.org/onlinepubs/9699919799"
bq='`'

for command in "$@"
do
    echo "[$bq$command$bq]($baseurl/utilities/$command.html)"
done
