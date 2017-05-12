### Stack Overflow Question 4380-8114

[SO 4380-8114](http://stackoverflow.com/q/43808114) &mdash;
Implementation of merge sort using threads and fork

### `ms83`

This is the original answer to the question.
The code works, at least for the size 10 arrays.
The threaded code is woefully slow, taking 100 times as long as the
non-threaded code.

### `mulprocsPipemergesortwords0.c`

This is code sent to me by the someone other than the OP after the
original Q&A.
It isn't bad code; it compiles cleanly under my default compilation
options.

> Attached is the code you posted on stackoverflow.
> I learned a lot from you.
> However, I tested it with simple data, the program got stuck when a
> input file quite big (in fact, not that big).
> Please help me check if I was doing wrong or something was missing on
> Linux platform.
> After I compiled & linked the program, I did the following

>     seq 100000 > data.txt
>     a.out < data.txt

> then it got stuck before the line `read_line(...)` inside the function
> `merge()`.
> Note that if I create data `seq 50000` or `80000` to `data.txt`, the
> program still runs fine.
> I have 4GB RAM/64bit OS in my Linux box.

It works on small enough data sets, but it locks up when the data set
generated using `seq NNNN` reaches around 320 KiB (5 x 64 KiB) - size
specified with 20/20 hindsight.

### `ms11`

This is the fixed code sent to the other person.  The email response
I gave was:

> Interesting!
> Attached is my code that solves your problem.
> I've tested it on on data sets from 50,000 up to 900,000 (and smaller
> ones too).
> The code you sent worked for me up to somewhere between 55000 and 58000;
> this works to as big as I've tested.
> If you compile the code with no special options, the bug fix will be
> included.
> If you compile the code with `-DDO_NOT_FIX_THE_BUG`, it will fail as
> before.

> I was using the command line:

>     rmk ms11 -u UFLAGS=-DDO_NOT_FIX_THE_BUG=1 &&
>     ms11 < data.100000 2>&1 | grep -E 'created|complete|all.lines|exited'

> where `rmk` is my version of make, `-u` means 'build unconditionally', and
> `UFLAGS` are 'user flags' added to the C compiler command line by the
> resident makefile.
> There's a lot of debugging output from the code that you don't want to
> see when there are 100,000 (or even 1,000) lines in the input.
> The grep command shows the interesting lines.
> The actual compiler command line was:

>     gcc -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes \
>         -Wstrict-prototypes -Wold-style-definition -DDO_NOT_FIX_THE_BUG=1 \
>         ms11.c -o ms11

> You can drop the `-D` option to get the code compiled with the fix.

> One of the key observations was that the output for the failing version
> contained:

>     Child 24639 created
>     Child 24640 created
>     Child 24641 created
>     Child 24642 created
>     Child 24643 created
>     Distribution complete
>     24643: all lines read
>     24643: all lines sorted

> and then I interrupted it.
> The last child, C5, completed its inputs, but the ones started before it
> did not.
> And this was consistent.
> But nothing was failing; it was as though the other children were not
> getting EOF on their input pipe, even though the parent process had
> closed it.
> And then it dawned on me — that was exactly the problem.
> The last child, C5, terminated because only the parent process and C5
> ever had the pipes open, and the child closed the write end of its input
> pipe, so when the parent closed the write end too, it got EOF correctly.
> However, the other children not only have their own pipes open but also
> the file streams for the child processes created before it — and they
> didn't close those extraneous streams.
> So, even though the parent closed the write end of their input pipe, the
> other children could still write to them, so they don't get EOF and they
> hang when the last child has more data to write to the parent than fits
> in the pipe buffer.
> When the last child's output can all fit in the pipe buffer, it can
> finish its writing to the pipe, and then it exits, closing the last open
> copy of the write descriptor going to C4, so C4 gets EOF and can do its
> sort and write, and then when it exits, the last open copy of the write
> descriptor going to C3 is closed so C3 gets EOF, and so on.

> The fix, obviously, is for each child to close the file streams
> connecting it to its predecessor — as shown by the `#ifdef FIX_BUG`
> code block in `make_kid()`.
> Note that I needed to (or, at least, did) change the interface to
> `make_kid()`.
> I also did some newline removal so that I could print without too many
> lines of output (that is, using one not two lines of output per
> message).
> At first, I was puzzled by seeing output like:

>     '1
>     ''2
>     ''3

> but that was a consequence of you printing using a format string "'%s'"
> in distribute() where the string contains a number and a newline (and
> without a newline at the end of the format).
> I've modified the format string in there, but the string minus the
> newline is still printed in the single quotes, with a newline after it.

> Note that the children must print diagnostics to stderr — stdout goes
> back to the parent process and children writing there confuses things.

> With the fix in place, the grep'd output looks like:

>     Child 24615 created
>     Child 24617 created
>     Child 24618 created
>     Child 24619 created
>     Child 24620 created
>     Distribution complete
>     24617: all lines read
>     24620: all lines read
>     24620: all lines sorted
>     24617: all lines sorted
>     24618: all lines read
>     24619: all lines read
>     24618: all lines sorted
>     24619: all lines sorted
>     24615: all lines read
>     24615: all lines sorted
>     24617: all lines written to parent
>     24618: all lines written to parent
>     24619: all lines written to parent
>     24620: all lines written to parent
>     24615: all lines written to parent
>     Merge complete
>     Child 24620 exited with status 0x0000
>     Child 24619 exited with status 0x0000
>     Child 24618 exited with status 0x0000
>     Child 24617 exited with status 0x0000
>     Child 24615 exited with status 0x0000

> In retrospect (with the benefit of 20/20 hindsight), the output from the
> unfixed code on a small data set could have been a giveaway:

>     Child 25476 created
>     Child 25477 created
>     Child 25478 created
>     Child 25479 created
>     Child 25480 created
>     Distribution complete
>     25480: all lines read
>     25480: all lines sorted
>     25480: all lines written to parent
>     25479: all lines read
>     25479: all lines sorted
>     25479: all lines written to parent
>     25478: all lines read
>     25478: all lines sorted
>     25478: all lines written to parent
>     25477: all lines read
>     25477: all lines sorted
>     25477: all lines written to parent
>     25476: all lines read
>     25476: all lines sorted
>     25476: all lines written to parent
>     Merge complete
>     Child 25480 exited with status 0x0000
>     Child 25479 exited with status 0x0000
>     Child 25478 exited with status 0x0000
>     Child 25477 exited with status 0x0000
>     Child 25476 exited with status 0x0000

> Notice how the children are completing synchronously, C5 before C4
> before … C1.
> That's because of how the EOF is not detected by C4 until C5 exits, etc.
> That pattern was systematic on the small runs.
> It took me a while to work it out — it wasn't that information that
> gave the game away, but it reinforces the conclusion.

> So, when using fork and pipes, make sure you spend enough time closing
> the unwanted file streams and file descriptors.

Since sending the email response above, I've tested it on random numbers
between -10000 and +10000 in sizes up to 10,000,000.  It takes its time
on such large data sets, though most of the time is in the
communications between processes — writing to distribute the data, and
reading to merge the results.

The debugging output should include the actual line counts in the 'all
lines read' etc messages.
It should probably also allow the lower-level (line-level) diagnostics
to be turned on when (if) needed, rather than generating such vast
quantities of data automatically.

