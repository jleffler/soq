### Stack Overflow Question 75494-6155

[SO 75494-6155](https://stackoverflow.com/q/754946155) &mdash;
Random Password Generator + Algorithm?

My suggested code is packaged as a function in `grpwd43.c` (header `grpwd43.h`).

    extern void gen_random_password(size_t length, char buffer[length]);

The random seed code generation code in `randseed.c` and `randseed.h`
uses `/dev/random` by default but can be configured to use a number of
other algorithms.
The files `crc.c` and `crc.h` contain some CRC algorithms if your system
has neither `/dev/random` (nor `/dev/urandom`) nor `arc4random()`.

The random number generation code using POSIX `nrand48()` is in
`prng48.c` and `prng48.h`.
You should call `prng48_seed()` with an array of 3 `unsigned short`
integers that represent the random seed - though there is a default
value.
You then call `prng48_rand()` with the lower and upper bounds of the
range of 31-bit unsigned integers that you want.
The algorithm takes care to ensure that there is no bias in the result.

The files `kludge.c`, `kludge.h`, `posixver.h`, `stderr.c`, and
`stderr.h` can be found in the
[src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.
They are needed for the `FEATURE` macro used in `randseed.c` and
testing, etc.

The makefile assumes you are using GNU Make or an equivalent that
understands the following notation which adds `-DTEST` to `CFLAGS` when
compiling `grpwd43.c` to produce `grpwd43.o`:

grpwd43.o: CFLAGS += -DTEST

