#!/bin/sh

for sample in $(range -f '%02d' 1 10)
do
    random -n 9 -T '%{ABCDEFJKMPS}s %[11:90]d   %{BG}s' |
    sort -u -k1,1 |
    join -o 1.2,2.2,2.3 names - |
    shuffle |
    sed 's/ /   /g' |
    perturb -f '%2.0f' -p 10 -c 2 > "sample$sample.file"
done
