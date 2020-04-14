### Stack Overflow Question 6118-1130

[SO 6118-1130](https://stackoverflow.com/q/61181130) &mdash;
How to use pipes in C with execv (No dup or dup2)


Curious constraint.
As noted in the comments, it would be possible to use `fcntl()` to
circumvent the ban on `dup()` and `dup2()`.

The `F_DUPFD` and `F_DUPFD_CLOEXEC` options allow you to simulate, more
or less, `dup()` or `dup2()`.
Note, however, that the behaviour is neither like `dup()` nor `dup2()`
precisely.
You specify a minimum file descriptor number, and `fcntl()` does not
close any file descriptor, unlike `dup2()`.
You'd have to treat it more like `dup()` than `dup2()` — you'd close
the target descriptor and specify the target descriptor as the minimum
to `fcntl()`.
However, this is clearly against the spirit of the ban.

The code is basically straight-forward.
The key is passing to the children a string argument specifying the file
descriptor for the reader to read from and for the writers to write to.
The rest is simple mechanics.
