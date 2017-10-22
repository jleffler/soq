#!/bin/sh
#
# SO 4685-9611
#
# First suggested version from ctac_
# https://stackoverflow.com/users/8592975/ctac

awk -F. 'NF>=3{seen[$(NF-1)"."$(NF)]++}END{for(i in seen)if(seen[i]>2)print i}' "$@"
