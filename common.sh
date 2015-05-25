#!/bin/bash
# SO 30428099

# Given that the key for a line is the first two columns, this script
# lists all appearances in all files of a given key if that key appears
# in N different files (where N defaults to the number of files). For
# the benefit of debugging, it includes the file name with each line.

usage()
{
    echo "Usage: $(basename "$0" .sh) [-n number] file [...]" >&2
    exit 1
}

while getopts n: opt
do
    case "$opt" in
    (n) num_files=$OPTARG;;
    (*) usage;;
    esac
done

shift $(($OPTIND - 1))

if [ "$#" = 0 ]
then usage
fi

# Record count of each key, regardless of file: keys
# Record count of each key in each file: key_file
# Count of different files containing each key: files
# Accumulate line number, filename, line for each key: lines

awk -v num_files=${num_files:-$#} '
{ 
    keys[$1,$2]++;
    if (++key_file[$1,$2,FILENAME] == 1)
        files[$1,$2]++
    #printf "%s:%d: Key (%s,%s); keys = %d; key_file = %d; files = %d\n",
    #        FILENAME, FNR, $1, $2, keys[$1,$2], key_file[$1,$2,FILENAME], files[$1,$2];
    sep = lines[$1,$2] ? RS : ""
    #printf "B: [[\n%s\n]]\n", lines[$1,$2]
    lines[$1,$2] = lines[$1,$2] sep FILENAME OFS FNR OFS $0
    #printf "A: [[\n%s\n]]\n", lines[$1,$2]
}
END {
    #print "END"
    for (key in files)
    {
        #print "Key =", key, "; files =", files[key]
        if (files[key] == num_files)
        {
            #printf "TAG\n%s\nEND\n", lines[key]
            print lines[key]
        }
    }
}
' "$@"
