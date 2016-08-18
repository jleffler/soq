#!/bin/sh

for file in $(seq -f 'moderately-long-file-name.%03.0f' 0 999)
do > "$file"
done
