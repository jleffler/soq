### Stack Overflow Question 4282-2480

[SO 4282-2480](http://stackoverflow.com/q/42822480) &mdash;
POSIX Threads, unique execution

One major difficulty is tracking when to create a new random number.
One obvious solution is to have an array of random numbers and generate
a new one for each iteration, indexed by the iteration number.
Since this is too obvious, we're presumably supposed to do the job
ourselves.

The code uses `pthread_cond_wait()` and `pthread_cond_broadcast()` to
control the threads.
The tricky part is getting the predicates associated with the condition
variable correct.

The program is in `pthrd37.c`, but the version in the answer on SO is in
`pthrd37-df75f045.c` (the 8-digit hex is the commit hash used for the
code in the answer on SO).
The code in `pthrd37.c` has a variety of mainly simple enhancements over
that original answer.
It takes command line options `-n threads` and `-c cycles` to control at
run-time how many threads to run and how many iterations to try.

The program also uses a more complex technique to identify which threads
are complete, rather than simply joining each thread in the order it was
started.
This requires cooperation from the thread functions, and uses an extra
condition variable to detect when a child has exited.

This code triggered an upgrade to `stderr.c` and `stderr.h` from the
`libsoq` directory.
The functions now use `flockfile()` and `funlockfile()` to ensure atomic
writing of the message, and there's a `fflush()` to improve the handling
of logging to a file.
Additionally, there's a pair of functions `err_settimeformat()` and
`err_gettimeformat()` that allow you to control the format used when
logging information.
These features are used by `pthrd37.c`.

Chapter 7 "Real Code" in the book [Programming with POSIX
Threads](http://www.informit.com/store/programming-with-posix-threads-9780201633924)
by David Butenhof describes and implements a 'barrier', which has pretty
much the structure outlined in the solution here.
There's the mutex, the condition, a counter, a threshold, and a cycle
number — all as devised for this answer.
The concepts are similar, but the barrier counts down to zero instead of
up to the threshold as this code does.
You can find the code (including the barrier code) at the linked site.
It also provides better separation of 'start of new cycle' activities
and 'continue with new cycle' activities.

Note the POSIX 2008 (2016) provides:

* [`pthread_barrierattr_destroy()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrierattr_destroy.html)
* [`pthread_barrierattr_getpshared()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrierattr_getpshared.html)
* [`pthread_barrierattr_init()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrierattr_init.html)
* [`pthread_barrierattr_setpshared()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrierattr_setpshared.html)
* [`pthread_barrier_destroy()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrier_destroy.html)
* [`pthread_barrier_init()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrier_init.html)
* [`pthread_barrier_wait()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_barrier_wait.html)
