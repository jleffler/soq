# SO 3982-4536

### `tsv19`

The question is marginally interesting and tsv19.c was an attempt to
resolve it but it doesn't insist on tabs.

### `tsv23`

The file tsv23.c attempts to insist on tabs, and the code didn't work
when compiled with GCC 6.2.0 on macOS Sierra 10.12 with optimization
levels set `-O3` or `-O2`.
Using `-O1` lets it work, as does compiling with Clang from XCode 8.

### GCC Bug Chase

The file gccbug.c is an attempt to distill the problem into a bug report
for submission to the GCC team.
It simplifies the problem by reducing the number of columns from 31
(example.tsv) to 5 (gccbug.tsv).
In fact, it only needs one line of data.

The script `check-bug.sh` runs both clang and gcc on the current
gccbug.c code and runs the program on the minimal test data -
gccbug.tsv.

