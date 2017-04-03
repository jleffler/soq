### Stack Overflow Question 4319-0158

[SO 4319-0158](http://stackoverflow.com/q/43190158) &mdash;
How to make a process ring with fork and mkfifo?

This code substantially rewrites the whole damn thing, but once all the
assignments were correct, it pretty much worked correctly.

Having the tracking code in `stderr.c` is great, but the writing needs
to be improved.
At the moment, it does multiple write calls (via `fprintf()`) which can
lead to undesirably interleaved output in a multi-process system.
This was already done for file descriptors and writing to syslog, so it
isn't going to be hard to incorporate.

Code for `"stderr.h"` (and library code `stderr.c`) in the `../libsoq`
directory.
