### Stack Overflow Question 4305-9874

[SO 4305-9874](http://stackoverflow.com/q/43059874) &mdash;
Composite Predicate of function pointers in C

This code is closely based on [Chris
Dodd](http://stackoverflow.com/users/16406/chris-dodd)'s
[answer](http://stackoverflow.com/a/43060435/) — or at least, the
initial versions of it were.

The source in pd31.c is a modestly extended version of Chris's code, but
no violence has yet been done to it.

The source in pd37.c is a simplified version of pd31.c.
One simplification is that it only uses `mk_predicate()` — the
`compose()` function in the answer was more specialized than necessary.
Another simplification at the moment is the removal of an extra level of
indirection - the closure structure stores pointers to functions, not
pointers to pointers to functions.

I've sought input from Chris with a view to finding why the extra level
of indirection was considered ncessary, but I've not received any
feedback yet (which is not at all surprising).
