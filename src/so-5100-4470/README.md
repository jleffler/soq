### Stack Overflow Question 5100-4470

[SO 5100-4470](https://stackoverflow.com/q/51004470) &mdash;
Closing unused pipe file descriptors

There are two programs here, one to demonstrate a pipeline hanging if
the write end of a pipe is not closed, and one to demonstrate a pipeline
hanging if the read end of a pipe is not closed.

* `fork13.c` — unclosed write end

* `fork29.c` — unclosed read end

The logic is similar, and so is the code.

In each case, a pipeline was devised where the non-closure of a pipe
would cause trouble.
For the write end, `ls -l | sort` is good; if `sort` has the write end
of the pipe open, it won't see EOF, so it won't produce any output.
For the read end, `seq 65536 | sed 10q` is good; even though the `sed`
quits, the `seq` process still has the read end of the pipe open, so it
will be blocked from writing and won't get SIGHUP or a write error.

For both programs, if run with no arguments, the program blocks an must
be signalled to kill it.
If the program is run with any arguments (it doesn't matter what the
arguments are), the processes will close pipes correctly and the
pipeline terminates promptly.

This code uses the `stderr.[ch]` code from `libsoq`.

The accepted answer only shows the code for the unclosed read end
(`fork29.c`), because the question was about that.
A first version of the answer shows the code for unclosed write end
(`fork13.c`), but that version of the answer was promptly deleted when I
realized I'd provided code for the wrong case.

