#!/bin/sh
#
# Generate concentric arrays
# Complex version, starting from a random value in the range -10..+10 and
# incrementing by random amounts.

# POSIX awk defines that rand() returns a value [0,1)

seed=$(randseed -d)
echo "Seed: $seed" >&2
printf '%s\n' "$@" |
awk -v seed="$seed" '
    BEGIN { srand(seed) }
    function min(x, y) { return (x < y) ? x : y }
    function values(n,  i)
    {
        val[1] = int(rand() * 21) - 10;
        for (i = 2; i <= int((n + 1) / 2); i++)
            val[i] = val[i-1] + int(rand() * n + 1)
    }
    function print_row(n, p,      g, i)
    {
        g = n - 2 * p
        s = (g < 0) ? p - 1 : p
        for (i = 1; i <= p; i++) printf(" %d", val[i])
        for (i = 0; i <  g; i++) printf(" %d", val[p])
        for (i = s; i >  0; i--) printf(" %d", val[i])
        printf("\n")
    }
    {
        n = $0
        print n
        values(n)
        for (r = 1; r <= n; r++)
        {
            p = min(r, n - r + 1)
            print_row(n, p)
        }
    }'
