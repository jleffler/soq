#!/bin/sh
#
# URLs for key quotes for SO in Markdown

cat << 'EOF'

Kernighan & Plauger [The Elements of Programming Style, 2nd Edn](https://smile.amazon.com/dp/0070342075/) 1978.

* It's still a good book, but the technology used to exemplify their
  points is a mix of Fortran IV (with some extensions) and PL/I.

* This limits its usefulness for people who've not been exposed to these
  languages - understanding the limitations (particularly of Fortran IV)
  is probably not taught today.

<hr>

Kernighan & Plauger say, in their old but classic book "The Elements of
Programming Style", that:

* A wise old programmer once said "floating point numbers are like
  little piles of sand; every time you move one, you lose a little sand
  and gain a little dirt".

They also say:

* 10 * 0.1 is hardly ever 1.0

Both sayings point out that floating point arithmetic is not precise.

<hr>

Kernighan and Plauger summarized it neatly in their book The Elements of
Programming Style:

* The subroutine call permits us to summarize the irregularities in the
  argument list, where we can see quickly what is going on.
* The subroutine itself summarizes the regularities of the code, so
  repeated patterns need not be used.

EOF
