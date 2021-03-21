#!/bin/sh
#
# Standard blurb about C indentation style for SO

cat <<'EOF'
Please use a more orthodox indentation style for C.
I strongly recommend either Allmann (which is what I use, more or less)
or some version of 1TBS (which is used by many other people) See
Wikipedia on [Indetation
Style](https://en.wikipedia.org/wiki/Indentation_style) for information
about the variants.

The Pico style, expecially with multiple `}` markers on a single line, is anathema in C.

Multiple close braces on a single line is a no-no;
multiple consecutive close braces at the same indent level is another.

EOF
