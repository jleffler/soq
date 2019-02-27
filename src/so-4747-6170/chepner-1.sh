cat "${@}" |
while read -r line; do
    read -r _ col2 _ <<< "$line"
    prefix=${col2:0:3}
    # If the first column has a fixed width, you can forgo the previous two lines and use
    #   prefix=${line:12:3}
    printf '%s\n' "$line" >> split_DB/$prefix.part
done
