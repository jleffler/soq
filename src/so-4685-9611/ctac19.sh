#!/bin/sh
#
# SO 4685-9611
#
# Fourth suggested version from ctac_
# https://stackoverflow.com/users/8592975/ctac

awk -F. 'NF>2{if (s[$(NF-2)FS$(NF-1)FS$(NF)]++>2){t[$(NF-1)FS$(NF)]}}END{for(i in t) print i}' "$@"
