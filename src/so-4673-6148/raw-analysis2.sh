# Record of statements executed.
# It is no longer clear which ones are really beneficial

so-4673-6148C | sort -k2n,2 -k1n,1 | less
*so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{count[$2]++}END{for (i in count) printf("%.4d %.4d\n", i, count[i])}' | sort -k2n,2 -k1n,1 | total -c 2
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '$1 !~ /^[0-9]/{next}{count[$2]++}END{for (i in count) printf("%.4d %.4d\n", i, count[i])}'
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '$1 !~ /^[0-9]/{next}{count[$2]++}END{for (i in count) printf("%.4d %.4d\n", i, count[i])}' | sort -k2n,2 -k1n,1
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '$1 !~ /^[0-9]/{next}{count[$2]++}END{for (i in count) printf("%.4d %.4d\n", i, count[i])}' | sort -n
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '$1 !~ /^[0-9]/{next}{count[$2]++}END{for (i in count) printf("%.4d %.4d\n", i, count[i]}'
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) min[$2] = $1 } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }'
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) min[$2] = $1 } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }' | sort -k2n
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) { min[$2] = $1; print $0 } } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }'
