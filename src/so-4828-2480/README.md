### Stack Overflow Question 4828-2480

[SO 4828-2480](http://stackoverflow.com/q/48282480) &mdash;
POSIX Threads, unique execution

One major difficulty is tracking when to create a new random number.
One obvious solution is to have an array of random numbers and generate
a new one for each iteration, indexed by the iteration number.
Since this is too obvious, we're presumably supposed to do the job
ourselves.
