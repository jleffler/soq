### Stack Overflow Question 4829-1562

[SO 4829-1562](https://stackoverflow.com/q/48291562) &mdash;
Sorting 2d array (matrix) in c

The sort requirements are unusual:

* Enter a square matrix of dimensions n .
* Elements below main diagonal sort in ascending order.
* Elements above main diagonal sort in descending order.
* Elements on main diagonal sort :
  * first even numbers in ascending order.
  * then odd numbers in descending order.

UT (or ut) designates the upper triangular sub-matrix.
LT (or lt) designates the lower triangular sub-matrix.

The key algorithmic step is finding a way to convert a list of index
numbers into the row and column values for the cells in the triangle
that is being sorted.
The `init_ut_map()` and `init_lt_map()` functions, combined with C99 VLA
(variable length array) technology makes that feasible, at least until
the arrays get too big.
It would be possible to replace the VLA with dynamically allocated
memory, of course.

After creating code to work with `qsort()`, there is no real need to
store the UT and LT maps.
Originally, they were used many times during the sorting, but with the
copy-sort-copy mechanism, it is as easy to do without the non-negligible
overhead of the arrays, as they are used once to copy out and once to
copy in, and each entry is used just once during each copy cycle.

### Code breakdown

* `sort2d-37.c`

  Variation 2: Use system `qsort()`.
  This code prototypes the copy-sort-copy mechanism, but has too much
  repetition that can be removed by judicious use of function pointers.

* `sort2d-53.c`

  Variation 1: Using direct sorting of triangles of matrix without
  copying.
  Timing tests show that this is very slow.
  Part of the overhead is that the sort is a simple-minded quadratic
  sort.
  Another major part of the overhead is computing the matrix indexes on
  the fly, even with the UT and LT lookup matrices to map from [0..N) to
  (r,c) pairs.

* `sort2d-59.c`

  Variation 3: Use system `qsort()` and common code to coordinate
  sorting of triangles.
  This code makes use of function pointers to extract and sort.
  It is more compact, therefore, than `sort2d-37.c`.

### Timing framework

* `time.sort2d-31.c`

  Implements a basic timing framework, generating N copies of a random
  matrix of different sizes so that the N different sort algorithms each
  get a copy of the same matrix to sort.
  It doesn't print the matrices by default; the 100x100 matrices are
  boring.
  It does check that the sorted results agree with each other.
  It does not verify that the results are also correct.

* `time.sort2d-31.h`

  Declares the N (currently 3) sorting algorithms.

* `time.sort2d-79.c`

  Implements `quick_sort()` which uses the system `qsort()` function.
  It is closely based on `sort2d-59.c`, implementing variation 3.

  Superseded by `time.sort2d-97.c`.

* `time.sort2d-83.c`

  Implements `basic_sort()` which sorts the triangular matrices in situ.
  It is closely based on `sort2d-53.c`, implementing variation 1.

* `time.sort2d-89.c`

  Implements `clean_sort()` which does copy-sort-copy using a basic
  quadratic sort.
  It is measurably faster than `basic_sort()`, and its advantage grows
  as the problem size grows, but the performance is still dreadful by
  comparison with the quick sort version.

* `time.sort2d-97.c`

  Derived from `time.sort2d-79.c`, but does not create the UT or LT
  mapping matrices since the information is only used twice — once to
  copy the data from the matrix to the vector that will be sorted, and
  once to copy the data from the sorted vector back to the matrix.
  When first used, the array was used during every comparison of the
  sort — it served an important purpose — but with the copy-sort-copy
  technique, it became unnecessary overhead.

  The code is neatly spartan now.
  The use of the tiny copier functions (which can't be inline because
  they're passed as function pointers) means that the triangular copying
  function can copy in either direction.

### Modified code submitted by OP on 2018-02-02

* `sort2d-mk2-67.c`

  This is the OPs modified code from the question reformatted and with
  void added to specify "int main(void)".

  It fails to sort properly for some cases of both the upper triangle
  and the lower triangle.

* `sort2d-mk2-73.c`

  This is the debugged and bug-fixed version of the OPs modified code.
  The original code is annotated with "`// OP`" after the comment; bug
  fix amendations are annotated with "`// JL`" after the code.
  The `printf()` statements were crucial to seeing the problem.

  In the lower triangle, when loops got to the third or fourth row, the
  first entries in the row were ignored, which meant they could be out
  of position.
  The fix is to start the current row at (it could be after) the current
  position, but for subsequent rows, to start the row scan at index 0.
  The variable `s` allows this to happen.

  The analogous problem existed in the upper triangle, compounded by
  making comparisons with elements not in the upper triangle.
  The `&& m < b` condition on the swap protected the swapping.
  Again, the variable `s` fixes the problem.
  Using `s = m + 2;` before `m` is incremented sets the start position
  to the same position as `m + 1` after `m` is incremented.

TBD: Add the amended code to the timing framework.

