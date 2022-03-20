### Stack Overflow Question 7085-8579

[SO 7085-8579](https://stackoverflow.com/q/70858579) &mdash;
Find maximum and minimum nondiagonal elements of matrix

### Answer on SO

The matrix must be at least a 3x3 matrix to have off-diagonal elements.
If you have an NxN matrix, then (using `r` for row and `c` for column)
the diagonals have `r == c` and `r == N - c - 1` (aka `r + c == N - 1`).
You can simply ignore elements for which either of those conditions is
true.

You must place the other elements into one of the four quadrants aligned
with the diagonals.  The triangle at the top is the N (north) quadrant;
at the bottom is the S (south) quadrant; at the left is the W (west)
quadrant; at the right is the E (east) quadrant.

     N=5                      N=4
     r\c 0  1  2  3  4        r\c 0  1  2  3
      0  .  N  N  N  .         0  .  N  N  .
      1  W  .  N  .  E         1  W  .  .  E
      2  W  W  .  E  E         2  W  .  .  E
      3  W  .  S  .  E         3  .  S  S  .
      4  .  S  S  S  .

The dots represent the diagonals.  In the 5x5 matrix, the W and S
elements satisfy `r > c`; the N and E elements satisfy `r < c` (and the
elements on the diagonal satisfy `r == c`).  Similarly, the W and N
elements satisfy `r + c < N - 1` while the S and E elements satisfy `r +
c > N -1` (and the elements on the diagonal satisfy `r + c == N - 1`).
The 4x4 matrix also satisfies these conditions.

You can then use these conditions to classify a given (row, column) pair
into one of the four quadrants using an encoding scheme similar to that
suggested by [Dèja
vu](https://stackoverflow.com/users/338904/d%c3%a9j%c3%a0-vu) in a
[comment](https://stackoverflow.com/questions/70858579/find-maximum-and-minimum-nondiagonal-elements-of-matrix#comment125266675_70858579),
but adjusted to use different conditions:

    int quadrant = ((r < c) ? 0 : 1) + ((r + c < N - 1) ? 0 : 2);

When `quadrant` is 0, it corresponds to the N quadrant; when it is 1, to
the W quadrant; when it is 2, to the E quadrant; when it is 3, to the S
quadrant.  Note that this condition assumes that the diagonal elements
are not tested.  You might write `assert(r != c && r + c != N - 1);` to
ensure that it is not invoked for an element on the diagonals.

You can then compare the element `mat[r][c]` with `min[quadrant]` and
`max[quadrant]`, which is the scheme outlined by
[kaylum](https://stackoverflow.com/users/3003365/kaylum) in a
[comment](https://stackoverflow.com/questions/70858579/find-maximum-and-minimum-nondiagonal-elements-of-matrix#comment125266632_70858579).

### `matminmax37.c`

Program which implements the solution outlined in the answer, with tests
cases for matrices 3x3, 4x4, 5x5, 6x6, 7x7, 12x12 and 13x13.  Those
matrices were generated at random using `gen_matrix` which in turn uses
`commalist`.  Contact me for the code.
