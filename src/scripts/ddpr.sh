#!/bin/bash
#
# Print a random double-digit prime

ddprimes=( 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 )
n_primes=${#ddprimes[@]}
prime_no=$(( $RANDOM % $n_primes ))
echo "${ddprimes[$prime_no]}"
