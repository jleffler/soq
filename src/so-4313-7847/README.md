### Stack Overflow Question 4313-7847

[SO 4313-7847](http://stackoverflow.com/q/43137847) &mdash;
Multiplication of polynomial in C using list

The code here is a complete rewrite of the code in the question, as
noted in the spiel submitted with the program.

Polynomial division was as an afterthought.

Wikipedia helps: [Polynomial long division](https://en.wikipedia.org/wiki/Polynomial_long_division).  
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

Returning a pair of values in C requires a structure.
