### Stack Overflow Question 4692-3548

[SO 4692-3548](https://stackoverflow.com/q/46923548) &mdash;
Dynamic Memory Allocation for Matrix Multiplication

Not clear that this is very interesting.
For some reason, I'd put the code in soq/so-4692-3548 and couldn't spot
this, but couldn't delete the branch either because it wasn't merged.

The exact status of any program is unclear.

<hr>

Given matrices X and Y, calculate

    W = (XT * X)^-1 * XT * Y

* `mm11.c`

Nominally the original code from the question.

* `mm47.c`

Revision A - using a matrix allocation function.

* `mm61.c`

Original code cleaned up for Valgrind.

* `mm89.c`

Revision C.

* `mm97.c`

Revision B - using functions to handle matrix multiplication and transposition.
It isn't clear why the functions were abandoned in Revision C.

