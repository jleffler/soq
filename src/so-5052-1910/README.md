## Stack Overflow Question 5052-1910

[SO 5052-1910](https://stackoverflow.com/q/50521910) &mdash;
Find max and min in an efficient way

The data structure is curiously laid out, which allows some unusual
opportunities for optimization.

Data structure for the array has: 

* count of ranges, N;
* N * 2 integers, low and high;
* plus any left-overs as individual values.

This means that the code doesn't have to check the low values against
the maxima or the high values against the minima.

### `mnmx79.c`

  Minor extension to `mnmx47.c` with added assertions and a couple more
  test cases pushing the extrema.  This is the code used in my answer.

