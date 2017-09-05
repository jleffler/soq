# Flexible Array Members

<!-- if version [gte C99] -->

## Type Declaration

A structure with at least one member may also contain a single array
member of unspecified length at the end of the structure.
This is called a _flexible array member_:

    struct ex1 
    {
        size_t foo;
        int flex[];
    };

    struct ex2_header 
    {
        int foo;
        char bar;
    };

    struct ex2 
    {
        struct ex2_header hdr;
        int flex[];
    };

    /* Merged ex2_header and ex2 structures. */
    struct ex3 
    {
        int foo;
        char bar;
        int flex[];
    };

The standard says:

> A structure with a flexible array member (and any union containing,
> possibly recursively, a member that is such a structure) shall not be
> a member of a structure or an element of an array, but pointers to
> such structures are legitimate.

Note that it is likely that the main part of the structure with a
flexible array member will have one member that identifies the length of
the array.
At the least, the code must have some way of knowing the size of the
array, whether that's an explicit counter or a null pointer marking the
end of the array, or some other technique.

## Usage

For most practical purposes, you will dynamically allocate structures
with flexible array members.



Although you can declare and initialize an object with a structure type
containing a flexible array member, you cannot allocate memory for the
flexible array member using standard C.
Any attempt to do so should elicit diagnostic messages (not necessarily
error messages) from a standard-conforming compiler.

However, some compilers (such as GCC and Clang) support such
initialization as an extension.
However, they only allow it for variables defined at file scope or with
`static` storage duration.
You can't use it to initialize automatic variables.
Further, they won't warn you that you are using a non-standard construct
unless you use the `-pedantic` option to make them generate a warning
about it.


Similarly, you should not attempt to assign a value to any element of a
flexible array member when declaring a structure in this way since there
will not be enough padding at the end of the structure to allow for any
objects required by the flexible array member.
The compiler will not necessarily prevent you from doing this, however,
so this can lead to undefined behavior.

    /* invalid: cannot initialize flexible array member */
    struct ex1 e1 = {1, {2, 3}};
    /* invalid: hdr={foo=1, bar=2} OK, but cannot initialize flexible array member */
    struct ex2 e2 = {{1, 2}, {3}};
    /* valid: initialize foo=1, bar=2 members */
    struct ex3 e3 = {1, 2};

    e1.flex[0] = 3; /* undefined behavior, in my case */
    e3.flex[0] = 2; /* undefined behavior again */
    e2.flex[0] = e3.flex[0]; /* undefined behavior */

You may instead choose to use `malloc`, `calloc`, or `realloc` to
allocate the structure with extra storage and later free it, which
allows you to use the flexible array member as you wish:

    /* valid: allocate an object of structure type `ex1` along with an array of 2 ints */
    struct ex1 *pe1 = malloc(sizeof(*pe1) + 2 * sizeof(pe1->flex[0]));

    /* valid: allocate an object of structure type ex2 along with an array of 4 ints */
    struct ex2 *pe2 = malloc(sizeof(struct ex2) + sizeof(int[4]));

    /* valid: allocate 5 structure type ex3 objects along with an array of 3 ints per object */
    struct ex3 *pe3 = malloc(5 * (sizeof(*pe3) + sizeof(int[3])));

    pe1->flex[0] = 3; /* valid */
    pe3[0]->flex[0] = pe1->flex[0]; /* valid */

## Effects on Size and Padding

A flexible array member is treated as having no size when calculating
the size of a structure, though padding between that member and the
previous member of the structure may still exist:

    /* Prints "8,8" on my machine, so there is no padding. */
    printf("%zu,%zu\n", sizeof(size_t), sizeof(struct ex1));

    /* Also prints "8,8" on my machine, so there is no padding in the ex2 structure itself. */
    printf("%zu,%zu\n", sizeof(struct ex2_header), sizeof(struct ex2));

    /* Prints "5,8" on my machine, so there are 3 bytes of padding. */
    printf("%zu,%zu\n", sizeof(int) + sizeof(char), sizeof(struct ex3));

The flexible array member is considered to have an incomplete array
type, so its size cannot be calculated using `sizeof`.

<!-- end version if -->

<!-- if version [gte C11] -->

Note that §6.10.8.3 Conditional feature macros allows a compiler ('the implementation') to define:

*  `__STDC_NO_VLA__` — The integer constant `1`, intended to indicate that the
    implementation does not support variable length arrays or variably
    modified types.

C99 requires support for variable length arrays unconditionally.
C90 has no support for variable length arrays.

<!-- end version if -->

<!-- if version [lt C99] -->

### The 'struct hack'

Flexible array members did not exist prior to C99 and are treated as
errors.
A common workaround is to declare an array of length 1, a technique
called the 'struct hack':

    struct ex1 
    {
        size_t foo;
        int flex[1];
    };

This will affect the size of the structure, however, unlike a true
flexible array member:

    /* Prints "8,4,16" on my machine, signifying that there are 4 bytes of padding. */
    printf("%d,%d,%d\n", (int)sizeof(size_t), (int)sizeof(int[1]), (int)sizeof(struct ex1));

To use the `flex` member as a flexible array member, you'd allocate it
with `malloc` as shown above, except that `sizeof(*pe1)` (or the
equivalent `sizeof(struct ex1)`) would be replaced with `offsetof(struct
ex1, flex)` or the longer, type-agnostic expression
`sizeof(*pe1)-sizeof(pe1->flex)`.
Alternatively, you might subtract 1 from the desired length of the
"flexible" array since it's already included in the structure size,
assuming the desired length is greater than 0.
Or, alternatively again, you might decide that there isn't enough wasted
space to matter if the code allocates one or two elements too many for
the array.
The same logic may be applied to the other usage examples.

<!-- end version if -->

## Compatibility

If compatibility with compilers that do not support flexible array
members is desired, you may use a macro defined like `FLEXMEMB_SIZE`
below:

    #if __STDC_VERSION__ < 199901L
    #define FLEXMEMB_SIZE 1
    #else
    #define FLEXMEMB_SIZE /* nothing */
    #endif

    struct ex1 
    {
        size_t foo;
        int flex[FLEXMEMB_SIZE];
    };

When allocating objects, you should use the `offsetof(struct ex1, flex)`
form to refer to the structure size (excluding the flexible array
member) since it is the only expression that will remain consistent
between compilers that support flexible array members and compilers that
do not:

    struct ex1 *pe10 = malloc(offsetof(struct ex1, flex) + n * sizeof(pe10->flex[0]));

The alternative is to use the preprocessor to conditionally subtract 1
from the specified length.  Due to the increased potential for
inconsistency and general human error in this form, I moved the logic
into a separate function:

    struct ex1 *ex1_alloc(size_t n)
    {
        struct ex1 tmp;
    #if __STDC_VERSION__ < 199901L
        if (n != 0)
            n--;
    #endif
        return malloc(sizeof(tmp) + n * sizeof(tmp.flex[0]));
    }

    ...

    /* allocate an ex1 object with "flex" array of length 3 */
    struct ex1 *pe1 = ex1_alloc(3);
