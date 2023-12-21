# Length modifiers for `printf()`

The C99 and C11 standards specify the following length modifiers for `printf()`; their meanings are:

| Modifier | Modifies            | Applies to                                                    |
|----------|---------------------|---------------------------------------------------------------|
| hh       | d, i, o, u, x, or X | `char`, `signed char` or `unsigned char`
| h        | d, i, o, u, x, or X | `short int` or `unsigned short int`
| l        | d, i, o, u, x, or X | `long int` or `unsigned long int`
| l        | a, A, e, E, f, F, g, or G  | `double` (for compatibility with `scanf()`; undefined in C90)
| ll       | d, i, o, u, x, or X | `long long int` or `unsigned long long int`
| j        | d, i, o, u, x, or X | `intmax_t` or `uintmax_t`
| z        | d, i, o, u, x, or X | `size_t` or the corresponding signed type (`ssize_t` in POSIX)
| t        | d, i, o, u, x, or X | `ptrdiff_t` or the corresponding unsigned integer type
| L        | a, A, e, E, f, F, g, or G  | `long double`


If a length modifier appears with any conversion specifier other than as specified above, the behavior is undefined.

[Microsoft](https://msdn.microsoft.com/en-us/library/tcxf1dw6.aspx) specifies some different length modifiers, and explicitly does not support `hh`, `j`, `z`, or `t`.

| Modifier | Modifies            | Applies to                                                    |
|----------|---------------------|---------------------------------------------------------------|
| I32 | d, i, o, x, or X | `__int32`
| I32 | o, u, x, or X | `unsigned __int32`
| I64 | d, i, o, x, or X | `__int64`
| I64 | o, u, x, or X | `unsigned __int64`
| I | d, i, o, x, or X | `ptrdiff_t` (that is, `__int32` on 32-bit platforms, `__int64` on 64-bit platforms)
| I | o, u, x, or X | `size_t` (that is, `unsigned __int32` on 32-bit platforms, `unsigned __int64` on 64-bit platforms)
|  l or L | a, A, e, E, f, g, or G | `long double` (In Visual C++, although `long double` is a distinct type, it has the same internal representation as `double`.)
|  l or w | c or C | Wide character with `printf` and `wprintf` functions. (An `lc`, `lC`, `wc` or `wC` type specifier is synonymous with `C` in `printf` functions and with `c` in `wprintf` functions.)
| l or w | s, S, or Z | Wide-character string with `printf` and `wprintf` functions. (An `ls`, `lS`, `ws` or `wS` type specifier is synonymous with `S` in `printf` functions and with `s` in `wprintf` functions.)

Note that the `C`, `S`, and `Z` conversion specifiers and the `I`, `I32`, `I64`, and `w` length modifiers are Microsoft extensions.  Treating `l` as a modifier for `long double` rather than `double` is different from the standard, though you'll be hard-pressed to spot the difference unless `long double` has a different representation from `double`.
