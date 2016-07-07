#!/bin/bash

set -o pipefail
(
"$@" 2>&1 1>&3 |
sed '/^In file /,/^ *^/d' >&2
) 3>&1
