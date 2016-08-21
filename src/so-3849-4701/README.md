## [SO 3849-4701](http://stackoverflow.com/q/38494701) Joining multiple files

The question asks about joining three files which can be done
non-iteratively - hence three-file-solution.sh.

The original multiple-file solution used random v6.11 but had to dink
around with the names file for lack of the feature in random v6.12 for
`-T '%{N1,N2,N3,N4}S'` to select from a list of names.

The solutions also use a fixed number of entries in each file for lack
of the `-N lo:hi` feature added in random v6.13.

This question and processing also triggered the addition of `-t` support
to `commalist` (and the test suite, and hence separation into a new
source directory since it is no longer a single-file program).
This came about from trying to use:

    random -T '%{$(colnum -c2 names | commalist)S' ...

The problem was that the trailing comma generated by `commalist`
triggered an empty name from random.

So, while the question is not of great significance by some standards
(there are other SO questions that deal with joining multiple files), it
is interesting because it triggered so much activity in the supporting
toolset.