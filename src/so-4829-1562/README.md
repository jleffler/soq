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

The initial version of the code is reasonably but not completely
factored.
There should be separate functions to initialize the upper-triangular
and lower-triangular arrays that identify which row and column value
corresponds to entry N in the sorting process.

