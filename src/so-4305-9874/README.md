### Stack Overflow Question 4305-9874

[SO 4305-9874](http://stackoverflow.com/q/43059874) &mdash;
Composite Predicate of function pointers in C

This code is closely based on [Chris
Dodd](http://stackoverflow.com/users/16406/chris-dodd)'s
[answer](http://stackoverflow.com/a/43060435/) — or at least, the
initial versions of it were.

The source in pd31.c is a modestly extended version of Chris's code, but
no violence has yet been done to it.
I devised a function `mk_predicate()` which is analogous to the original
`compse()` shown by Chris Dodd.
Instead of being fixed on the `A&&B` operator, it can take any operator.
I created `A||B` and also !A&&B.

The source in pd37.c is a simplified version of pd31.c.
One simplification is that it only uses `mk_predicate()` — the
`compose()` function in the answer was more specialized than necessary.
Another simplification at the moment is the removal of an extra level of
indirection - the closure structure stores pointers to functions, not
pointers to pointers to functions.

I sought input from Chris Dodd to find why the extra level of
indirection is ncessary.
It comes down to what happens when you build a predicate from a
'manufactured' predicate using one or more of the predicates created by
`mk_predicate()`.

The file pd41.c is an adaptation of pd31.c that has a new predicate
function `isPrimeUnder20_p()` which returns true if the absolute value
of the numeric argument is a prime number less than 20.
A straight-forward operation to create the code worked admirably.

The file pd47.c is likewise an adaptation of pd37.c with the same new
predicate support function and parallel support code.
It crashes horribly.

More research is needed to understand what is going on.

