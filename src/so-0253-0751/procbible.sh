sed -e '1,/ *bmcgin@patriot.net *$/d' \
    -e 's/^[0-9][0-9][0-9]:[0-9][0-9][0-9]//' \
    -e '/Book [0-9][0-9]*	/d' \
    -e '/<></,$d' \
    bible12.txt |
tr -d '()?!.,:;' |
tr -s ' ' '\n' |
sort |
uniq -c |
sort -n
