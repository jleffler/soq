### Stack Overflow Question 4341-8227

[SO 4341-8227](https://stackoverflow.com/q/43418227) &mdash;
CodeChef problem ROWSOLD

The problem description makes it easy to use a quadratic solution, but
on big data sets, that is far too slow.
After studying the behaviour on smallish (20-40 element) data sets, you
can find a linear solution, which is very fast even on the maximum size
problem sets.

* `cc97.c` — quadratic solution
* `cc17.c` — linear solution, official input format
* `cc19.c` — linear solution, not using official input format

The difference between 'official' and 'unofficial' input formats is that
the official format includes a count of the test cases as the first line
of data (somewhat pointlessly), while the unofficial format does not
include that first line with the number.

The code will be revised to print verbosely when commanded via `-v` on
the command line.

