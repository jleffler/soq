#!/bin/ksh
#
# @(#)$Id$
#
# Standard blurb about not using literals for filenames to fopen.

so-flatten <<'EOF'

Recommendation: you should not call a function that opens a file (such
as `fopen()` or `open()`) with a string literal for the file name.
You must check that the open succeeded, and if not, report the error (on
standard error - `stderr`) and you should include the file name in the
error message.
To avoid repetition, you should pass a variable that points to the file
name to the open function, and can then use that variable when
formatting the error message too.
For example: `const char *filename = "input.txt"; FILE *fp =
fopen(filename, "r"); if (fp == NULL) { perror(filename); return NULL; }`

EOF
