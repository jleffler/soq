# Material to be used for SO documentation in C for topic 'Using `qsort()`'

The material here was going to be used to create a topic within the C
Documentation on Stack Overflow related to the `qsort()` function.
However, since the original Documentation project was cancelled, that
won't happen now.

The source code in qs-07-int.c can use the cmpint() function from any of
the files altcmp?.c.

The command line to do so is:

    rmk UFLAGS=-DCOMPARATOR_SOURCE=altcmp4.c -u qs-07-int

This may be improved by upgrading the makefile.

* `altcmp1.c` &mdash; A first variant of integer comparison ascending
* `altcmp2.c` &mdash; A second variant of integer comparison ascending
* `altcmp3.c` &mdash; A third variant of integer comparison ascending
* `altcmp4.c` &mdash; A fourth variant of integer comparison descending (based on altcmp3.c).
* `ls73.c` &mdash; Lexicographic sort of numeric data
* `ls79.c` &mdash; Lexicographic sort of numeric data

* `oddascevendesc.c` &mdash; sort odd numbers ascending before even numbers descending
* `qs-01-int.c` &mdash; Basic sort of integer data ascending order
* `qs-02-str.c` &mdash; Basic sort of data within a single string ascending order
* `qs-03-2da.c` &mdash; Basic sort of 2D character array ascending order
* `qs-04-asp.c` &mdash; Basic sort of array of character pointers ascending order
* `qs-05-date.c` &mdash; Basic sort of structured data (a Date type)
* `qs-06-bad.c` &mdash; What happens when you use the wrong comparator
* `qs-07-int.c` &mdash; Basic sort of integer data with controllable comparator
* `qs47.c` &mdash; Composite of qs-01-int.c to qs-06-bad.c
* `qs79.c` &mdash; Sort of array of ragged arrays of `int` (length of array in index 0)
* `qs8m.c` &mdash; Sort array of arrays of 6 `int`.
* `sr19.c` &mdash; Sort of array of structures including FAM data

