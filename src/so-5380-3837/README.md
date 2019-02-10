### Stack Overflow Question 5380-3837

[SO 5380-3837](https://stackoverflow.com/q/53803837) &mdash;
Sorting 2D array in C

The 2D array has 6 columns (called a, b, c, n, m, v in the question).
The data is to be sorted on the values in column n, and in case of ties
on the values in column m.

The original code in the question seemed to work — at least when edited
to become `sort31.c`.

The code in `sort89.c` uses a simpler copy function than the inordinately
complex `copyTripleToArray()` function, but the sort function still
accesses a global array.

The code in `sort67.c` passes the array to the sort function, as well as
its size.

