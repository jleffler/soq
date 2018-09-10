### Stack Overflow Question 5223-3288

[SO 5223-3288](https://stackoverflow.com/q/52233288) &mdash;
Printing out relatively prime pairs, triples, quadruples etc between two given numbers

PPTQ = Prime Pairs, Triples, Quadruples

* `pptq47.c`

  Basic printing of mutually prime pairs between two values.

* `pptq59.c`

  Extending `pptq47.c` to handle triples, etc.

<hr>

Experimentation with [Valgrind](http://www.valgrind.org/) shows that the
original code in `pptq59.c` does not leak memory, which is gratifying.
Not surprisingly, the first version of `pptq47.c` did leak memory, but it
was fixed with a trivial backport of the freeing code from `pptq59.c`.
