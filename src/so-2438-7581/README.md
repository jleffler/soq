## [SO 2438-7581](https://stackoverflow.com/q/24387581) Can code for a library function be contained several times in an executable?

### Question

I am wondering if it could happen that, in a program written in C, the
code for a function from a static library is contained twice in an
executable.

For example, assume that you create a static library lib_a which uses
functions from another static library lib_b.
Then you create a programm that uses both lib_a and lib_b.
Would the executable for this programm contain the code for the
functions from lib_b twice?
If not, how is this avoided?

My understanding of the linker and of the format of an executable is
very rough; sorry if this question is quite basic.
Maybe somebody knows a good reference for this topic?
I have searched several books on C, but I can't find the answer.

### Observation

The answer text is not an easy read, not helped by an absence of
examples.
Also, this is a curious setup because there seems to be an RCS
repository backing up the code on Osiris, but that RCS directory is
specifically excluded by .gitignore.
That explains the RCS version information in the C source and headers.

### Answer

Suppose library `lib_a.a` (a Unix-style static library) contains a
function `a1_function()`, and `a1_function()` calls another function
`b1_function()` that is found in `lib_b.a`.

Suppose your program calls `a1_function()` directly, and also calls
another function, `b2_function()`, from `lib_b.a` directly.

Your linker command might look like:

    c99 -o program program.c -l_a -l_b

You cannot link your program without mentioning both `lib_a.a` (as
`-l_a` or by pathname) and `lib_b.a`.
Even if you later revise your program so it no longer calls
`b2_function()`, you will still need both libraries, because `lib_a.a`
only contains its own code, not the code that is in `lib_b.a`.

With shared libraries, it might be possible for to link the revised
program (with no direct call to `b2_function()`) with just `-l_a` and
rely on the metadata in `lib_a.so` to tell the linker to link with
`lib_b.so` too.

If you revise `lib_a.a` so it contains not only `a1_function()` but also
the code for `b1_function()` and any supporting code necessary to
support it (which will exclude `b2_function()` for the purposes of this
discussion).
Then the program that calls just `a1_function()` would not need
`lib_b.a` at all.
However, if the program calls `b2_function()`, then you will need to
link with both libraries.
The material from `lib_a.a` that satisfied `b1_function()` and its
dependencies will come from `lib_a.a`; the function `b2_function()` and
any supporting material it needs that was not provided by `lib_a.a` will
also be linked in.

If the code from `lib_b` included in `lib_a.a` is different from the
'same' code in `lib_b.a`, then you have potential for aberrant
behaviour.
An extreme case of this might be an object file, `b_file1.c`, which
contains a number of functions including `b1_function()` and
`b2_function()`.
When compiled for inclusion in `lib_a.a`, the `b2_function()` is not
included; when compiled for inclusion in `lib_b.a`, the `b2_function()`
_is_ included (and `b1_function()` is always included).
Then you will fail to link the program when it calls `b2_function()`
because the program will link `b_file1.o` from `lib_a.a` to satisfy the
`b1_function()` reference, but the linker will also try to link
`b_file1.o` from `lib_b.a` to satisfy the `b2_function()` reference.
This leads to two definitions of function `b1_function()`, and that
isn't allowed (under static library linking rules).
With shared libraries, it isn't entirely clear what would happen, but
there are a number of ways that things could go wrong (but errors for
doubly-defined symbols wouldn't be one of those ways).

Note that you should studiously avoid circumstances where a function in
`lib_a.a` calls a function in `lib_b.a` and a function in `lib_b.a`
calls a function in `lib_a.a`.
This leads to circular dependency problems, and can mean you need to
list libraries multiple times on a command line.
It would be far better to create a single library, `lib_c.a` containing
the material from both `lib_a.a` and `lib_b.a` and link with that, once.

