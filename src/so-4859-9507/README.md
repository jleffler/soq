### Stack Overflow Question 4859-9507

[SO 4859-9507](https://stackoverflow.com/q/48599507) &mdash;
How to pipe to a program that read only from file

OP's code sends a null byte after an otherwise valid JavaScript program
to PhantomJS, and PhantomJS 2.1.1 hangs because of the null byte.
There were other problems to be fixed originally; most of them were
indeed fixed.
Program `pipe19` is the working code that does not send the null byte to
PhantomJS.

* `min-repro-01.c`

  A more or less minimal reproduction of the problem for the bug report
  made to PhantomJS.org.
  This code is adapted from `pipe31.c` but heavily modified.
  It reads the response in kilobyte-size chunks, writing as it reads.
  It has an error reporting function which reduces the code in `main()`.
  It has variables renamed.
  The wait code has been removed.

  When run as `min-repro-01` (no argument), it hangs 'indefinitely'; no
  response is received in 20 seconds.
  Interrupt the program.

  When run as `min-repro-01 fix` (the spelling "fix" matters), it
  produces a response (of about 250 KiB data in 3650 lines) in about 6s
  on a modern MacBook Pro.

  The difference is simply whether or not the null byte at the end of
  the string holding the JavaScript program is sent to PhantomJS.

* `ext_program.c`

  A dummy external program to work with the OP's original program.
  It reads the file named on the command line, which is actually
  `/dev/stdin`.
  Used in controlled contexts, it works fine The variant here expands
  the input data by a factor of over 100 by the simple expedient of
  printing the message received 100 times with annotations around it.

* `phantomjs.c`

  Another external program — a mild modification of `alev.c` — which
  reports its arguments and its environment to standard output, and
  copies the file named as `argv[2]` to standard output as well as
  adding the other information.

  Initially used with `pipe31` and `pipe19` until the real program
  was used instead.

* `pipe11.c`

  A variant of the `pipe89.c` with a medium buffer size (1024 bytes) for
  reading the response from the child program.

* `pipe19.c`

  The final bug-fixed and reformatted version of the OP's second
  program.
  This does not send the null byte to PhantomJS.
  The JavaScript program is split across multiple source lines using
  string concatenation.

  It takes 5-6 seconds to get the output from phantomjs.

* `pipe31.c`

  The OP's second program with minimal modifications (comment at the
  top; add `void` to definition of `int main(void)`.
  As with the first program, this writes a null byte to the child
  process, which turns out to be the crucial problem.

  It is not clear why PhantomJS hangs when an otherwise valid program if
  followed by a null byte, but empirically, that is what happens in
  PhantomJS 2.1.1.

* `pipe37.c`

  The OP's first program with minimal modifications (comment at the top;
  add `void` to definition of `int main(void)`.
  This code does write a trailing null byte to the child process.

* `pipe89.c`

  Bug-fixed version of OP's first program.
  There were a variety of issues with memory management, which did not
  consistently manifest themselves on macOS High Sierra, which is
  puzzling.
  Unfortunately, Valgrind is still not available for High Sierra, which
  is a nuisance.
  The fixed code did not write the trailing null byte, but the
  importance of that was not clear at the time.

