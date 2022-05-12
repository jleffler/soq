#!/bin/sh
#
# Report standard facts about factorials

cat <<'EOF'

A 32-bit integer can store factorials up to 12!
A 64-bit integer can store factorials up to 20!
A 128-bit (unsigned) integer can store factorials up to 34!
A 256-bit integer can store factorials up to 57!
A 512-bit (unsigned) integer can store factorials up to 98!

Using IEEE 754 64-bit floating-point arithmetic, you can store
approximations up to 170!  (7.257415615307994E+306)
Using IEEE 754 128-bit floating-point arithmetic, you can store
approximations up to 1754!  (1.979261890105010E+4930)

You probably don't have a compiler that handles sizes bigger than 64-bit
integers (though GCC has rudimentary support for 128-bit integers).

See also [Calculating factorial of large numbers in C](https://stackoverflow.com/a/60255725/15168).

There is code to calculate factorials for the `bc` command available in
my [SOQ](https://github.com/jleffler/soq) repository on GitHub as file
`factorial.bc` in the
[src/miscellany](https://github.com/jleffler/soq/tree/master/src/miscellany)
sub-directory.

EOF
