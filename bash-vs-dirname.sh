doit() {
    strings=( "[[$1]]"
              "[[$(basename "$1")]]"
              $( [ "$(basename "$1")" = "${1##*/}" ] && echo "==" || echo "!=" )
              "[[${1##*/}]]"
              "[[$(dirname "$1")]]"
              $( [ "$(dirname "$1")" = "${1%/*}" ] && echo "==" || echo "!=" )
              "[[${1%/*}]]"
            )
    printf "%-15s %15s %2s %-15s %15s %2s %-15s\n" "${strings[@]}"
}

printf "%-15s %15s %2s %-15s %15s %2s %-15s\n" \
    'file' 'basename $file' '' '${file##*/}' 'dirname $file' '' '${file%/*}'

doit /aaa/bbb/
doit /
doit /aaa
doit aaa
doit aaa/
doit aaa/xxx
doit aaa//
