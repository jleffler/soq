## Matrices in C

These are assorted answers to questions about matrix handling in C.
It would not be surprising to find that there are other answers in the
src/so-abcd-wxyz directories that should be here too.

NB: In this directory, the term matrix is used to describe both arrays
of pointers (to arrays of pointers (to ...)) to elements, and also to
simple blocks of elements.
Both are accessed using the multiple square bracket notation &mdash; the
underlying access mechanics are different, though.

### [SO 1719-2011](https://stackoverflow.com/q/17192011)

* `matmul89.c` &mdash; variable-dimension 2D array multiplication in strict C89.
* `matmul99.c` &mdash; variable-dimension 2D array multiplication in C99 using VLA.

These programs show the difference between coding in C89 and C99 for
variable size arrays.
The C89 code uses a simple pointer to `float` and explicitly computes
the subscript corresponding to a given row and column number.
The C99 code simply uses the row and column subscripts.

### [SO 1857-9583](https://stackoverflow.com/q/18579583)

There are multiple answers for the question.
The crux seems to be about handling recovery from memory allocation
failure.

* `3dalloc1.c` &mdash; Minimal fix, leaking memory, but not crashing.
* `3dalloc2.c` &mdash; Better fix, releasing most memory if allocation fails
    part way through.  Definitely has a leak though.
* `3dalloc3.c` &mdash; Reworked variant of `3dalloc3.c` with proper (simpler) memory allocation.
* `3dalloc4.c` &mdash; Dramatically reduced memory allocations, dramatically simplifying recovery.
* `matmake3d.c` &mdash; Another crack at this issue.
    Not sure about its relation to the `3dalloc?.c` code.

### [SO 2881-8521](https://stackoverflow.com/q/28818521)

* `alloc3dmat.c` &mdash; Allocate a 3D matrix in a single memory allocation.

  The code makes some mostly excusable (though not strictly justifiable)
  assumptions about alignment requirements, namely that pointers are as
  stringently aligned as type `double`.  Fixing that would not be all that
  easy, though neither would it be impossible.

### [SO 2635-0717](https://stackoverflow.com/q/26350717)

* `2da.c` &mdash; memory allocation for a 2D array of arrays with negative indices.

This code allocates an array and then adjusts things so that it is legitimate to
use negative indexes into the array.

### [SO 3256-5694](https://stackoverflow.com/q/32565694)

* `vlastruct.c` &mdash; another variable-dimension 2D array multiplication in C99 using VLA. 

### [SO 3259-8224](https://stackoverflow.com/q/32598224)

* `vlamat.c` &mdash; and another variable-dimension 2D array multiplication in C99 using VLA.

This code accepts 3 command line arguments, all of which must be numbers
in the range 1..99.
These control the size of the arrays worked with.
If the arguments are N1, N2, N3, then the size of the first matrix is
N1xN2, the size of the second is N2xN3, and the size of the result
(obviously) is N1xN3.
With any other number of arguments, the code runs with N1 = 3, N2 = 5,
N3 = 4.

### `mda.c`

The code in `mda.c` is not operational (it crashes).
It's an attempt to code up arbitrary dimensional arrays (e.g. 3D or 4D
or 5D) using a single structure, though there are numerous issues still
to resolve.

### [SO 5428-2732](https://stackoverflow.com/q/54282732)

* `alloc2dvla47.c` &mdash; yet another 2D VLA allocation.

### [SO 4885-6272](https://stackoverflow.com/q/48856272)

* `alloc2d19.c` — dynamic allocation of 2D array of arbitrary type
* `alloc3d79.c` — dynamic allocation of 3D array of arbitrary type

These programs exhibit 3-star and 4-star program.
What's good for generals is not, in general, good for programmers.

### `vla17.c`, `vla53.c`, `vla67.c`

* Nominally demonstrating the use of "\*" as a placeholder for VLA
  sizes in a function prototype.
* As of 2022-06-23, these do not compile with GCC 11.2.0.
* These compiled OK with GCC 8.3.0 (version compiled in March 2019).
* Investigation discovered that GCC 11 added the `-Warray-parameter` and
  `-Wvla-parameter` options, now included in `-Wall`.
* See https://gcc.gnu.org/gcc-11/changes.html
* The change is basically saying "parts of the C standard relating to
  VLAs do not make sense".
* Whether that's fully justified or not is debatable.
* However, I'd never been tempted to actually use the "\*" notation
  other than in these vignettes.
* A sample error is:

        vla67.c:8:83: error: argument 6 of type ‘int[*][0]’ declared with 2 unspecified variable bounds [-Werror=vla-parameter]
            8 | static void mat_multiply(int x, int y, int z, int mat1[*][*], int mat2[*][*], int result[*][*]);
              |                                                                               ~~~~^~~~~~~~~~~~
        vla67.c:65:83: note: subsequently declared as ‘int[x][z]’ with 0 unspecified variable bounds
           65 | static void mat_multiply(int x, int y, int z, int mat1[x][y], int mat2[y][z], int result[x][z])
              |                                                                               ~~~~^~~~~~~~~~~~

### `maxfldwidth.c`, `vecmaxfldwidth.c`, `test-maxfldwidth.c`, `test-vecmaxfldwidth.c`

Playing with determining the maximum field width needed to display the
numbers in a matrix or a vector.

The test programs include the non-test files directly.
The non-test files contain more or less the outline of a header.
The function names are not unique - this isn't ready for use in a
library.

I wonder if 'max' should be 'min' as it determines the field width that
will allow all the values to be printed aligned in the calculated width?
