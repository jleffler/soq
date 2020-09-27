### Stack Overflow Question 0067-5039

[SO 0067-5039](https://stackoverflow.com/q/00675039) &mdash;
How can I create a directory tree in C++/Linux?

The file `mkpath.c` contains the updated code from the
[answer](https://stackoverflow.com/a/675193/15168) with the race condition
fixed.

The other files needed are also present here.
Most of them are also present in the `src/libsoq` directory too.

## Answer

With C++17 or later, there's the standard header `<filesystem>` with
function
[`std::filesystem::create_directories`](https://en.cppreference.com/w/cpp/filesystem/create_directory)
which should be used in modern C++ programs.
The C++ standard functions do not have the POSIX-specific explicit
permissions (mode) argument, though.

However, here's a C function that can be compiled with C++ compilers.

    ...code from mkpath.c...

The macros `STRDUP()` and `FREE()` are error-checking versions of
`strdup()` and `free()`, declared in `emalloc.h` (and implemented in
`emalloc.c` and `estrdup.c`).
The `"sysstat.h"` header deals with broken versions of `<sys/stat.h>`
and can be replaced by `<sys/stat.h>` on modern Unix systems (but there
were many issues back in 1990).
And `"mkpath.h"` declares `mkpath()`.

The change between v1.12 (original version of the answer) and v1.13
(amended version of the answer) was the test for `EEXIST` in
`do_mkdir()`.
This was pointed out as necessary by
[Switch](https://stackoverflow.com/users/205938/switch) &mdash; thank
you, Switch.
The test code has been upgraded and reproduced the problem on a MacBook
Pro (2.3GHz Intel Core i7, running Mac OS X 10.7.4), and suggests that
the problem is fixed in the revision (but testing can only show the
presence of bugs, never their absence).
The code shown is now v1.16; there have been cosmetic or administrative
changes made since v1.13 (such as use `mkpath.h` instead of `jlss.h` and
include `<unistd.h>` unconditionally in the test code only).
It's reasonable to argue that `"sysstat.h"` should be replaced by
`<sys/stat.h>` unless you have an unusually recalcitrant system.

_(You are hereby given permission to use this code for any purpose with attribution.)_

This code is available in my [SOQ](https://github.com/jleffler/soq)
(Stack Overflow Questions) repository on GitHub as files `mkpath.c` and
`mkpath.h` (etc.) in the
[src/so-0067-5039](https://github.com/jleffler/soq/tree/master/src/so-0067-5039)
sub-directory.
