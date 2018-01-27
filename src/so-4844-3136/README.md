### Stack Overflow Question 4844-3136

[SO 4844-3136](https://stackoverflow.com/q/48443136) &mdash;
C How read() function read from STDERR?

Code to demonstrate that:

* `stdio11.c` — file descriptors 0, 1, 2 are all typically readable
   and writable.
* `stdio13.c` — file stream stdin is not writable and file streams
   stdout and stderr are not readable.

