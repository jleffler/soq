## Primes

The Primes directory contains a number of programs related to generating
primes.
There are vast chunks of overlap between them.

The first set of programs are the Sieves of Eratosthenes in various
forms.
These programs all take an option `-v` to actually print the primes, but
by default count and sum the primes.
This ensures that the compiler doesn't get too enthusiastic about
optimizing anything away — the numbers found are used.

* `eratosthenes-1.c`

  Works with numbers up to 1E9, using one byte per number to record the
  sieve.
  This uses a lot of memory, therefore.

* `eratosthenes-2.c`

  Also works with numbers up to 1E9, but uses one bit per odd number to
  record the sieve.
  Clearly, this uses a lot less memory.
  The main data type is still a byte.

* `eratosthenes-3.c`

  Like number 2, this also works with numbers up to 1E9, using one bit
  per odd number to record the sieve.
  Clearly, this uses a lot less memory.
  The main data type is now `uint64_t`.

  Interestingly, it runs slightly slower than number 2; there might be
  some mileage in experimenting with `uint16_t` and `uint32_t` to see
  whether there's a difference there.

* `eratosthenes-4.c`

  This code exploits the fact that after finding primes 2 and 3, all
  other primes are of the form 6N±1.
  This means it does not check as many numbers for primality, which
  speeds things up.

* `eratosthenes-5.c`

  This is coded to work with numbers up to 1E10, and has been shown to
  cause problems at 1E12 (no recollection of the result at 1E11, but
  probably not good).
  It uses a lot of memory, of course.

* `eratosthenes-6.c`

  This is actually a segmented Sieve of Eratosthenes, and should be
  renamed since in many respects it is separate from the other programs
  named `eratosthenes-N.c`.
  The code seems to work, but that is as much as can be said for it.
  It is a mess.
  Compile with `-DDEBUG` to get some (not readily intelligible)
  information about the segmentation process.

* C++ variants

  The files `eratosthenes-1-cxx.cpp`, `eratosthenes-2-cxx.cpp`,
  `eratosthenes-3-cxx.cpp`, `eratosthenes-4-cxx.cpp`,
  `eratosthenes-5-cxx.cpp`, `eratosthenes-6-cxx.cpp` are links to the
  equivalent name minus the `-cxx`, and are used to demonstrate that the
  code can be compiled as a C++ program as well as a C program.
  No claims are made that the C++ code is idiomatic modern C++ &mdash;
  it is not!
  But it does compile and run and produce the same answers.

* `isprime.c`

  Test harness for various 'is prime' functions.
  There's no caching here; each primality test is ab initio.
  The tests are definitive; there is no probabilistic determination of
  primality.

  Running the code takes time.  The code is written for Mac OS X (10.11.5)
  where the modern POSIX
  [`timer_create()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_create.html),
  [`timer_destroy()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_destroy.html),
  [`timer_settime()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/timer_settime.html)
  functions are not available, so the code instead uses 
  [`setitimer()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/setitimer.html).

  The files `posix-progress.c` and `posix-timer.h` are untested code (as
  of 2016-07-15) that uses the `timer_create()` functions to do the same
  timing that `setitimer()` does.

* `prime-factors.c`

  This code prints out the prime factors of the numbers given on the
  command line, or the numbers from a built-in list.
  It works with 64-bit unsigned integers.

* `minimal-primes.c`

  SO 3383-8621 seeks minimal prime numbers, which are numbers that are
  themselves prime, but where any subsequence of the digits is not a
  prime number.
  The single-digit primes (2, 3, 5, 7) are all minimal.
  No multi-digit minimal prime contains a 2, 3, 5 or 7.
  You can specify a maximum value for the range to be searched.

  The sequence up to 8 digits is as shown.
  The three 8-digit values are remarkable!

  * 1-digit: 2, 3, 5, 7
  * 2-digit: 11, 19, 41, 61, 89
  * 3-digit: 409, 449, 499, 881, 991
  * 4-digit: 6469, 6949, 9001, 9049, 9649, 9949
  * 5-digit: 60649
  * 6-digit: 666649, 946669
  * 7-digit: -none-
  * 8-digit: 60000049, 66000049, 66600049,

  IIRC, there are no 9-digit minimal primes, and I don't recall whether
  I tested beyond that.

* `alt-min-primes.c`

  Also a solution to SO 3383-8621, but I don't think it is code I
  developed.
  OTOH, it isn't an answer on SO either, so I'm no longer sure where it
  came from.

* `project-euler-87.c`

  The number 28 is the smallest number that can be expressed as the sum
  of a prime square, a prime cube and a prime fourth power (that is, you
  can write 28 = 2^2 + 2^3 + 2^4).
  How many numbers below fifty million can be expressed as the sum of a
  prime square, prime cube, and prime fourth power?

* `segmented_sieve.cpp`

  This is code produced by Kim Walisch <kim.walisch@gmail.com>.
  It is a simple implementation of the segmented Sieve of Eratosthenes
  with a few optimizations.
  It has not been assessed for flexibility, conformance with the other
  programs, or any other such functionality.

* `so28005392.cpp`

  This is probably a Project Euler or SPOJ or similar program.
  It's given a series of entries, each entry on a single line.
  An entry consists of a triplet a, b, c.
  The output should be the count of the numbers in the inclusive range
  [a, b] that have c distinct prime factors.

### Scripts

These scripts use a program `timecmd` which is not yet in the
respository (2016-07-15).
It reports the date, command line, and PID of the command that is run,
then waits for the command to complete and reports the exit status and
elapsed time.

* `run`

  Generic script; uses `blanklines` to print a series of blank lines
  (yes, another script not in the repo; it isn't a hard one to write,
  though) and then times whatever command was given as its arguments.

* `test-0`
* `test-1`
* `test-2`
* `test-3`
* `test-4`
* `test-5`
* `test-6`

  These scripts use `run` to execute various of the `eratosthenes-N`
  commands with a default size argument of 1000.
  The later scripts run multiple programs to get the results, and use
  `timecmd` again on each program separately.
  The scripts apart from `test-0` ensure the programs are up to date
  using `make`.

