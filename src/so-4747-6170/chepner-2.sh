cat "${@}" |
while read -r line; do
    prefix=${line: 12: 3}
    printf '%s\n' "$line" >> split_DB/$prefix.part
done
