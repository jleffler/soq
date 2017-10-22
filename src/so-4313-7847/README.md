### Stack Overflow Question 4313-7847

[SO 4313-7847](https://stackoverflow.com/q/43137847) &mdash;
Multiplication of polynomial in C using list

The code here is a complete rewrite of the code in the question, as
noted in the spiel submitted with the program.

Polynomial division was added as an afterthought.

Wikipedia helps: [Polynomial long
division](https://en.wikipedia.org/wiki/Polynomial_long_division).
It gives the pseudo-code algorithm:

    function n / d:
      require d ≠ 0
      q ← 0
      r ← n       # At each step n = d × q + r
      while r ≠ 0 AND degree(r) ≥ degree(d):
        t ← lead(r)/lead(d)     # Divide the leading terms
        q ← q + t
        r ← r − t * d
      return (q, r)

Returning a pair of values in C requires a structure.  So, the type
`poly_pair` (name subject to revision) is defined.

The code is now split into header polynomial.h where the polynomial type
is opaque, source file polynomial.c for the implementation of polynomial
arithmetic, and source file pm43.c for the test code.
The polynomial type was upgraded to use rational numbers — using an
improved version of the code from SO 3388-7484 (rational.c, rational.h,
actually from $HOME/lib/JL and not yet from soq/src/libsoq).
This can probably be fixed at some time.
Function `ri_neg()` was added, and `ri_chk()` exposed — though this
might be a temporary phenomenon.
Function `ri_fmt()` and `ri_fmtproper()` have been upgraded to take an
extra argument that specifies the string to print in front of positive
fractions.
This might sanely be "" (empty string, used by polynomial printing), " "
(blank) or "+" (used by `test.rational.c` code.

The division code has been completed — it is proven to work OK on two
examples from the Wikipedia page (though there is room to question why
the second example divides by (x-1)^2; it is probably coincidentally
correct when analyzing a cubic polynomial, but it is not going to give a
straight line in general for a seventh-order polynomial.
That needs to be questioned on the Wikipedia chat pages.)
Some of the homebrew examples have been hand-validated, but not all.

At some stage the test code should be converted to the Phased Test
Harness, but that also needs to be available at GitHub.  Because it uses
multiple sub-packages, it is complex to move satisfactorily.

