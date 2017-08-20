### Stack Overflow Question 0035-2055

[SO 0035-2055](https://stackoverflow.com/q/00352055) &mdash;
Best algorithm to strip leading and trailing spaces in C

Fundamentally, the [answer](https://stackoverflow.com/a/352119) posted
by [AlfaZulu](https://stackoverflow.com/users/44060/alfazulu) is broken.
The function `stripLeadingAndTrailingSpaces()` does not do what it
claims to do and does trample out of bounds on occasion.

The code in `slts59.c` demonstrates the problem and provides a fix
(function `str_strip()`, adapted from AlfaZulu's code).

Note that you need to use [Valgrind](http://valgrind.org/) or equivalent
to see the memory abuse; you simply need to run the code on data with
trailing blanks to see that the algorithm doesn't do what it claims to
do

The code in `slts61.c` also demonstrates the problem and provides a fix,
but also demonstrates another working
[answer](https://stackoverflow.com/a/352109) — from the Linux kernel,
but posted by [Tuminoid](https://stackoverflow.com/users/40657/tuminoid)
— and that has a different interface.
The functions from slts59.c are revised to match the `strstrip()`
interface.
