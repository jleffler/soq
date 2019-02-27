### Stack Overflow Question 5028-5210

[SO 5028-5210](https://stackoverflow.com/q/50285210) &mdash;
Generating random values without time.h

[Answer]() by  []() contains an interesting PRNG and some possibly useful links.

The question is a little odd, asking how to generate random seeds for
`srand()` using only the facilities from `<stdio.h>`, `<stdlib.h>` and
`<string.h>`.

<hr>

> getpid hasn't been declared.

No, because you haven't included the `<unistd.h>` header where it is
declared (and according to your
[comment](https://stackoverflow.com/questions/50285210/generating-random-values-without-time-h#comment87586416_50285273),
you cannot use it, because you're restricted to using `<stdlib.h>`,
`<string.h>`, and `<stdio.h>`).

In that case, I would use something like

    #include <stdlib.h>
    #include <stdio.h>

    static int randomize_helper(FILE *in)
    {
        unsigned int  seed;

        if (!in)
            return -1;

        if (fread(&seed, sizeof seed, 1, in) == 1) {
            fclose(in);
            srand(seed);
            return 0;
        }

        fclose(in);
        return -1;
    }

    static int randomize(void)
    {
        if (!randomize_helper(fopen("/dev/urandom", "r")))
            return 0;
        if (!randomize_helper(fopen("/dev/arandom", "r")))
            return 0;
        if (!randomize_helper(fopen("/dev/random", "r")))
            return 0;

        /* Other randomness sources (binary format)? */

        /* No randomness sources found. */
        return -1;
    }

and a simple `main()` to output some pseudorandom numbers:

    int main(void)
    {
        int i;

        if (randomize())
            fprintf(stderr, "Warning: Could not find any sources for randomness.\n");

        for (i = 0; i < 10; i++)
            printf("%d\n", rand());

        return EXIT_SUCCESS;
    }

The `/dev/urandom` and `/dev/random` character devices are available in
Linux, FreeBSD, macOS, iOS, Solaris, NetBSD, Tru64 Unix 5.1B, AIX 5.2,
HP-UX 11i v2, and `/dev/random` and `/dev/arandom` on OpenBSD 5.1 and
later.

As usual, it looks like Windows does not provide any such randomness
sources: Windows C programs must use proprietary Microsoft interfaces
instead.

The `randomize_helper()` returns nonzero if the input stream is NULL, or
if it cannot read an `unsigned int` from it.
If it can read an unsigned int from it, it is used to seed the standard
pseudorandom number generator you can access using `rand()` (which
returns an `int` between 0 and `RAND_MAX`, inclusive).
In all cases, `randomize_helper()` closes non-NULL streams.

You can add other binary randomness sources to `randomize()` trivially.

If `randomize()` returns 0, `rand()` should return pseudorandom numbers.
Otherwise, `rand()` will return the same default sequence of
pseudorandom numbers.
(They will still be "random", but the same sequence will occur every
time you run the program.
If `randomize()` returns 0, the sequence will be different every time
you run the program.)

-----

Most standard C `rand()` implementations are linear congruental
pseudorandom number generators, often with poor choices of parameters,
and as a result, are slowish, and not very "random".

For non-cryptographic work, I like to implement one of the
[Xorshift](https://en.wikipedia.org/wiki/Xorshift) family of functions,
originally by George Marsaglia.
They are very, very fast, and reasonably random; they pass most of the
statistical randomness tests like the [diehard
tests](https://en.wikipedia.org/wiki/Diehard_tests).

In OP's case, the
[xorwow](https://en.wikipedia.org/wiki/Xorshift#xorwow) generator could
be used.
According to current C standards, `unsigned int` is at least 32 bits, so
we can use that as the generator type.
Let's see what implementing one to replace the standard srand()/rand()
would look like:

    #include <stdlib.h>
    #include <stdio.h>

    /* The Xorwow PRNG state. This must not be initialized to all zeros. */
    static unsigned int  prng_state[5] = { 1, 2, 3, 4, 5 };

    /* The Xorwow is a 32-bit linear-feedback shift generator. */
    #define  PRNG_MAX  4294967295u

    unsigned int  prng(void)
    {
        unsigned int  s, t;

        t = prng_state[3] & PRNG_MAX;
        t ^= t >> 2;
        t ^= t << 1;
        prng_state[3] = prng_state[2];
        prng_state[2] = prng_state[1];
        prng_state[1] = prng_state[0];
        s = prng_state[0] & PRNG_MAX;
        t ^= s;
        t ^= (s << 4) & PRNG_MAX;
        prng_state[0] = t;
        prng_state[4] = (prng_state[4] + 362437) & PRNG_MAX;
        return (t + prng_state[4]) & PRNG_MAX;
    }

    static int prng_randomize_from(FILE *in)
    {
        size_t        have = 0, n;
        unsigned int  seed[5] = { 0, 0, 0, 0, 0 };

        if (!in)
            return -1;

        while (have < 5) {
            n = fread(seed + have, sizeof seed[0], 5 - have, in);
            if (n > 0 && ((seed[0] | seed[1] | seed[2] | seed[3] | seed[4]) & PRNG_MAX) != 0) {
                have += n;
            } else {
                fclose(in);
                return -1;
            }
        }

        fclose(in);
        prng_seed[0] = seed[0] & PRNG_MAX;
        prng_seed[1] = seed[1] & PRNG_MAX;
        prng_seed[2] = seed[2] & PRNG_MAX;
        prng_seed[3] = seed[3] & PRNG_MAX;
        prng_seed[4] = seed[4] & PRNG_MAX;

        /* Note: We might wish to "churn" the pseudorandom
                 number generator state, to call prng()
                 a few hundred or thousand times. For example:
           for (n = 0; n < 1000; n++) prng();
                 This way, even if the seed has clear structure,
                 for example only some low bits set, we start
                 with a PRNG state with set and clear bits well
                 distributed.
        */

        return 0;
    }

    int prng_randomize(void)
    {
        if (!prng_randomize_from(fopen("/dev/urandom", "r")))
            return 0;
        if (!prng_randomize_from(fopen("/dev/arandom", "r")))
            return 0;
        if (!prng_randomize_from(fopen("/dev/random", "r")))
            return 0;
        /* Other sources? */
        /* No randomness sources found. */
        return -1;
    }

The corresponding `main()` to above would be

    int main(void)
    {
        int  i;

        if (prng_randomize())
            fprintf(stderr, "Warning: No randomness sources found!\n");

        for (i = 0; i < 10; i++)
            printf("%u\n", prng());

        return EXIT_SUCCESS;
    }

Note that `PRNG_MAX` has a dual purpose.
On one hand, it tells the maximum value `prng()` can return — which is
an *unsigned* int, not int like `rand()`.
On the other hand, because it must be 2<sup>32</sup>-1 = 4294967295, we
also use it to ensure the temporary results when generating the next
pseudorandom number in the sequence remain 32-bit.
If the `uint32_t` type, declared in `stdint.h` or `inttypes.h` were
available, we could use that and drop the masks (`& PRNG_MAX`).

Note that the `prng_randomize_from()` function is written so that it
still works, even if the randomness source cannot provide all requested
bytes at once, and returns a *"short count"*.
Whether this occurs in practice is up to debate, but I prefer to be
certain.
Also note that it does not accept the state if it is all zeros, as that
is the one single prohibited initial seed state for the Xorwow PRNG.

You can obviously use both `srand()`/`rand()` and
`prng()`/`prng_randomize()` in the same program.
I wrote them so that the Xorwow generator functions all start with prng.

Usually, I do put the PRNG implementation into a header file, so that I
can easily test it (to verify it works) by writing a tiny test program;
but also so that I can switch the PRNG implementation simply by
switching to another header file.
(In some cases, I put the PRNG state into a structure, and have the
caller provide a pointer to the state, so that any number of PRNGs can
be used concurrently, independently of each other.)
