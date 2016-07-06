### Three-star and four-star programming is not recommended!

This code uses `char ***` (`3-star.c`) and `char ****` (`4-star.c`), but
the latter in particular is not to be recommended.  The code implements
the allocation of a 2D array of strings.

### How did this get here?

For better or worse, the code in these source files exists on branch
so/19782086.

The branch was cleaned of most extraneous material, so merging the
branch back into the main-stream did not work easily (there were many
conflicts).  To avoid the problem, the files were copied from the
top-level directory into this sub-directory, then the sphinx/reorg.003
branch added the files, and they should merge into master from there
without problem.
