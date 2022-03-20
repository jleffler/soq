### Stack Overflow Question 7063-3743

[SO 7063-3743](https://stackoverflow.com/q/70633743) &mdash;
C lang task - how to optimize my code for performance. My time complexity is O(N^2)

Task:

A non-empty array A consisting of N integers is given.  Array A
represents numbers on a tape.

Any integer P, such that 0 < P < N, splits this tape into two non-empty
parts: A[0], A[1], ..., A[P − 1] and A[P], A[P + 1], ..., A[N − 1].

The difference between the two parts is the value of:

|(A[0] + A[1] + ... + A[P − 1]) − (A[P] + A[P + 1] + ... + A[N − 1])|

In other words, it is the absolute difference between the sum of the
first part and the sum of the second part.

For example, consider array A such that:

    A[0] = 3
    A[1] = 1
    A[2] = 2
    A[3] = 4
    A[4] = 3

We can split this tape in four places:

* P = 1, difference = |3 − 10| = 7
* P = 2, difference = |4 − 9| = 5
* P = 3, difference = |6 − 7| = 1
* P = 4, difference = |10 − 3| = 7

Write a function:

int solution(int A[], int N);

that, given a non-empty array A of N integers, returns the minimal
difference that can be achieved.

For example, given:

    A[0] = 3
    A[1] = 1
    A[2] = 2
    A[3] = 4
    A[4] = 3

the function should return 1, as explained above.

Write an efficient algorithm for the following assumptions:

* N is an integer within the range [2..100,000];
* each element of array A is an integer within the range [−1,000..1,000].

### Solutions

* `md19.c` - bare-bones solution
  This at least includes input validation missing from the question

* `md41.c` - fancy solution documenting progress
  Variation with command line arguments `-h` to print help and `-v` for
  verbose, printing the calculations as it goes.  Uses `getopt(3)` and
  some code available in my [SOQ](https://github.com/jleffler/soq)
  (Stack Overflow Questions) repository on GitHub as files `stderr.c`
  and `stderr.h` in the
  [src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
  sub-directory.

* `md43.c` - variation on `md41.c`
  Another fancy solution but this one avoids the JLSS functions and
  command-line argument handling Variation on `md41.c` which
  unconditionally prints the calculations as it goes.  Avoids using
  `stderr.[ch]` but doesn't use command line options either.

* `md17-generate.sh` - data generator
  Not properly paramterized; it runs `md41` unless edited.  Use JLSS program `random`.

