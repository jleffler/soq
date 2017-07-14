#!/bin/bash
#
# Find official description of SO questions for README.md file

site="https://stackoverflow.com"

case "$#" in
(0) set -- so-*;;
esac

for dir in "$@"
do
    [ -h "$dir" ] && continue
    [ ! -d "$dir" ] && continue
    [ -f "$dir/README.md" ] && continue
    echo $dir
    (
    qd=${dir#so-}
    qn=${qd/-/}
    redirect=$(curl -s "$site/q/$qn" |
               perl -lne 'print $1 if m/.*Object moved to <a href="([^"]*)".*/')
    title=$(curl -s "$redirect" |
            perl -lne 'print $1 if m/<title>(?:[^-]*? - )?(.+?) - [^-]*<\/title>.*/')
    echo "### Stack Overflow Question $qd"
    echo
    echo "[SO $qd](https://stackoverflow.com/q/$qn) &mdash;"
    echo "$title"
    ) > $dir/README.md
done
