# Questions and answers related to sorting


## so-0765-6915 &mdash; Sort and merge separate files

Using multiple child processes to sort separate files, and then merge
the results back.
Merging is done for pairs of files.
More sophisticated code could merge many more files at a time.

Note that the data is expected to be binary integers written using
`fwrite()` or equivalent.

## so-1321-3864 &mdash; Multiple pipe sort

Reads text lines from standard input and distributes the lines to
multiple child processes.
Each child sorts its data using `qsort()`, then writes the results back
so that the results can be merged.

## so-1482-4668 &mdash; Merge sort

One generic (`void *`) sort, and one `int` array sort.

## so-1802-8773 &mdash; Merging in merge sort algorithm

Another example with one program implementing a merge sort for an array
of `int` and another program implementing a generic merge sort.

## so-1882-0288 &mdash; Using qsort() for key + value list from file

Curious text data layout, like:

    key: 1804289383 rec:886 777 ...

The key value is the sort criterion.

* `keysort1.c` reads standard input and writes to standard output only
* `keysort2.c` reads files or standard input, overwriting file or
   writing to standard output


## so-1892-8821 &mdash;

Templatized C++ merge sort using vectors.

## so-1947-1071 &mdash;

Basic fix-ups of radix code provided in question.
Radix sorts are relatively unusual, so I've kept note of it.


## so-1960-7450 &mdash; Semi-basic quick sort

Basic quick sort except it can use a random or last value for the partition element.
Uses Lomuto partitioning.

The test code is a simplified version of what's in sorttest.


## so-1972-7309 &mdash;

* `qs3.c` - basic quick sort with Lomuto partitioning on last element
* `qs7.c` - same code with extensive debugging

## so-3442-6337 &mdash; Batcher sort

A particular sorting algorithm.

## so-3842-7289 &mdash; Perl sorting criteria

Mildly complex sort criterion in Perl.

## so-4178-6918 &mdash;

Working from Wikipedia.  Hoare partitioning.  Using first element as pivot.

* Files `qs-hp37.c`, `qs-main.c`, `qs-main.h` form one program.
* File `qs37.c` formas another.

Code contains pseudo-code comments from Wikipedia.

##  so-5332-1864 &mdash stable partition (sort)

Sort array so that the numbers with the same digits are in front of
those that don't have the same digits.

This has code based on merge sort, insertion sort and selection sort.

## sortfile &mdash; sorting files

* `sortfile1.c` - sort up to 1000 lines from standard input
* `sortfile2.c` - sort indefinite number lines from standard input

As much an exercise in using POSIX `getline()` as anything else.

## sorttest &mdash; Testing sort algorithms against data sets

Sorting data generated in various patterns (including random, but also
uniform, ascending, descending, forward organ pipe, reverse organ pipe)
using various algorithms (quick, bubble, selection, insertion) and
timing the results.

This code sorts arrays of `int`.

