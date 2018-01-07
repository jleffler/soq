### Stack Overflow Question 4756-4391

***This is a WIP — work in progress***

[SO 4756-4391](https://stackoverflow.com/q/47564391) &mdash;
POSIX regular expression for parsing uevent causing error

The problem is the use of PCRE notations &mdash; specifically, the named
captures `(?<name>...)`:

      char *regexString = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)"
                          "\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";

The code in `rx-posix-59.c` shows the use of POSIX regular expressions
without the named captures, which meets the reqirements of the question.

The code in `rx-pcre-79.c` will show the equivalent use of PCRE regular
expression code.

The code in pcre.c is a vignette using PCRE 1.
It needs to be upgraded to work with PCRE 2.

