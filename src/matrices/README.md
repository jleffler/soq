## Matrices in C

These are assorted answers to questions about matrix handling in C.
It would not be surprising to find that there are other answers in the
src/so-abcd-wxyz directories that should be here too.

NB: In this directory, the term matrix is used to describe both arrays
of pointers (to arrays of pointers (to ...)) to elements, and also to
simple blocks of elements.
Both are accessed using the multiple square bracket notation &mdash; the
underlying access mechanics are different, though.

### SO 1719-2011

* `matmul89.c` &mdash; variable-dimension 2D array multiplication in strict C89.
* `matmul99.c` &mdash; variable-dimension 2D array multiplication in C99 using VLA.

### SO 1857-9583

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

### SO 2881-8521

* `alloc3dmat.c` &mdash; Allocate a 3D matrix in a single memory allocation.

  The code makes some mostly excusable (though not strictly justifiable)
  assumptions about alignment requirements, namely that pointers are as
  stringently aligned as type `double`.  Fixing that would not be all that
  easy, though neither would it be impossible.

### SO 2635-0717

* `2da.c` &mdash; memory allocation for a 2D array of arrays with negative indices.

### SO 3256-5694

* `vlastruct.c` &mdash; another variable-dimension 2D array multiplication in C99 using VLA. 

### SO 3259-8224

* `vlamat.c` &mdash; and another variable-dimension 2D array multiplication in C99 using VLA.

