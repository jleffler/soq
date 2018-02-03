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

The rule also applies if you duplicate the descriptors with either
[`dup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/dup.html)
or
[`fcntl()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/fcntl.html)
with `F_DUPFD`

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
