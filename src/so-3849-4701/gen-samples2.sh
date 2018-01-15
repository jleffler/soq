#!/bin/bash
#
# SO 3849-4701

# NB: The sort ensures a given name only appears once in a sample file,
#     which is rather important (to avoid cartesian products when joining).
#     The shuffle re-randomizes that which sort sorted.

names=$(colnum -c2 names | commalist -s '' -t -)
for sample in $(range -f '%02d' 1 10)
do
    random -n 9 -T "%{$names}S	%[11:90]d	%{BG}s" |
    sort -u -k1,1 |
    shuffle > "sample-$sample.file"
done
