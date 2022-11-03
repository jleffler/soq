### Stack Overflow Question 1974-7644

[SO 1974-7644](https://stackoverflow.com/q/19747644) &mdash;
Shell, run four processes parallel

[SO 7430-0464](https://stackoverflow.com/questions/74300464) &mdash;
How can I limit the number of parallel child processes?

The question code for SO 1974-7344 runs a simulation (instead of
sleep), and can't predict how long a simulation will take (so sleep
with random delay is a good model).  The object is to have N (4)
processes running all the time, starting a new one as soon as one of
the current N is complete.

The question for SO 7430-0464 asks how to limit the processes and
specifies that the platform is FreeBSD.

* `run-processes.pl`

   A Perl script to simulate the requirements of SO 1974-7644.

* `numproc19.c`

  This code uses a fixed limit (4 child processes) and number of tasks
  to run (20), but is trivially adaptable to run arbitrary numbers of
  processes with arbitrary limits.
  It doesn't use o/s facilities to enforce the limit; it simply ensures
  it does not run too many processes.

  Clearly, the `be_childish()` function can be revised to do whatever
  task is appropriate - as identified by the task number argument.
  This might be to run a series of commands read from a file, or any
  other more or less devious technique for choosing what to do.

  As noted by the `_Noreturn` in the signature, it is crucial that the
  `be_childish()` function does not return.
  If it executes another program, the post-exec code should report an
  appropriate error and exit with a non-zero status.

  For use in production code, you'd consider carefully how much of the
  output is required and where it should be logged to.

* `numproc23.c`

  This program uses a couple of more complicated PRNG support systems
  which are not yet available in the src/libsoq library, and some other
  code which is available there.

  It is code that would be adapted to handle command line arguments.
  The code in `numproc19.c` was adapted by stripping out the JLSS
  support library code.

  Production code would not delay for random intervals but would run
  useful commands.  See also the commentary for `numproc19.c`.  It would
  probably make heavier use of the code from `stderr.[ch]` and would
  likely set options such as `ERR_MILLI` or `ERR_MICRO` to report times
  automatically, and `ERR_PID` to report the PID automatically.

  The makefile is not configured to build this program as it relies on
  options that won't work on other people's machines.
