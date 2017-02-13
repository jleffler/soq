#!/bin/sh
#
# Echo URLs for POSIX functions

baseurl="http://pubs.opengroup.org/onlinepubs/9699919799"
bq='`'

for function in "$@"
do
    echo "[$bq$function()$bq]($baseurl/functions/$function.html)"
done
