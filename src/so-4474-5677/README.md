### Stack Overflow Question 4474-5677

[SO 4474-5677](https://stackoverflow.com/q/44745677) &mdash;
Flexible array members can lead to undefined behavior?

My answer was moderately well received, but was semi-accidentally
received a 250-point bounty bonus (automatically awarded from a
500-point bounty offered but my answer was not, unsurprisingly, accepted
and awarded the full bounty).

### Point at issue

The key point of debate is the meaning of:

> ### ISO/IEC 9899:2011 

> ### §6.2.6 Representation of types
> ### §6.2.6.1 General

> ¶6 When a value is stored in an object of structure or union type,
> including in a member object, the bytes of the object representation
> that correspond to any padding bytes take unspecified
> values.<sup>51)</sup> The value of a structure or union object is
> never a trap representation, even though the value of a member of the
> structure or union object may be a trap representation.

> <sup>51)</sup> Thus, for example, structure assignment need not copy
> any padding bits.

Consider the structures:

    struct A
    {
        char a_c1;
        int  a_i1;
        char a_c2;
    };

    struct B
    {
        char b_c1;
        struct A b_a1;
        char b_c2;
    };

and the code:

    struct A a1 = { … };
    struct A a2 = { … };
    struct B b1 = { … };

    a2 = a1;
    b1.b_a1 = a1;

Does §6.2.6.1 ¶6 give permission for the padding after `b1.b_c1` and
`b1.b_c2` to take 'unspecified values' after the assignment `b1.b_a1 =
a1;`?

We need to agree that the type `struct A` could have 3 bytes padding
after `a_c1` and before `a_i1`, and could have another 3 bytes padding
after `a_c2`.
Similarly, `struct B` could have 3 bytes padding after `b_c1` and
another 3 bytes padding after `b_c2`.
Yes, there could be other amounts of padding, but on many systems,
that's what would be present.
The discussion below assumes this.

It depends on the parsing of:

_When a value is stored in an object of structure or union type,
including in a member object, the bytes of the object representation
that correspond to any padding bytes take unspecified values._

It is clear that after the assignment `a2 = a1` the padding bytes in
`a2` have unspecified values.
The footnote says that the padding bits need not be copied (from `a1` to
`a2`), but equally they could be copied, and presumably it would not be
a violation of the standard if the padding bits in `a2` were generated
as random bytes, or the xor of the bytes from the pre-assignment values
in the structure — not that a sane compiler would do anything that
complex.
That's the simple, non-controversial case.

At issue is whether, when the assignment is of the form `b1.b_a1 = a1;`
the 'bytes of the object representation that correspond to any padding
bytes' means the padding bytes of the `struct A` object contained within
`struct B` are unspecified — but the padding bytes within `struct B`
are not changed because it is the `struct A` member object that is
assigned to (which is my position), or whether it means the padding
bytes of the `struct B` object can also take unspecified values (which
is the contrary position).

If the 'contrary position' is what's intended, my argument is wrong.
If my position is accurate, then there is no problem, as my main answer
states.
There is no formal resolution of this as yet (2017-07-26).

