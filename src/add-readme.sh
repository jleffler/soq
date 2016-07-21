#!/bin/bash
#
# Find official description of SO questions for README.md file

site="http://stackoverflow.com"
for dir in so-*
do
    [ -h "$dir" ] && continue;
    [ -f "$dir/README.md" ] && continue;
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
    echo "[SO $qd](http://stackoverflow.com/q/$qn) &mdash;"
    echo "$title"
    ) > $dir/README.md
done
