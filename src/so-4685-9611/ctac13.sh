#!/bin/sh
#
# SO 4685-9611
#
# Second suggested version from ctac_
# https://stackoverflow.com/users/8592975/ctac

awk -F. 'NF>2{s[$(NF-2)FS$(NF-1)FS$(NF)]++}END{for(i in s)if(s[i]>2){sub("[^.]*.","",i);print i}}' "$@"
