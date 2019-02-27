### Stack Overflow Question 4576-0666

[SO 4576-0666](https://stackoverflow.com/q/45760666) &mdash;
Static Matrix multiplication to dynamic matrix in C

Various matrix multiplication schemes.
Note that the 'multiplication' algorithm is not the normal matrix multiplication.

* `mm19.c` — Return pointer to dynamically allocated array of pointers.
* `mm23.c` — Hack job returning a pointer to a dynamically allocated array.

  The hack revolves around the return type, and the use of a constant,
  5, in the signature.
  Can it be upgraded to use one of the parameters outside the argument
  list?

* `mm53.c` — Argument is pointer to dynamically allocated array.

