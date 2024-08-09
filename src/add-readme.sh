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
    ofile="$dir.html"
    trap "rm -f '$ofile'; exit 1" 0 1 2 3 13 15
    qd=${dir#so-}
    qn=${qd/-/}
    wget -q -O "$ofile" "$site/questions/$qn"
    title=$(perl -lne 'print $1 if m/<title>(?:[^-]*? - )?(.+?) - [^-]*<\/title>.*/' "$ofile")
    echo "### Stack Overflow Question $qd"
    echo
    echo "[SO $qd]($site/q/$qn) &mdash;"
    echo "$title"
    rm -f "$ofile"
    ) > $dir/README.md
done
