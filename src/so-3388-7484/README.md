### [SO 3388-7484](http://stackoverflow.com/q/33887484) &mdash; Fraction Arithmetic

This code is known not to compile in the GitHub environment because the
Phased Test library is not yet available.
In principle, I'm working on creating a sub-module or two for that
(probably several).

<hr>

This question is one that is not a very good fit for SO.
It's a homework assignment.
The homework specification describes one interface — three-argument
functions taking two inputs and one output structure, all as pointers.
The sample code flies against that specification, taking two structures
as value parameters and returning one.
Which set of rules should be followed?

The code written here as so.33887484.[ch] corresponds to the stated
specification rather than the sample code.

The code written here as rational.c — which embeds the code that
should be in the header rational.h — follows the sample code rather
than the stated specification.
It does not expose the GCD function.

The arithmetic and printing code is straight-forward.
As so often, the input scanning code is far, far trickier.

The input code implemented accepts fixed point decimals (9.999), plain
fractions (1/5) and proper fractions (1 3/4).

