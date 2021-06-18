### Stack Overflow Question 4756-4391

[SO 4756-4391](https://stackoverflow.com/q/47564391) &mdash;
POSIX regular expression for parsing uevent causing error

The problem is the use of PCRE notations &mdash; specifically, the named
captures `(?<name>...)`:

      char *regexString = "(?<action>[a-zA-Z]+)@\\/(?<dev_path>.*)"
                          "\\/(?<subsystem>[a-zA-z]+)\\/(?<name>[a-zA-z]+)";

The code in `rx-posix-59.c` shows the use of POSIX regular expressions
without the named captures, which meets the reqirements of the question.

The code in `rx-pcre1-73.c` shows the equivalent use of PCRE version 1 regular
expression code.

The code in `rx-pcre2-83.c` shows the equivalent use of PCRE version 2 regular
expression code.

