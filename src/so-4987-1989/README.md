### Stack Overflow Question 4987-1989

[SO 4987-1989](https://stackoverflow.com/q/49871989) &mdash;
Error: cannot convert `double*` to `char*` for argument
1 to `void swap(char*, char*, unsigned int)`

<hr>

### Question SO 4987-1989

    #include <stdio.h>

    void swap( char* pA,  char* pB, unsigned tam) {
        for( unsigned i = 0; i < tam; i++) {
            char tmp = *pA;
            *pA = *pB;
            *pB = tmp;

            pA = pA + 1;
            pB = pB + 1;
        }
    }

    int main(int argc, char** argv) {
        double a = 1.0;
        double b = 2.0;

        printf("linea: %d - antes a(%f) b(%f)\n", __LINE__, a, b);

        swap(&a, &b, sizeof(double)); //This line gives the error

        printf("linea: %d - despues a(%f) b(%f)\n", __LINE__, a, b);
    }

When I call the swap method I get the error message in the title, any
idea why?
I saw many other posts with solutions but none of them fixed this
problem.

### Answer to SO 4987-1989

There are a number of ways of writing a generic swap function.
If it will be used for only one type (so it doesn't need to be generic),
the size argument is not needed and you can pass pointers of the
relevant type (`double *` in the question) and swap using indirection.

    extern void double_swap(double *d1, double *d2);

    void double_swap(double *d1, double *d2)
    {
        double d = *d1;
        *d1 = *d2;
        *d2 = d;
    }

There might well be advantages to making that into:

    static inline void double_swap(double *d1, double *d2)
    {
        double d = *d1;
        *d1 = *d2;
        *d2 = d;
    }

This could be placed in a header and used safely.

If it will be used for multiple types, you should use `void *` in the
function arguments (and `size_t` for the size of the type).

    /*
    ** This declaration belongs in a header if there is more than one
    ** source file that uses it.  If there is only one file, then it
    ** should be declared and defined as a static function.  If the
    ** header doesn't include any other headers that define size_t,
    ** it should #include <stddef.h> as that's the smallest header
    ** that does define size_t.  You could make the function static
    ** inline instead of extern, even if it is in a header.
    */
    extern void generic_swap(void *v1, void *v2, size_t size);

    /* Implementation 1: Using VLA */
    void generic_swap(void *v1, void *v2, size_t size)
    {
        char sp[size];
        memmove(sp, v1, size);
        memmove(v1, v2, size);
        memmove(v2, sp, size);
    }

You can use `memcpy()` if you don't mind living dangerously (you should
probably add `restrict` to the `v1` and `v2` pointer types if you do
that).
Again, the function could probably be made `static inline` to good
effect — that also applies to the other implementations below.

If you don't like the idea of large objects being allocated on the
stack, you can copy the data in chunks, but you have to work quite a bit
harder.

    enum { CHUNK_SIZE = 64 };

    static inline size_t min_size(size_t x, size_t y) { return (x < y) ? x : y; }

    /* Implementation 2: Using a fixed size buffer */
    void generic_swap(void *v1, void *v2, size_t size)
    {
        unsigned char sp[CHUNK_SIZE];
        unsigned char *p1 = v1;
        unsigned char *p2 = v2;
        size_t chunk;
        while ((chunk = min_size(size, CHUNK_SIZE)) != 0)
        {
            memmove(sp, p1, chunk);
            memmove(p1, p2, chunk);
            memmove(p2, sp, chunk);
            p1 += chunk;
            p2 += chunk;
            size -= chunk;
        }
    }

Notwithstanding anything that GCC permits, the C standard says you can't
increment a `void *` because there is no known size to increment it by.
That's why the pointers are converted to `unsigned char *`.
Clearly, you can tune the chunk size to suit your system.
Any power of 2 in the range 16..1024 is probably usable, and other
values than a power of 2 can be used if you prefer.

If you don't mind the overhead, you can dynamically allocate a buffer:

    /* Implentation 3: Using dynamic memory allocation */
    void generic_swap(void *v1, void *v2, size_t size)
    {
        char *sp = malloc(size);
        if (sp != 0)
        {
            memmove(sp, v1, size);
            memmove(v1, v2, size);
            memmove(v2, sp, size);
            free(sp);
        }
    }

If memory allocation fails, the swap doesn't occur.
That's bad, so you might fall back on the 'fixed size buffer and swap in
chunks', but that is probably quicker than this anyway.

I would use Implementation 2 in preference to Implementation 3; dynamic
memory allocation is expensive.
I would probably use Implementation 2 in preference to Implementation 1
as the extra cost of the looping is minimal and using a fixed amount of
stack works well.
I have not benchmarked any of these to verify my assertions.
(If you're swapping megabyte sized lumps of data, you should probably
think again — use pointers instead.
If you're only swapping smaller chunks, Implementation 1 is simple and
safe.)

With any of the generic swap implementations, your main program becomes:

    int main(void)
    {
        double a = 1.0;
        double b = 2.0;
    
        printf("linea: %d - antes   a(%f) b(%f)\n", __LINE__, a, b);
        generic_swap(&a, &b, sizeof(double));
        printf("linea: %d - despues a(%f) b(%f)\n", __LINE__, a, b);
        return 0;
    }

I'm assuming that at least the declaration of `generic_swap()` is
available before the start of `main()`.

Note that using either `double_swap()` or `generic_swap()` means that no
casts are necessary in the code.
Minimizing casts is A Good Idea™.

See also [Universal array element swap in C](https://stackoverflow.com/questions/50559106/).

<hr>

### Question SO 5055-9106

I've realized now that in many of my codes, I will have 2 or 3 functions
like this:

    void swap(int* a, int* b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }

Each with their own pointer type.
What I'm wondering is, if there is a way to swap two elements of an
array, for example, regardless of the array type?

### Answer to SO 5055-9106

Yes, but you have to tell the `swap` code how big the elements are:

    void generic_swap(void *v1, void *v2, size_t size)
    {
        char temp[size];
        memmove(temp, v1, size);
        memmove(v1, v2, size);
        memmove(v2, temp, size);
    }

This uses a VLA (variable length array — a feature of C99 and an
optional feature of C11) for the temporary space.
The size of the local array, `temp`, is controlled at runtime by the
function parameter `size`.
If you don't trust your users not to request swapping multiple megabytes
of data, you can use dynamic memory allocation instead, or only use
dynamic memory allocation if the size is bigger than, say, 1 kilobyte.

Either:

    void generic_swap(void *v1, void *v2, size_t size)
    {
        size_t chunk = (size > 1024) ? 1024 : size;
        size_t offset = 0;
        char *s1 = v1;
        char *s2 = v2;
        char  temp[chunk];
        while (size > 0)
        {
            size_t length = (size > chunk) ? chunk : size;
            memmove(temp, s1 + offset, length);
            memmove(s1 + offset, s2 + offset, length);
            memmove(s2 + offset, temp, length);
            size -= length;
            offset += length;
        }
    }

Or:

    void generic_swap(void *v1, void *v2, size_t size)
    {
        void *v3 = malloc(size);
        if (v3 != 0)
        {
            memmove(v3, v1, size);
            memmove(v1, v2, size);
            memmove(v2, v3, size);
            free(v3);
        }
    }

The loop version avoids the overhead of dynamic memory allocation, and
won't be much slower than copying it all in three operations.
There are various ways that could be used to tune the looping code —
see also the
[comments](https://stackoverflow.com/questions/50559106/universal-array-element-swap-in-c/50559141#comment88129382_50559141)
by [rici](https://stackoverflow.com/users/1566221/rici) about other ways
in which you can optimize that if you find that the swapping code is a
bottleneck.
You're at liberty to choose a smaller size than 1024 bytes; 64 or 128
might be feasible too, and you don't necessarily need a VLA in the
function.

To swap two integers:

    int i = 37;
    int j = 99;

    swap_generic(&i, &j, sizeof(i));

To swap two arrays of `char`:

    char data[80] = "A tabloid writer's nightmare on steroids";
    char info[80] = "Obsequiousness will get you nowhere fast";

    swap_generic(data, info, sizeof(data));

Etc.
Note that the arrays need to be the same size — or, more accurately,
the size you specify needs to be the size of the smaller of the arrays
to be safe.

You can use `memcpy()` instead of `memmove()` if you are happy to live
dangerously — though the danger is limited in this context.
(If you swap an object with itself, you invoke undefined behaviour.
Otherwise, it is safe.)
Using `memmove()` always works; using `memcpy()` usually works.
I prefer 'always' to 'mostly'.

<hr>

### Test harness for the three algorithms

Compile with, for example:

    gcc -O3 -g -std=c11 -Wall -Wextra -Werror -DUSE_GENSWAP_3 swap89.c -o swap89

When run with [Valgrind](http://valgrind.org), the code gets a clean bill of health.

Code — in `swap89.c`

Sample output (the result is the same from each algorithm):

    i = 37; j = 99
    i = 99; j = 37
    data = [A tabloid writer's nightmare on steroids]
    info = [Obsequiousness will get you nowhere fast]
    data = [Obsequiousness will get you nowhere fast]
    info = [A tabloid writer's nightmare on steroids]
    maxibuff1 = [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]
                [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]
    …
                [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]
    maxibuff2 = [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
                [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
    …
                [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
    maxibuff1 = [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
                [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
    …
                [zyxwvutsrqponmlkjihgfedcba`_^]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;]
    maxibuff2 = [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]
                [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]
    …
                [!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`]


### Extended information from SO 5055-9106

There are three variants on the generic swap code in `swap89.c`.
As it stands, only one is active at a time.
It would not be all that hard to create a test case that compares all
three, working on small (up to 16 bytes, say), medium (up to 1 KiB,
say), large (up to 64 KiB, say) and very large (bigger than 64 KiB).

