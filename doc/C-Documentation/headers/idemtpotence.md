# Idempotence

If a particular header file is included more than once in a translation
unit (TU), there should not be any compilation problems.
This is termed 'idempotence'; your headers should be idempotent.
Think how difficult life would be if you had to ensure that `#include
<stdio.h>` was only included once.

There are two ways to achieve idempotence: header guards and the
`#pragma once` directive.

## Header guards

Header guards are simple and reliable and conform to the C standard.
The first non-comment lines in a header file should be of the form:

    #ifndef UNIQUE_ID_FOR_HEADER
    #define UNIQUE_ID_FOR_HEADER

The last non-comment line should be `#endif`, optionally with a comment after it: 

    #endif /* UNIQUE_ID_FOR_HEADER */

All the operational code, including other `#include` directives, should
be between these lines.

Each name must be unique.
Often, a name scheme such as `HEADER_H_INCLUDED` is used.
Some older code uses a symbol defined as the header guard (e.g. `#ifndef
BUFSIZ` in `<stdio.h>`), but it is not as reliable as a unique name.

One option would be to use a generated MD5 (or other) hash for the
header guard name.
You should avoid emulating the schemes used by system headers which
frequently use names reserved to the implementation &mdash; names
starting with an underscore followed by either another underscore or an
upper-case letter.

## The `#pragma once` Directive

Alternatively, some compilers support the `#pragma once` directive which
has the same effect as the three lines shown for header guards.

    #pragma once

The compilers which support `#pragma once` include MS Visual Studio and
GCC and Clang.
However, if portability is a concern, it is better to use header guards,
or use both.
Modern compilers (those supporting C89 or later) are required to ignore,
without comment, pragmas that they do not recognize ('Any such pragma
that is not recognized by the implementation is ignored') but old
versions of GCC were not so indulgent.
