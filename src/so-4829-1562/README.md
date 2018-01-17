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

The key algorithmic step is finding a way to convert a list of index
numbers into the row and column values for the cells in the triangle
that is being sorted.
The `init_ut_map()` and `init_lt_map()` functions, combined with C99 VLA
(variable length array technology makes that feasible.
It would be possible to replace the VLA with dynamically allocated
memory, of course.


Next step: work with `qsort_r()` to get the data sorted with a standard
quicksort.
It will be interesting to instrument the speed of `qsort_r()` against
the admittedly primitive O(N^2) sorts used at the moment.
