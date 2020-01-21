#!/bin/sh
#
# Standard message with x-refs for the pipe rule-of-thumb.

# Actually, two standard messages, one for answers (-a, and the
# default), one for comments (-c).  The problem is that comments are
# limited to 600 characters.

usage() { echo "Usage: $(basename "$0" .sh) [-ac]" >&2; exit 1; }

mode="answer"
while getopts ac opt
do
    case "$opt" in
    (a) mode="answer";;
    (c) mode="comment";;
    (*) usage;
    esac
done

shift $(($OPTIND - 1))
[ $# = 0 ] || usage

if [ "$mode" = "answer" ]
then

cat <<'EOF'
You aren't closing enough file descriptors in the child process.

<hr>

**Rule of thumb**: If you
[`dup2()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup2.html)
one end of a pipe to standard input or standard output, close both of the
original file descriptors returned by
[`pipe()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pipe.html)
as soon as possible.
In particular, you should close them before using any of the
[`exec*()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/execvp.html)
family of functions.

The rule also applies if you duplicate the descriptors with either
[`dup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)
or
[`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html)
with `F_DUPFD` or `F_DUPFD_CLOEXEC`.

<hr>

If the parent process will not communicate with any of its children via
the pipe, it must ensure that it closes both ends of the pipe early
enough (before waiting, for example) so that its children can receive
EOF indications on read (or get SIGPIPE signals or write errors on
write), rather than blocking indefinitely.
Even if the parent uses the pipe without using `dup2()`, it should
normally close at least one end of the pipe — it is extremely rare for
a program to read and write on both ends of a single pipe.

Note that the `O_CLOEXEC` option to 
[`open()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html),
and the `FD_CLOEXEC` and `F_DUPFD_CLOEXEC` options to `fcntl()` can also factor
into this discussion.

If you use
[`posix_spawn()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/posix_spawn.html)
and its extensive family of support functions (21 functions in total),
you will need to review how to close file descriptors in the spawned process
([`posix_spawn_file_actions_addclose()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/posix_spawn_file_actions_addclose.html),
etc.).

Note that using `dup2(a, b)` is safer than using `close(b); dup(a);`
for a variety of reasons.
One is that if you want to force the file descriptor to a larger than
usual number, `dup2()` is the only sensible way to do that.
Another is that if `a` is the same as `b` (e.g. both `0`), then `dup2()`
handles it correctly (it doesn't close `b` before duplicating `a`)
whereas the separate `close()` and `dup()` fails horribly.
This is an unlikely, but not impossible, circumstance.

EOF

else

# Beware: even flattened, this is about 595 characters long out of the
# 600 allowed by SO.  Compressing it further is tricky.  Note that dup()
# is documented on the same page as dup2().

tr -s ' \n\t' '   ' <<'EOF'
You aren't closing enough file descriptors in the child.

**Rule of thumb**: If you
[`dup2()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup2.html)
one end of a pipe to standard input or standard output, close both of
the original file descriptors from `pipe()` as soon as possible.
In particular, that means before using any of the
[`exec*()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/execvp.html)
family of functions.

The rule also applies with either `dup()` or
[`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html)
with `F_DUPFD`.

EOF

fi
