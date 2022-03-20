#!/bin/sh
#
# Blurb for a comment to an SQL question that does not specify table names

exec tr -s ' \n' ' ' <<'EOF'
Note that you do not specify the data table names — a surprisingly
common oversight in SQL questions.
If you don't specify the table names, everyone who answers has to make
up their own table names, which makes life harder than need be for
people answering.
Please also read the guidelines under the [tag:sql] tag
[wiki](https://stackoverflow.com/tags/sql/info).
EOF
echo ''
