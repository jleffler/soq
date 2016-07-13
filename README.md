SOQ - Stack Overflow Questions
------------------------------

A repository of material related to Stack Overflow
(http://stackoverflow.com/) questions and answers.

As of 2016-07-13, the repository has undergone extensive reorganization.
Most of the material is present in a source directory for each question,
such as src/so-3567-8399.  There are exceptions to this, both in the src
directory and in the top-level directory.  The exceptions in the top-level
will ultimately be resolved by moving the material into an appropriate
sub-directory under `src`.

For the time being, the directory names for answers are written as
so-abcd-wxyz (e.g. so-3333-8314), and will be placed in the src directory.

The `inc` top-level directory contains common headers (but the source for them is in `src/libsoq`
and `src/libcs50` or other locations as appropriate).  The `lib` top-level directory contains the
compiled libraries of common code (but the source for it is in `src/libsoq` and `src/libcs50`).
The `etc` directory contains miscellaneous files, such as the common
makefile control information and also [`valgrind`](http://valgrind.org/) suppressions
file for Mac OS X 10.11.5 (which probably just requires a rebuild of `valgrind` that has not happened yet).
