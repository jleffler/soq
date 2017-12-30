cat "$@" |
while read line
do
    PREFIX=$(echo "$line" | cut -f2 | cut -c1-3)
    echo -e "$line" >> split_DB/$PREFIX.part
done
