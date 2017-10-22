### [SO 3388-7484](https://stackoverflow.com/q/33887484) &mdash; Fraction Arithmetic

This code is known not to compile in the GitHub environment because the
Phased Test library is not yet available.
In principle, I'm working on creating a sub-module or two for that
(probably several).

<hr>

This question is one that is not a very good fit for SO.
It's a homework assignment.

* The homework specification describes one interface — three-argument
functions taking two inputs and one output structure, all as pointers.
* The sample code flies against that specification, taking two structures
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
fractions (`[1/5]`) and proper fractions (`[-1 3/4]`).

<hr>

### `rational.c`

The file presented here is a combination of three separate files in my
private library: `rational.h`, `rational.c` and `test.rational.c`.
The test code uses the Phased Test Harness, which is the main reason it
is not posted to SO as an answer.

The Phased Test Harness is not under Git yet - I have still to decide
how to manage sub-modules or the equivalent.
The Phased Test Harness itself uses the full Stderr library, and sundry
other groups of functions from the JLSS library too (MD Debug, Minimal
BitMap, etc).
Although it links with JLSS Getopt and GetSubOpt, they're used
essentially as simple plug-in surrogates for the system-provided
functions of the same names (no special functionality used).

### `so.33887484.c`

This code contains a variant of the rational arithmetic functions using
the interface demanded by the question — three-argument functions
returning `void` rather than two-argument functions returning the
result.

The input scanning code in `ri_scn()` expects fractions to be enclosed in square
brackets, such as `[165/7]` or `[23 4/7]` or `[23]`.
It also accepts pure decimals without square brackets (such as `3` or
`3.14159`).
There are two output functions:

* `ri_fmt()` to print a straight ratio of two numbers, such as
  `[+165/7]` (unless the denominator is 1, in which case it prints a
  simple integer `[+23]`)
* `ri_fmtproper()` to print a proper number such as `[+23 4/7]`

Note that the output always includes a sign; the sign is optional on input.

### `so.33887484.h`

The header for the code in `so.33887484.c`.

### `ratcalc.c`

A simple rational number calculator.  
It works on expressions on a single line at a time.
It doesn't print anything if there's a single number on the line (bug? feature?).
It only prints improper fractions (using `ri_fmt()` and not `ri_fmtproper()`).
It evaluates terms stricly left to right and does not support parentheses.

**Example output**

    165/7
    lhs = [+165]
    rhs = [+7]
    res = [+165/7] (op = '/')

    [165/7] + [0]
    lhs = [+165/7]
    rhs = [+0]
    res = [+165/7] (op = '+')

    [23 4/7] + 0
    lhs = [+165/7]
    rhs = [+0]
    res = [+165/7] (op = '+')

    165 / 7 + 23 / 4
    lhs = [+165]
    rhs = [+7]
    res = [+165/7] (op = '/')

    lhs = [+165/7]
    rhs = [+23]
    res = [+326/7] (op = '+')

    lhs = [+326/7]
    rhs = [+4]
    res = [+163/14] (op = '/')

    [165/7] + [23/4]
    lhs = [+165/7]
    rhs = [+23/4]
    res = [+821/28] (op = '+')

There is no doubt that the calculator could be made more sophisticated,
but the level of sophistication wasn't really mandated in the question.

The square bracket notation makes the fraction handling unambiguous, but
also a bit clumsy.
The code in `rational.c` manages to handle the more general
loosey-goosey formatting that humans expect.

A pair of missing functions is `ri_todouble()` to convert a fraction to
a `double`, and `ri_cvdouble()` to convert a `double` to a fraction.
The first is simple; any fraction can be approximated by a `double`.
The second is not straight-forward.
There are values that can be stored in a `double` that cannot be
represented as a fraction, so there are two failure modes:

* too large — there isn't a formal signed infinity notation
* too small — truncate to zero?

