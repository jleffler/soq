#!/bin/sh
#
# Standard message with x-refs for the pipe rule-of-thumb.

# This version is too big to fit in a comment on SO.
# For a comment, drop the fcntl() URL; it is a tad esoteric.

cat <<'EOF'
You aren't closing enough file descriptors in the child.

**Rule of thumb**: If you
[`dup2()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup2.html)
one end of a pipe to standard input or standard output, close both of the
original file descriptors returned by
[`pipe()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/pipe.html)
as soon as possible.
In particular, you should close them before using any of the
[`exec*()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/execvp.html)
family of functions.

It also includes using `dup()` or
[`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html)
with `F_DUPFD`.

EOF
