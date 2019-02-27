so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) min[$2] = $1 } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }'
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) min[$2] = $1 } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }' | sort -k2n
so-4673-6148C | sort -k2n,2 -k1n,1 | awk '{ if (count[$2]++ == 0) min[$2] = $1 } END { for (i in min) printf "Start: %.4d - length %4d\n", min[i], count[min[i]] }' | total -c 2
