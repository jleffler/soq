#!/bin/sh
#
# Standard spiel about searching for primes in a range

exec cat <<'EOF'
Note that you don't need to search up to N-1; up to and including
`ceil(sqrt(N))` is sufficient.
If N is composite, then one factor is not larger than √N and the other
is not smaller than √N).
After you've checked for 'divisible by 2', you could check only the odd
numbers.
If you check for 'divisible by 3' outside the loop, then all bigger
primes have the form 6K±1 for an integer K starting at K equal to 1.
Limiting the search range gives a radical speedup even when N is just in
the thousands, let alone much bigger.
Using 'odds only' does 1/2 the work; using 6K±1 does 1/3.

If the range to be searched is big enough (the maximum value is large
enough), building a Sieve of Eratosthenes (or even more advanced
techniques — such as Sieve of Atkin) for the primes up to the square
root of the maximum and then testing only the 'known to be prime'
possible factors can be beneficial.

Eventually, deterministic evaluation of 'is it a prime' becomes too slow
and you resort to probabilistic prime detection such as the Miller-Rabin
test.

See Wikipedia on [Primality
test](https://en.wikipedia.org/wiki/Primality_test).

EOF
