#!/bin/sh
#
# Check the output of pp97 - prime pair candidate generator.
#
# Note that pp97 generates possible prime pairs.  Some of the possible
# pairs are not prime pairs (the first such not-prime pair is 47..49;
# the next is 77..79).  However, pp97 does not miss any prime pairs.
#
# The difference output contains line numbers and the < lines from extra
# (non-prime pairs) from pp97.out.  The number lines are removed, and
# the < marks removed.  The .. markers separating pairs are converted to
# newlines, and the list of numbers factorized.
# 77:    7.11           # Lower is composite
# 79:    79
# 89:    89
# 91:    7.13           # Upper is composite
# 119:    7.17          # Both lower and upper are composite
# 121:    (11^2)
# The awk script then processes pairs of lines such as the 77-79 lines,
# checking that the numbers are 2 apart and whether there is a single
# number as the 'factor' of each number - so they are both prime.
# Consequently, if the output from pp97 includes all the actual prime
# pairs, there is no output from this script (a whole lot of work for no
# output).

diff pp97.out prime.pairs.1000000 |
sed -e '/^[0-9]/d; s/< //;' |
tr -s '.' '\n' |
xargs factor |
awk -F'[:[:space:]]+' \
   'NR % 2 == 1 { old_num = $1; old_factors = $2 }
    NR % 2 == 0 { new_num = $1; new_factors = $2;
                    #print "Check: ", old_num, old_factors, new_num, new_factors
                    if (new_num - old_num != 2)
                    {
                        #print new_num, old_num
                        printf("Oops: (%d,%s) vs (%d,%s)\n", old_num, old_factors, new_num, new_factors)
                    }
                    else if (old_factors ~ /^[0-9]+$/ && new_factors ~ /^[0-9]+$/)
                        printf("Pair: (%d,%s) vs (%d,%s)\n", old_num, old_factors, new_num, new_factors)
                }'
