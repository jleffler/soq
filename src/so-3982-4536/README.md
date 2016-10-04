# SO 3982-4536

### `tsv19`

The question is marginally interesting and tsv19.c was an attempt to
resolve it but it doesn't insist on tabs.

### `tsv23`

The file tsv23.c insists on tab delimiters.

Initially, the code didn't work when compiled with GCC 6.2.0 on macOS
Sierra 10.12 with optimization levels set `-O3` or `-O2`, but `-O1` let
it work, as did compiling with Clang from XCode 8.
However, the GCC bug submission process eventually pointed out the
error.
Using `char delim;` and reading with `%1[\n\t\r]` overwrites one byte
after `delim`, which got to be the first byte of `offset` when optimized
enough.

