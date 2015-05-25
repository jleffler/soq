#!/bin/bash
# SO 30428099

awk '
FNR == NR { 
    arr[$1,$2] = 1
    line[$1,$2] = line[$1,$2] (line[$1,$2] ? SUBSEP : "") $0
    next
}
FNR == 1 { delete found }
{ if (arr[$1,$2] && ! found[$1,$2]) { arr[$1,$2]++; found[$1,$2] = 1 } }
END { 
    num_files = ARGC -1 
    for (key in arr) {
        if (arr[key] < num_files) { continue }
        split(line[key], line_arr, SUBSEP)
        for (i = 1; i <= length(line_arr); i++) { 
            printf "%s\n", line_arr[i]
        } 
    } 
}
 ' "$@"
