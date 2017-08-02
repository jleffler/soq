### Stack Overflow Question 4544-8840

[SO 4544-8840](https://stackoverflow.com/q/45448840) &mdash;
Multithreaded (C) program threads not terminating

* `pth17.c` — original code; only compiles with warnings under GCC 7.1.0
* `pth31.c` — first answer; reasonable code, but room for improvement
* `pth47.c` — revised code with sub-second sleeping, random fractions (0.10-0.25),
random sleep intervals (0.100 s to 0.250 s), printing of characteristics, etc.
* `pth79.c` — original code; minimal cleanup so it compiles
* `pth97.c` — second answer; more succinct thread function

Note that `pth31.c` and `pth47.c` 'cheat' and reference variable
`scholarship` without the protection of the mutex.
One of the changes is to ensure that the variable is only referenced
with the protection of the mutex.
