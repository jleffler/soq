### Stack Overflow Question 0618-7908

[SO 0618-7908](https://stackoverflow.com/q/06187908) &mdash;
Is it possible to dynamically define a struct in C

### Answer

It isn't possible to dynamically define a struct that is identical to a
compile-time struct.

It is possible, but difficult, to create dynamic structures that can
contain the information equivalent to a struct.
The access to the data is less convenient than what is available at
compile-time.

All else apart, you cannot access a member
`somestruct.not_seen_at_compile_time` using the `.` or `->` notation if
it was not defined at compile-time.

With network communications, there are other issues to address - notably
'endianness'.
That is, the data on the wire will probably include multi-byte (2, 4, 8)
integers, and either the MSB or the LSB will be sent first, but if one
machine is little-endian (IA-32, IA-64, x86/64) and the other is
big-endian (SPARC, PPC, almost anything not from Intel), then the data
will need to be transformed.
Floating point formats can also be problematic.
There are numerous standards dedicated to defining how data will be sent
across the network - it is not trivial.
Some are specific: IP, TCP, UDP; others are general, such as ASN.1.

However, the 'cannot do dynamic data structures' part limits things -
you have to agree beforehand on what the data structures are, and how
they will be interpreted.
How do you do that?

[gerty3000](https://stackoverflow.com/users/823872/dan) asks:

> _It is possible, but difficult, to create dynamic structures that can
> contain the information equivalent to a struct.
> — How do you do that?
> I would like to pass dynamically-defined structs off to other C code
> (assume same compiler and other settings) without having to duplicate
> the struct memory layout routines from the compiler.
> I won't be accessing fields of these structs inside my process much
> (just initializing them once), so convenient syntax is not a concern._

You can't do it without duplicating the memory layout in some shape or
form.
It might not have to be exactly the same, but it is likely best if it
is.
Here's some sample code that shows roughly how it might be done.

### `dynstruct.c`

This contains the basic structure manipulation material — structures
to describe structures and (simple) members.
Handling full arrays (as opposed to strings) would require more work,
and there's a good deal of make-work replication to be managed for other
types.

It also contains a `main()` program that tests the code.
It makes a call to `other_function()`, which demonstrates that the
structure I've defined in the data structures does match the structure
exactly.
The data does assume a 64-bit machine where `double` must be aligned on an
8-byte boundary (so there's a 4-byte hole in the structure); you will
have to tweak the data for a machine where `double` can be on a 4-byte
boundary.

* See `dynstruct.c`

### `other.c`

This code knows nothing about the structure description material in
dynstruct.c; it knows about the struct simulated that the simulation
code simulates.
It prints the data it is passed and modifies it.

* See `other.c`

Sample output

    Main (before):
    Integer: 37
    Double:  3.141590
    String:  Absolute nonsense
    Other function:
    Integer: 37
    Double:  3.141590
    String:  Absolute nonsense
    Main (after):
    Integer: 74
    Double:  1.570795
    String:  Codswallop

Clearly, this code is not production ready.
It is a sufficient demonstration of what can be done.
One issue you'd have to deal with is initializing the Structure and
Descriptor data correctly.
You can't put too many assertions into that sort of code.
For example, I should really have `assert(d->size == sizeof(double);` in
`get_double_element()`.
It would also be sensible to include `assert(d->offset % sizeof(double)
== 0);` to ensure that the double element is properly aligned.
Or you might have a `validate_structure(const Structure *sp);` function
that did all these validation checks.
You'd need a function `void dump_structure(FILE *fp, const char *tag,
const Structure *sp);` to dump the defined structure to the given file
preceded by the tag, to assist in debugging.
Etc.

This code is pure C; it is not compilable by a C++ compiler as C++.
There aren't enough casts to satisfy a C++ compiler.

