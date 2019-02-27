#!/usr/gnu/bin/bash-4.3
#
# SO 4685-9611 (https://stackoverflow.com/q/46859611)

declare -A domains2       # 2-part domains keyed by 3-part domains
declare -A domains3       # Count of occurrences of 3-part domains
min_count=4

${SED:-sed} -E -n -e '/.*(\.[-a-zA-Z0-9_]{1,}\.([-a-zA-Z0-9_]{1,}\.[-a-zA-Z0-9_]{1,}))$/ s//\1 \2/p' "$@" |
{
while read dom3 dom2
do
    #echo "$dom2   $dom3"
    domains2[$dom3]=$dom2
    ((domains3[$dom3]++))
done

declare -A results
for dom3 in "${!domains3[@]}"
do
    if [ "${domains3[$dom3]}" -gt "$min_count" ]
    then ((results[${domains2[$dom3]}]++))
    fi
done
printf '%s\n' "${!results[@]}" | sort
}

