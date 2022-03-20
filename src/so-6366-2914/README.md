### Stack Overflow Question 6366-2914

[SO 6366-2914](https://stackoverflow.com/q/63662914) &mdash;
Sort elements in array that are greater than n in ascending order and
remaining in descending in C.

> I need to sort an array in C in both ascending and descending order.
>
> Values greater than n need to be first and ascending and any values
> less than n will be at the end and in descending order.  There will be
> an unknown number of inputs

### `qs71.c`

Verbose comparator using global variable N.

### `qs73.c`

On Linux and Mac systems, there is also a qsort_r() which allows you to
pass N as a value to the comparator function — but unfortunately, the
signatures on the two systems are different:

MacOS (BSD):

    void qsort_r(void *base, size_t nel, size_t width, void *thunk,
                 int (*compar)(void *, const void *, const void *));
Linux:

    void qsort_r(void *base, size_t nmemb, size_t size,
                 int (*compar)(const void *, const void *, void *), void *arg);

The comparison function is given an extra argument, and a pointer is
passed to the qsort() that is relayed to the comparator.
However, the calling sequences are different.
Here is code using the MacOS variant — the changes for the Linux
variant are simple.

### `qs79.c`

Variation of `qs73.c` with debugging available (and turned on).
Uses a more compact comparator but produces the same results.

### `qs83.c`

Variation of `qs79.c` with function to check the sort order, etc.

