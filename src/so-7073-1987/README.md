### Stack Overflow Question 7073-1987

[SO 7073-1987](https://stackoverflow.com/q/70731987) &mdash;
Represent a tridiagonal sparse matrix in column major order

Summary
=======

You'll find that (indexing from 1), for an NxN tridiagonal matrix X
linearized in column-major order into an array Z, the entry in row r:

* On the main diagonal of X is at index (3 * c - 2) of Y for c = 1..N;
* On the upper-diagonal of X is at (3 * c - 3) of Y (for c = 1..N-1);
* On the lower-diagonal of X is at (3 * c - 1) of Y (for c = 2..N).

For an element with row r, column c (both in the range 1..N):

* if |r - c| > 1 then the value is zero;
* if c == r then it is on the leading diagonal;
* if c = r + 1 then it is on the upper diagonal;
* if c = r - 1 then it is on the lower diagonal.

Of course, in C, arrays are indexed from zero, not one.

Cogitations
===========

* NxN tri-diagonal matrix X
* Linearized in row-major order into array Y with `3*N-2` entries 
* Linearized in column-major order into array Z with `3*N-2` entries 
* Non-zero elements have c = r + { -1, 0, +1 }
* Equivalently they have r = c + { -1, 0, +1 }
* With one-based indexing, the first row with an element on the lower
  diagonal is r = 2 and the last row with an element on the upper
  diagonal is r = N - 1.
* With zero-based indexing, the first row with an element on the lower
  diagonal is r = 1 and the last rows with an element on the upper
  diagonal is r = N - 2.
* In the linearized vectors, the notation is:
  - D = diagonal, L = lower diagonal, U = upper diagonal

Row-Major Order with Zero-Based Indexing
========================================

    X   c = 0   1   2   3   4   5
          +----------------------
    r = 0 | 1   2   0   0   0   0
    r = 1 | 3   4   5   0   0   0
    r = 2 | 0   6   7   8   0   0
    r = 3 | 0   0   9  10  11   0
    r = 4 | 0   0   0  12  13  14
    r = 5 | 0   0   0   0  15  16

           D  U  L  D  U  L  D  U  L  D  U  L  D  U  L D
    Y = {  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 }
    Index  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15

* Elements on main  diagonal at indexes: 0, 3, 6, 9, 12, 15
* Elements on upper diagonal at indexes: 1, 4, 7, 10, 13
* Elements on lower diagonal at indexes: 2, 5, 8, 11, 14

Function `get_rm_0()`:

* `X[r,c] = 0         if |r - c| > 1`
* `X[r,c] = 3 * r + 0 if r == c + 0` — Main diagonal
* `X[r,c] = 3 * r + 1 if r == c - 1` — Upper diagonal
* `X[r,c] = 3 * r - 1 if r == c + 1` — Lower diagonal

Always subject to 0 <= r < N; 0 <= c < N

Row-Major Order with One-Based Indexing
=======================================

    X   c = 1   2   3   4   5   6
          +----------------------
    r = 1 | 1   2   0   0   0   0
    r = 2 | 3   4   5   0   0   0
    r = 3 | 0   6   7   8   0   0
    r = 4 | 0   0   9  10  11   0
    r = 5 | 0   0   0  12  13  14
    r = 6 | 0   0   0   0  15  16

           D  U  L  D  U  L  D  U  L  D  U  L  D  U  L D
    Y = {  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 }
    Index  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16

* Elements on main  diagonal at indexes: 1, 4, 7, 10, 13, 16
* Elements on upper diagonal at indexes: 2, 5, 8, 11, 14
* Elements on lower diagonal at indexes: 3, 6, 9, 12, 15

Function `get_rm_1()`:

* `X[r,c] = 0         if |r - c| > 1`
* `X[r,c] = 3 * r - 2 if r == c + 0` — Main diagonal
* `X[r,c] = 3 * r - 1 if r == c - 1` — Upper diagonal
* `X[r,c] = 3 * r - 3 if r == c + 1` — Lower diagonal

Always subject to 0 < r <= N; 0 <= c <= N

Column-major instead of row-major order
=======================================

>You are correct.  Here you are considering row-major order.  I
>wanted to store the elements in the array as:
>
> Z = { 1, 3, 2, 4, 6, 5, 7, 9, 8, 10, 12, 11, 13, 15, 14, 16 }
>
>as per your example

Column-Major Order with One-Based Indexing
==========================================

So, you can make a parallel argument to the one I gave.  Annotate
your column-major array Z similarly to the way I annotated the
row-major array Y:

           D   L   U   D   L   U   D   L   U   D   L   U   D   L   U   D
    Z = {  1,  3,  2,  4,  6,  5,  7,  9,  8, 10, 12, 11, 13, 15, 14, 16 }
    Index  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16

* Elements on main  diagonal at indexes: 1, 4, 7, 10, 13, 16
* Elements on upper diagonal at indexes: 3, 6, 9, 12, 15
* Elements on lower diagonal at indexes: 2, 5, 8, 11, 14

Function `get_cm_1()`:

* `X[r,c] = 0         if |c - r| > 1`
* `X[r,c] = 3 * c - 2 if c == r + 0` — Main diagonal
* `X[r,c] = 3 * c - 3 if c == r + 1` — Upper diagonal
* `X[r,c] = 3 * c - 1 if c == r - 1` — Lower diagonal

Always subject to 0 < r <= N; 0 < c <= N.

Column-Major Order with Zero-Based Indexing
===========================================

           D   L   U   D   L   U   D   L   U   D   L   U   D   L   U   D
    Z = {  1,  3,  2,  4,  6,  5,  7,  9,  8, 10, 12, 11, 13, 15, 14, 16 }
    Index  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15

* Elements on main  diagonal at indexes:  0,  3,  6,  9, 12, 15
* Elements on upper diagonal at indexes:  2,  5,  8, 11, 14
* Elements on lower diagonal at indexes:  1,  4,  7, 10, 13

Function `get_cm_0()`:

* `X[r,c] = 0         if |c - r| > 1`
* `X[r,c] = 3 * c + 0 if c == r + 0` — Main diagonal
* `X[r,c] = 3 * c - 1 if c == r + 1` — Upper diagonal
* `X[r,c] = 3 * c + 1 if c == r - 1` — Lower diagonal

Always subject to 0 <= r < N; 0 <= c < N.
