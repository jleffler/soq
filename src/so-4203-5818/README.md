### Stack Overflow Question 4203-5818

[SO 4203-5818](https://stackoverflow.com/q/42035818) &mdash;
C find all possible sides of a triangle from the perimeter

This code is mainly about 'sort 3 numbers' without using `qsort()`.
There are three program which explore what happens.
They're differently configurable.
The code that might actually be used in production is one of the working
functions in `st13.c`, but the code in `st17.c` and `st19.c` allows you
to experiment with greater or lesser flexiblity how different comparison
orders work.

The material in so-4203-5818.md is from my answer to the question, and
it does in fact use `qsort()`, not any of these 'sort 3' operations.

The files `s6v23.c` and `s6v59.c` both sort 6 fixed name variables,
not necessarily in the most efficient way possible.
