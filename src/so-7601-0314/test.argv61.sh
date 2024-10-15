#!/bin/sh
#
# Test argv61 with different input lines

# Beware trailing blanks!

{
echo ""
echo "a"
echo "a "
echo " a"
echo " a "
echo "ab"
echo "a b"
echo "a b c"
echo "   a  b  c  "
echo "abc def  ghi   jkl    "
echo "    "
printf 'a\tb\t\tc\n'
} |
./argv61
