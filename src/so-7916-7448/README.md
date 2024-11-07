### Stack Overflow Question 7916-7448

[SO 7916-7448](https://stackoverflow.com/q/79167448) &mdash;
Incorrect output while trying to calculate SINE using Taylor series in C

It turned out to be a simple error initializing variable sum.

* `sine17.c`
  Code from OP with minor modifications (principally, using `int
  main(void)` rather than `int main()`; otherwise, minor spacing
  changes).
* `sine47.c`
  Compiling code with instrumentation which shows the problem.
* `sine59.c`
  Fixed code with instrumentation.
* `sine97.c`
  Fixed code using `double` instead of `long double`.

