# Using the standard C function `qsort()`

## Overview

    void qsort(void *base, size_t number, size_t size, int (*cmp)(const void *v1, const void *v2))

The C standard provides a function, `qsort()`, that sorts arbitrary data
in an array using sort criteria of the programmers choosing.
Although traditionally it is implemented as a quicksort, there is no
requirement in the standard about the algorithm used.

The start of the array is identified by `base`.
The number of elements in the array is specified by `number`.
The size of each element is specified by `size`.
The comparisons are done by the function `cmp`.
It should compare the two elements of the array pointed at by the
pointers, and return a negative value if the one pointed to by `v1`
should come before the one pointed to by `v2`; a positive value if the
one pointed to by `v1` should come after the one pointed to by `v2`; and
zero if the two entries are equal.

## Sort an array of integers



## Variant: `qsort_r()`

There are at least two variants of the `qsort_r()` function: the one
found on BSD-based systems (including macOS Sierra and Mac OS X), and
the one found on Linux-based systems.

### BSD Variant

    void qsort_r(void *base, size_t number, size_t size, void *arg,
                 int (*compar)(void *arg, const void *v1, const void *v2))

### Linux Variant

    void qsort_r(void *base, size_t number, size_t size,
                 int (*compar)(const void *, const void *, void *), void *arg);

### How it works

The basic idea is that sometimes you need extra information to be able
to make comparisons correctly, and the `qsort_r()` function allows you
to pass such data to the comparator.

However, there are multiple differences between the BSD and Linux
variants:

* The `qsort_r() on BSD takes the argument as the fourth argument to
  `qsort_r()` and it is passed as the first argument to the comparator.
*  The comparator on Linux takes the argument as the fifth argument to
   `qsort_r()` and it is passed as the third argument to the comparator.

The only good news here is that what works on one system shouldn't
compile on the other.
Because of this discrepancy, POSIX is unlikely to standardize
`qsort_r()`, especially not with that name (it tries to avoid breaking
existing implementations).

### When might you use it?

