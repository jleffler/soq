### Stack Overflow Question 1363-6252

[SO 1363-6252](https://stackoverflow.com/q/13636252) &mdash;
C Minishell Adding Pipelines

Two minor variants of the same code.

* `pipes-13636252.c`

  Basic code handling a pipeline of 5 commands.

* `pipes-v2.c`

  Enhanced version of the code that print detailed information about
  the file descriptors in use, if invoked with the `-v` flag.

There is room to think that this solution using mutually recursive functions
isn't necessarily the best — but it does work.

