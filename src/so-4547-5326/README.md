### Stack Overflow Question 4547-5326

[SO 4547-5326](https://stackoverflow.com/q/45475326) &mdash;
Copy a file with buffers of different sizes for read and write

This is the trigger for the incomplete work on `unitsize.[ch]`.

The asymmetric buffering is a mainly resolveable problem.

One interesting sub-question is what happens if you use `readv()` and,
more particularly, `writev()`.
Do all the writes from separate buffers count as a single write (so if
you had a collection of fragments to write that added to up to the
output buffer size, would a single call to `writev()` count as one
buffer full, or would it be any fragmentary writes.
The cautious view is 'multiple fragments' so that the buffering and
copying has to be done by the code.

There isn't an accepted answer.
The answers presented are somewhat frgmentary.

The [`dd`](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/dd.html)
command has input and output buffer sizes that can be decoupled from each other.
