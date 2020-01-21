### Stack Overflow Question 1843-7779

[SO 1843-7779](https://stackoverflow.com/q/18437779) &mdash;
Do I need to do anything with a SIGCHLD handler if I am just using
wait() to wait for 1 child to finish at a time?


* `sigalrm.c`

  Showing SIGALRM and catching it at work.
  Uses `microsleep.h` and nominally `microsleep.c` for microsecond
  sleeping.

* `sigchld.c`

  Showing how handling `SIGCHLD` in different ways affects the way
  processes get to see children dying.

* `sigexit73.c`

  Showing how `sigaction()` and `SA_SIGINFO` can be used to capture a
  32-bit exit status on Unix.
  Built with code from `sigchld.c`.

  Support material for [SO
  0017-8565](https://stackoverflow.com/q/179565) &mdash; ExitCodes
  bigger than 255 &mdash; possible?

* `signals.c`

  Showing how `sigaction()` and `SA_SIGINFO` can capture information about
  which process sent a signal, unlike the regular signal handler.

* `sigsync.c`

  Showing one way in which processes can use `SIGUSR1` to coordinate
  activity between themselves.
