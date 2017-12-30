sed 's/^[^ ]*  \(...\)/\1 &/' "$@" |
while read key line
do
    echo "$line" >> split_DB/$key.part
done
