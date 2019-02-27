### Stack Overflow Question 3670-8171

[SO 3670-8171](https://stackoverflow.com/q/36708171) &mdash;
How can `openat()` avoid TOCTTOU errors?

My original answer gave no code.

### Original answer

The POSIX specification for
[`openat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/openat.html)
says:

> `int openat(int `_`fd`_`, const char *`_`path`_`, int `_`oflag`_`, ...);`

> <sup>_[…lengthy spiel on regular `open()`…]_</sup>

> The `openat()` function shall be equivalent to the `open()` function
> except in the case where `path` specifies a relative path.
> In this case the file to be opened is determined relative to the
> directory associated with the file descriptor `fd` instead of the
> current working directory.
> If the file descriptor was opened without `O_SEARCH`, the function
> shall check whether directory searches are permitted using the current
> permissions of the directory underlying the file descriptor.
> If the file descriptor was opened with `O_SEARCH`, the function shall
> not perform the check.

> The `oflag` parameter and the optional fourth parameter correspond
> exactly to the parameters of `open()`.

>If `openat()` is passed the special value `AT_FDCWD` in the `fd`
>parameter, the current working directory shall be used and the behavior
>shall be identical to a call to `open()`.

This means that if you want to place files in, or relative to, a
specific directory, you can open a file descriptor to that directory
(probably with the `O_SEARCH` option), and then specify path names
relative to that directory in the `openat()` system call.

Other `*at()` functions such as
[`fstatat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fstatat.html)
work similarly.

* How does this improve security?

First, note that the file descriptor is the file descriptor of a
directory.
At the time when the directory was opened (for reading), it existed, and
the process had permission to access the directory and the files in it.
Further, because this process has the directory open, the last
references to that directory won't vanish until the process closes the
directory file descriptor.
If it's on a mounted file system, that file system can't be unmounted
until the program terminates (because the process has the directory
open).
If the directory is moved (on the same file system), then files will
continue to be created relative to that directory in its current
position in the file system.

Things get more speculative from here on — I've not formally tested
these observations.

Even if the directory was removed, it appears that you'd be still able
to create files relative to it.
If the names are simple names (`"new_file"` or `"./new_file"`), that
should be OK.
If the names have more of a path (`"subdir/new_file"`), creating or
opening the file will fail if the directory has been removed because all
sub-directories will also have been removed.

Of course, there's
[`mkdirat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/mkdirat.html)
to create sub-directories.

Presumably, the file system has to clean up after all this, which could
be quite complex.
That means there's a chance that in fact you can't create files in a
directory for which you have an open file descriptor but for which the
name has been removed.
However, you would know that this is no longer possible, rather than
assuming that it is the same directory.

Either way, it is harder for the attacker to confuse your program into
creating files in the wrong directory, as long as you've been careful
and consistent in using the correct `*at()` functions.

One set of TOCTOU attacks is removed; those attacks that depend on the
directory being renamed (or possibly removed) and instead using a new
name (e.g. a symlink to some other location) are foiled because the
files continue to be created relative to the original directory, not
using the renamed or replacement directory.

The rationale section of the POSIX specification for `openat()` says:

> The purpose of the `openat()` function is to enable opening files in
> directories other than the current working directory without exposure
> to race conditions.
> Any part of the path of a file could be changed in parallel to a call
> to `open()`, resulting in unspecified behavior.
> By opening a file descriptor for the target directory and using the
> `openat()` function it can be guaranteed that the opened file is
> located relative to the desired directory.
> Some implementations use the `openat()` function for other purposes as
> well.
> In some cases, if the oflag parameter has the `O_XATTR` bit set, the
> returned file descriptor provides access to extended attributes.
> This functionality is not standardized here.

<hr>

There are three salient comments:


At 2017-05-05 03:28,
[cong](https://stackoverflow.com/users/2659573/cong)
[commented](https://stackoverflow.com/questions/36708171/how-can-openat-avoid-tocttou-errors#comment74631384_36725842):

>What do you mean by "confuse your program into creating files in the
>wrong directory"?
>Would you please just show us a example?

[My
response](https://stackoverflow.com/questions/36708171/how-can-openat-avoid-tocttou-errors#comment74632467_36725842)
was:

It's intricate — it'll take time and effort to produce a reasonable
example that I'm not sure I want to spend.
Basically, the problem is that if your program creates a directory
`/some/where` and tries to place files in it with
`open("/some/where/filename", …)`, but the attacker is able to move or
remove the original `/some/where` and create their own alternative, then
the program creates its file in their directory, not yours.
Fiendish attackers might even move the original `/some/where` back,
perhaps having captured a password or some critical info.
Using `openat()` carefully avoids that.

At 2017-06-26 19:48,
[mtk](https://stackoverflow.com/users/1292502/mtk)
[commented](https://stackoverflow.com/questions/36708171/how-can-openat-avoid-tocttou-errors#comment76516189_36725842):

>"Even if the directory was removed, it appears that you'd be still able
>to create files relative to it." This isn't correct, at least on Linux:
>if the (empty) directory is deleted, then trying to create a file using
>(say) openat() relative to the dirfd will fail with ENOENT.
>But the subsequent text ("That means there's a chance that in fact you
>can't create files in a directory for which you have an open file
>descriptor but for which the name has been removed.
>However, you would know that this is no longer possible, rather than
>assuming that it is the same directory.") is to the point.

<hr>

The code in `openat59.c` is part of an exercise to verify the comment
from @mtk.

Tested on a Mac running macOS Sierra 10.12.5 (using GCC 7.1.0, though
the compiler is probably immaterial), the observation that you cannot
make files in a deleted directory even with the open handle is correct.
However, that directory was not opened with `O_SEARCH`; the option is
not available on macOS (or Mac OS X).

