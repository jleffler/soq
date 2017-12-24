#!/bin/sh
#
# Standard message with x-refs for the pipe rule-of-thumb.

cat <<'EOF'
You aren't closing enough file descriptors in the child.
**Rule of thumb**: If you
[`dup2()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup2.html)
one end of a pipe to standard input or standard output, close both ends
of the pipe as soon as possible.
That means before using any of the
[`exec*()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/execvp.html)
family of functions in particular.

It also includes using
[`dup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)
or
[`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html)
with `F_DUPFD`.

EOF
