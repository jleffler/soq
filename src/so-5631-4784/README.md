### Stack Overflow Question 5631-4784

[SO 5631-4784](https://stackoverflow.com/q/56314784) &mdash;
How to chunk shell script input by time, not by size?

This is a non-trivial problem.
The program `chunker79` is my suggested solution.

There are three implementations, one using `alarm(2)`, one using
`setitimer(2)` et al, and one using `timer_create(2)` et al.
The first should work practically anywhere.
The second must be used on macOS (up to 10.14.5 Mojave, anyway; who
knows what'll be in 10.15 Catalina).
The third can be used on Linux (tested on an Ubuntu 18.04 LTS VM running
on a Mac).

The default mode is to use `timer_create(2)` etc; that is the direction
POSIX would prefer.
It has marked `setitimer(2)` obsolete.
To compile using `setitimer(2)`, add flag `-DUSE_SETITIMER` (and, on a
Mac, add LDLIB2= too).
To compile using `alarm(2)`, add flag `-DUSE_ALARM`.

The script `gen-data.sh` uses a combination of somewhat specialized
programs to produce random data at random intervals.
It can be used to check the behaviour of `chunker79`.

There are undoubtedly improvements that could be made, but this seems to
meet the basic requirements of the question.
