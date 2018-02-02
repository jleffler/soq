#!/bin/bash
#
# Standard diatribe on C getchar() returning an int, not a char.

cat <<'EOF'
Note that `getchar()` and relatives return an `int` and not a
`char`.  That's because they have to be able to return any valid
`char` value plus a distinct value, EOF.  Using `char` instead of
`int` leads to one of two problems.  If plain `char` is a signed
type, then some valid character (often ÿ, y-umlaut, 0xFF,
U+00FF, LATIN SMALL LETTER Y WITH DIAERESIS) is mis-recognized as
EOF.  If plain `char` is an unsigned type, then the value
assigned to the `char` variable is never recognized as EOF.
Neither is really acceptable.
EOF
