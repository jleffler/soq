#!/bin/bash
# SO 30428099

while getopts n: opt
do
    case "$opt" in
    (n) num_files=$OPTARG;;
    (*) echo "Usage: $(basename "$0" .sh) [-n number] file [...]" >&2
        exit 1;;
    esac
done

shift $(($OPTIND - 1))

awk -v num_files=${num_files:-$#} '
FNR == NR { 
    arr[$1,$2] = 1
    line[$1,$2] = line[$1,$2] (line[$1,$2] ? SUBSEP : "") $0
    next
}
FNR == 1 { delete found }
{ if (arr[$1,$2] && ! found[$1,$2]) { arr[$1,$2]++; found[$1,$2] = 1 } }
END { 
    if (num_files == 0) num_files = ARGC - 1
    for (key in arr) {
        if (arr[key] == num_files) {
            split(line[key], line_arr, SUBSEP)
            for (i = 1; i <= length(line_arr); i++) {
                printf "%s\n", line_arr[i]
            }
        }
    }
}
' "$@"
