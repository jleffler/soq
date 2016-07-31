#!/bin/bash
#
# SO 38494701

names=$(colnum -c2 names | commalist -s '' -t -)
for sample in $(range -f '%02d' 1 10)
do
    random -n 9 -T "%{$names}S	%[11:90]d	%{BG}s" > "sample-$sample.file"
done
