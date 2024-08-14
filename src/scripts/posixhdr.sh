#!/bin/sh
#
# Echo URLs for POSIX headers

#baseurl="https://pubs.opengroup.org/onlinepubs/9699919799" # POSIX 2014

baseurl="https://pubs.opengroup.org/onlinepubs/9799919799" # POSIX 2024
bq='`'

for header in "$@"
do
    mapped="$(echo "$header" | sed 's%/%_%; s/[<>"]//g')"
    echo "[$bq<$header>$bq]($baseurl/basedefs/$mapped.html)"
done
