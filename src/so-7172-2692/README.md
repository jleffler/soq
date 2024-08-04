### Stack Overflow Question 7172-2692

[SO 7172-2692](https://stackoverflow.com/q/71722692) &mdash;
I am trying to shuffle my deck but it is displaying it unshuffled again

The code in `shuffle19.c` fixes the OP's problem.

The code in `checkrand.c` attempts, sort of, to find bias in the naive
random algorithms.  I'm not convinced it succeeds, though the results
are usually different between the biassed and unbiassed PRNG code, using
the same seed for each.  It is not presented on SO.
