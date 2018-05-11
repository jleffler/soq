### Stack Overflow Question 5011-0992

[SO 5011-0992](https://stackoverflow.com/q/50110992) &mdash;
Why does forking my process cause the file to be read infinitely

This was puzzling — and surprising that it produced a problem on Linux
(with the GNU C Library).

Then there was a second question: [Unwanted child processes being
created while file
reading](https://stackoverflow.com/questions/50244579/) with basically
the same problem showing up.
(SO 5024-4579 is now a duplicate of SO 5011-0992.)

[Bug 23151](https://sourceware.org/bugzilla/show_bug.cgi?id=23151) was
entered against GLIBC, and promptly rejected.
My answer here deconstructs a section of the POSIX standard.
It remains surprising to me that GLIBC behaves as it does, but there is
room to think it remains permissible according to POSIX.

* `neof11.c`

  This is the original code from the OP.
  It does reproduce the problem.

* `neof19.c`

  Like `neof97.c` but with an extra `fclose()` in the child.
  This does not reproduce the problem.

* `neof67.c`

  Opening and reading a file, instead of reopening standard input.
  This reproduces the problem.

* `neof97.c`

  Reopening standard input to use a file.
  This reproduces the problem.

### Answer from Stack Overflow

I am surprised that there is a problem, but it does seem to be a problem
on Linux (I tested on Ubuntu 16.04 LTS running in a VMWare Fusion VM on
my Mac) — but it was not a problem on my Mac running macOS 10.13.4
(High Sierra), and I wouldn't expect it to be a problem on other
variants of Unix either.

As I noted in a
[comment](https://stackoverflow.com/questions/50110992/why-does-forking-my-process-cause-the-file-to-be-read-infinitely#comment87240933_50111085):

> There's an open file description and an open file descriptor behind
> each stream.
> When the process forks, the child has its own set of open file
> descriptors (and file streams), but each file descriptor in the child
> shares the open file description with the parent.
> ***IF*** (and that's a big 'if') the child process closing the file
> descriptors first did the equivalent of `lseek(fd, 0, SEEK_SET)`, then
> that would also position the file descriptor for the parent process,
> and that could lead to an infinite loop.
> However, I've never heard of a library that does that seek; there's no
> reason to do it.

See POSIX
[`open()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html)
and
[`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html)
for more information about open file descriptors and open file
descriptions.

The open file descriptors are private to a process; the open file
descriptions are shared by all copies of the file descriptor created by
an initial 'open file' operation.
One of the key properties of the open file description is the current
seek position.
That means that a child process can change the current seek position for
a parent — because it is in the shared open file description.

### `neof97.c`

I used the following code — a mildly adapted version of the original
that compiles cleanly with rigorous compilation options:

    #include "posixver.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <unistd.h>

    enum { MAX = 100 };

    int main(void)
    {
        if (freopen("input.txt", "r", stdin) == 0)
    	    return 1;
        char s[MAX];
        for (int i = 0; i < 30 && fgets(s, MAX, stdin) != NULL; i++)
        {
            // Commenting out this region fixes the issue
            int status;
            pid_t pid = fork();
            if (pid == 0)
            {
                exit(0);
            }
            else
            {
                waitpid(pid, &status, 0);
            }
            // End region
            printf("%s", s);
        }
        return 0;
    }

One of the modifications limits the number of cycles (children) to just
30.
I used a data file with 4 lines of 20 random letters plus a newline (84
bytes total):

    ywYaGKiRtAwzaBbuzvNb
    eRsjPoBaIdxZZtJWfSty
    uGnxGhSluywhlAEBIXNP
    plRXLszVvPgZhAdTLlYe

I ran the command under `strace` on Ubuntu:

    $ strace -ff -o st-out -- neof97
    ywYaGKiRtAwzaBbuzvNb
    eRsjPoBaIdxZZtJWfSty
    uGnxGhSluywhlAEBIXNP
    plRXLszVvPgZhAdTLlYe
    …
    uGnxGhSluywhlAEBIXNP
    plRXLszVvPgZhAdTLlYe
    ywYaGKiRtAwzaBbuzvNb
    eRsjPoBaIdxZZtJWfSty
    $

There were 31 files with names of the form `st-out.808##` where the
hashes were 2-digit numbers.
The main process file was quite large; the others were small, with one
of the sizes 66, 110, 111, or 137:

    $ cat st-out.80833
    lseek(0, -63, SEEK_CUR)                 = 21
    exit_group(0)                           = ?
    +++ exited with 0 +++
    $ cat st-out.80834
    lseek(0, -42, SEEK_CUR)                 = -1 EINVAL (Invalid argument)
    exit_group(0)                           = ?
    +++ exited with 0 +++
    $ cat st-out.80835
    lseek(0, -21, SEEK_CUR)                 = 0
    exit_group(0)                           = ?
    +++ exited with 0 +++
    $ cat st-out.80836
    exit_group(0)                           = ?
    +++ exited with 0 +++
    $

It just so happened that the first 4 children each exhibited one of the
four behaviours — and each further set of 4 children exhibited the
same pattern.

This shows that three out of four of the children were indeed doing an
`lseek()` on standard input before exiting.
Obviously, I have now seen a library do it.
I have no idea why it is thought to be a good idea, though, but
empirically, that is what is happening.

### `neof67.c`

This version of the code, using a separate file stream (and file
descriptor) and `fopen()` instead of `freopen()` also runs into the
problem.

    #include "posixver.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <unistd.h>

    enum { MAX = 100 };

    int main(void)
    {
        FILE *fp = fopen("input.txt", "r");
        if (fp == 0)
            return 1;
        char s[MAX];
        for (int i = 0; i < 30 && fgets(s, MAX, fp) != NULL; i++)
        {
            // Commenting out this region fixes the issue
            int status;
            pid_t pid = fork();
            if (pid == 0)
            {
                exit(0);
            }
            else
            {
                waitpid(pid, &status, 0);
            }
            // End region
            printf("%s", s);
        }
        return 0;
    }

This also exhibits the same behaviour, except that the file descriptor
on which the seek occurs is `3` instead of `0`.
So, two of my hypotheses are disproven — it's related to `freopen()`
and `stdin`; both are shown incorrect by the second test code.

### Preliminary diagnosis

IMO, this is a bug.
You should not be able to run into this problem.
It is most likely a bug in the Linux (GNU C) library rather than the
kernel.
It is caused by the `lseek()` in the child processes.
It is not clear (because I've not gone to look at the source code) what
the library is doing or why.

<hr>

## GLIBC Bug 23151

GLIBC [Bug 23151](https://sourceware.org/bugzilla/show_bug.cgi?id=23151)
- A forked process with unclosed file does lseek before exit and can
cause infinite loop in parent I/O.

The bug was created 2019-05-08 US/Pacific, and was closed as INVALID by
2018-05-09.
The reason given was:

> Please read
<http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_05_01>,
especially this paragraph:

> Note that after a `fork()`, two handles exist where one existed before.  […]

## POSIX

The complete section of POSIX referred to (apart from verbiage noting
that this is not covered by the C standard) is this:

> ### [2.5.1 Interaction of File Descriptors and Standard I/O Streams](http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_05_01)

> An open file description may be accessed through a file descriptor,
> which is created using functions such as
> [`open()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html)
> or
> [`pipe()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pipe.html),
> or through a stream, which is created using functions such as
> [`fopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html)
> or
> [`popen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/popen.html).
> Either a file descriptor or a stream is called a "handle" on the open
> file description to which it refers; an open file description may have
> several handles.

> Handles can be created or destroyed by explicit user action, without
> affecting the underlying open file description.
> Some of the ways to create them include
> [`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html),
> [`dup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html),
> [`fdopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fdopen.html),
> [`fileno()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fileno.html),
> and
> [`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html).
> They can be destroyed by at least
> [`fclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html),
> [`close()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html),
> and the
> [`exec`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)
> functions.


> A file descriptor that is never used in an operation that could affect
> the file offset (for example,
> [`read()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html),
> [`write()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html),
> or
> [`lseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/lseek.html))
> is not considered a handle for this discussion, but could give rise to
> one (for example, as a consequence of
> [`fdopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fdopen.html),
> [`dup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html),
> or
> [`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html)).
> This exception does not include the file descriptor underlying a
> stream, whether created with
> [`fopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html)
> or
> [`fdopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fdopen.html),
> so long as it is not used directly by the applic

This exception does not include the file descriptor underlying a stream,
whether created with
[`fopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html)
or
[`fdopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fdopen.html),
so long as it is not used directly by the application to affect the file
offset.
The
[`read()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html)
and
[`write()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html)
functions implicitly affect the file offset;
[`lseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/lseek.html)
explicitly affects it.

> The result of function calls involving any one handle (the "active
> handle") is defined elsewhere in this volume of POSIX.1-2017, but if
> two or more handles are used, and any one of them is a stream, the
> application shall ensure that their actions are coordinated as
> described below.
> If this is not done, the result is undefined.

> A handle which is a stream is considered to be closed when either an
> [`fclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html),
> or
> [`freopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/freopen.html)
> with non-full<sup>(1)</sup> filename, is executed on it (for
> [`freopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/freopen.html)
> with a null filename, it is implementation-defined whether a new
> handle is created or the existing one reused), or when the process
> owning that stream terminates with
> [`exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exit.html),
> [`abort()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/abort.html),
> or due to a signal.
> A file descriptor is closed by
> [`close()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html),
> [`_exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/_exit.html),
> or the
> [`exec()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.ht



> A handle which is a stream is considered to be closed when either an
> [`fclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fclose.html),
> or
> [`freopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/freopen.html)
> with non-full<sup>(1)</sup> filename, is executed on it (for
> [`freopen()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/freopen.html)
> with a null filename, it is implementation-defined whether a new
> handle is created or the existing one reused), or when the process
> owning that stream terminates with
> [`exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exit.html),
> [`abort()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/abort.html),
> or due to a signal.
> A file descriptor is closed by
> [`close()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/close.html),
> [`_exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/_exit.html),
> or the
> [`exec()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)
> functions when FD_CLOEXEC is set on that file descriptor.

<sup>(1)</sup> _[sic] Using 'non-full' is probably a typo for 'non-null'._

> For a handle to become the active handle, the application shall ensure
> that the actions below are performed between the last use of the
> handle (the current active handle) and the first use of the second
> handle (the future active handle).
> The second handle then becomes the active handle.
> All activity by the application affecting the file offset on the first
> handle shall be suspended until it again becomes the active file
> handle.
> (If a stream function has as an underlying function one that affects
> the file offset, the stream function shall be considered to affect the
> file offset.)

> The handles need not be in the same process for these rules to apply.

> Note that after a
> [`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html),
> two handles exist where one existed before.
> The application shall ensure that, if both handles can ever be
> accessed, they are both in a state where the other could become the
> active handle first.
> The application shall prepare for a
> [`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html)
> exactly as if it were a change of active handle.
> (If the only action performed by one of the processes is one of the
> [`exec()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)
> functions or
> [`_exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/_exit.html)
> (not
> [`exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exit.html)),
> the handle is never accessed in that process.)

> For the first handle, the first applicable condition below applies.
> After the actions required below are taken, if the handle is still
> open, the application can close it.

> * If it is a file descriptor, no action is required.

> * If the only further action to be performed on any handle to this
>   open file descriptor is to close it, no action need be taken.

> * If it is a stream which is unbuffered, no action need be taken.

> * If it is a stream which is line buffered, and the last byte written
>   to the stream was a `<newline>` (that is, as if a:

>         putc('\n')

>    was the most recent operation on that stream), no action need be taken.

> * If it is a stream which is open for writing or appending (but not
>   also open for reading), the application shall either perform an
>   [`fflush()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fflush.html),
>   or the stream shall be closed.

> * If the stream is open for reading and it is at the end of the file
>   ([`feof()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/feof.html)
>   is true), no action need be taken.

> * If the stream is open with a mode that allows reading and the
>   underlying open file description refers to a device that is capable
>   of seeking, the application shall either perform an
>   [`fflush()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fflush.html),
>   or the stream shall be closed.

> For the second handle:

> * If any previous active handle has been used by a function that
>   explicitly changed the file offset, except as required above for the
>   first handle, the application shall perform an
>   [`lseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/lseek.html)
>   or
>   [`fseek()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fseek.html)
>   (as appropriate to the type of handle) to an appropriate location.

> If the active handle ceases to be accessible before the requirements
> on the first handle, above, have been met, the state of the open file
> description becomes undefined.
> This might occur during functions such as a
> [`fork()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fork.html)
> or
> [`_exit()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/_exit.html).


> The
> [`exec()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/exec.html)
> functions make inaccessible all streams that are open at the time they
> are called, independent of which streams or file descriptors may be
> available to the new process image.

> When these rules are followed, regardless of the sequence of handles
> used, implementations shall ensure that an application, even one
> consisting of several processes, shall yield correct results: no data
> shall be lost or duplicated when writing, and all data shall be
> written in order, except as requested by seeks.
> It is implementation-defined whether, and under what conditions, all
> input is seen exactly once.

> Each function that operates on a stream is said to have zero or more
> "underlying functions".
> This means that the stream function shares certain traits with the
> underlying functions, but does not require that there be any relation
> between the implementations of the stream function and its underlying
> functions.

## Exegesis

That is hard reading!
If you're not clear on the distinction between open file descriptor and
open file description, read the specification of `open()` and `fork()`
(and `dup()` or
[`dup2()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup2.html)).
The definitions for [file
descriptor](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_166)
and [open file
description](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_258)
are also relevant, if terse.

In the context of the code in this question (and also for [Unwanted
child processes being created while file
reading](https://stackoverflow.com/questions/50244579/)), we have a file
stream handle open for reading only which has not yet encountered EOF
(so `feof()` would not return true, even though the read position is at
the end of the file).

One of the crucial parts of the specification is: _The application shall
prepare for a `fork()` exactly as if it were a change of active handle._

This means that the steps outlined for 'first file handle' are relevant,
and stepping through them, the first applicable condition is the last:

> * If the stream is open with a mode that allows reading and the
>   underlying open file description refers to a device that is capable
>   of seeking, the application shall either perform an `fflush()`, or
>   the stream shall be closed.

If you look at the definition for
[`fflush()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fflush.html),
you find:

> If _stream_ points to an output stream or an update stream in which
> the most recent operation was not input, `fflush()` shall cause any
> unwritten data for that stream to be written to the file, [CX] ⌦  and
> the last data modification and last file status change timestamps of
> the underlying file shall be marked for update.

> For a stream open for reading with an underlying file description, if
> the file is not already at EOF, and the file is one capable of
> seeking, the file offset of the underlying open file description shall
> be set to the file position of the stream, and any characters pushed
> back onto the stream by
> [`ungetc()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ungetc.html)
> or
> [`ungetwc()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/ungetwc.html)
> that have not subsequently been read from the stream shall be
> discarded (without further changing the file offset).  ⌫

It isn't exactly clear what happens if you apply `fflush()` to an input
stream associated with a non-seekable file, but that isn't our immediate
concern.
However, if you're writing generic library code, then you might need to
know whether the underlying file descriptor is seekable before doing a
`fflush()` on the stream.
Alternatively, use `fflush(NULL)` to have the system do whatever is
necessary for all I/O streams, noting that this will lose any
pushed-back characters (via `ungetc()` etc).

The `lseek()` operations shown in the `strace` output seem to be
implementing the `fflush()` semantics associating the file offset of the
open file description with the file position of the stream.

So, for the code in this question, it seems that `fflush(stdin)` is
necessary before the `fork()` to ensure consistency.
Not doing that leads to _undefined behaviour_ ('if this is not done, the
result is undefined') — such as looping indefinitely.

