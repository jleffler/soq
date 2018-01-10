# Using `inline` with `extern` declarations in C

See also:

* [extern inline](https://stackoverflow.com/questions/216510-inline) — SO'6510.
* [Is "inline" without "static" or "extern" ever useful in C99?](https://stackoverflow.com/questions/6312597) — SO'2597.
* [How to declare an inline function in a C99 multi-file project?](https://stackoverflow.com/questions/5229343) — SO'9343.
* [What's the difference between static inline, extern inline, and a normal inline function?](https://stackoverflow.com/questions/25000497) — SO'0497.
* [Differentiate `extern inline` and `inline` in C](https://stackoverflow.com/questions/48192187/differentiate-extern-inline-and-inline-in-c) — SO'2187.

### Motivation

The code from blame-1.3.1.tar.gz downloaded from
https://blame.sourceforge.net/ doesn't link on macOS 10.13.2 using GCC
7.2.0 as the compiler.
The code was released in 2006; there is no more recent release.

The problem is in the library code for `argp` argument parsing
(`blame-1.3.1/lib/argp-*.[ch]`).
That code is, itself, an extract of code from Glibc, which complicates
the setup.
The immediate problem is that the files `argp-fmtstream.o` and
`argp-help.o` both end up defining a set of functions, and both object
files are linked into a single object file, and those functions are
defined with `inline` at times.
(To confuse things further, the files `argp-fs-xinl.c` and `argp-xinl.c`
also seem to try to create object files with the definitions of the
functions in situ.)

The code almost seems like it is obfuscated; it has weak symbol
management, and it uses macros to control the linkage of the inline
functions.

### Partial discussion

The answers to SO'6510 explain how Standard C (C99) and GNU C (before
C99) differ in their handling of `inline` functions.
The breakage is almost certainly due to this difference.

This directory tries to elaborate on the issues for personal
understanding, while trying to attain MCVE ([Minimal, Complete,
Verifiable Example](https://stackoverflow.com/help/mcve)) status.

### Setup

There are three sets of source files:

* `g90-*.[ch]` — a set of files using GNU `inline` technology from prior to C99.
* `c11-*.[ch]` — a matching set of files using C99/C11 `inline` technology.
* `program.c` — a sample program which attempts to use the `inline` functions.

With the `g90-*` and `c11-*` sets of files (prefix `xyz-`), there are:

* `xyz-inline.h` — a header file containing `inline` function
        definition `fn_inline()`.
* `xyz-extern.h` — a header declaring functions `fn_regular1()` and
        `fn_regular2()`.
* `xyz-user1.c` — a source file defining function `fn_regular1()` and
        using `inline` function `fn_inline()`.
* `xyz-user2.c` — a source file defining function `fn_regular2()` and
        using `inline` function `fn_inline()`.
* `xyz-define.c` — a source file that forces the definition of
        `fn_inline()`.

The code in `program.[ch]` directly includes either `g90-inline.h` or
`c11-inline.h` via macro definitions:

    #ifdef TEST_G90
    #define INLINE_HDR "g90-inline.h"
    #define EXTERN_HDR "g90-extern.h"
    #else
    #define INLINE_HDR "c11-inline.h"
    #define EXTERN_HDR "c11-extern.h"
    #endif
    #include INLINE_HDR
    #include EXTERN_HDR

Other than selecting the header, it is common code that uses both
`fn_regular1()` and `fn_regular2()` and calls `fn_inline()` directly as well.

There will be rules to build `g90-program.c` and `c11-program.c` by
linking them to `program.c`.
The macros in the makefile should allow most variants to be built.

