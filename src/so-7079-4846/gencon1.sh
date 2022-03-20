#!/bin/sh
#
# Generate concentric arrays
# Simple version, counting from 1 and increasing by one for each shell

printf '%s\n' "$@" |
awk '
    function min(x, y) { return (x < y) ? x : y }
    function print_row(n, p,      g, i)
    {
        g = n - 2 * p
        s = (g < 0) ? p - 1 : p
        for (i = 1; i <= p; i++) printf(" %d", i)
        for (i = 0; i <  g; i++) printf(" %d", p)
        for (i = s; i >  0; i--) printf(" %d", i)
        printf("\n")
    }
    {
        n = $0
        print n
        for (r = 1; r <= n; r++)
        {
            p = min(r, n - r + 1)
            print_row(n, p)
        }
    }'
