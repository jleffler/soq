### Stack Overflow Question 4825-2451

[SO 4825-2451](https://stackoverflow.com/q/48252451) &mdash;
Is there any way for a program reading from a FIFO to detect that a
program writing to the same FIFO has closed it?

The short answer is 'yes, but…'.

The question asks about epoll() which is a Linux-specific extension.
This code was developed on a Mac running macOS High Sierra 10.13.2,
where epoll() is not available.
However, it helps make a point, that once there are no processes with a
FIFO open for writing, the reader continually gets 0 bytes returned
until another process opens the FIFO for writing.
It goes into a busy loop unless you're careful.
This code naps for a random time (between 0.250 and 0.750 seconds) to
avoid busy waiting.
Another option is to close the FIFO on getting EOF and then reopening
the FIFO; the open hangs until there is a process that has opened the
FIFO for writing.
This is implemented with the `-r` option for `fifo-rdr-41`.
A third option is to have the reading process also open the file for
writing (best to use a separate file descriptor for that; the result is
undefined if you open a FIFO with `O_RDWR` according to POSIX).
Of course, since open-for-reading blocks until there's a writer, and
open-for-writing blocks until there's a reader, you can't open the
writing file descriptor until after the reading open has succeeded.
This is implemented with the `-w` option for `fifo-rdr-41`.

The writer process currently writes a random amount of random upper-case
alphabetic data to the reader on each of a random number of iterations.
It takes a random nap before writing on each iteration, and a random nap
before closing the file descriptor.

The reader, `fifo-rdr-41`, now accepts options:

    -h  Print help and exit
    -r  Reopen FIFO on reading EOF
    -w  Open FIFO for writing

Other options aplenty could be added, such as:

    -T timeout  Stop if timeout elapses in a system call
    -c count    Stop after count cycles (number of reopens)
    -f FIFO     Name of FIFO
    -t elapsed  Stop after total elapsed time.

