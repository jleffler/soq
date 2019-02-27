## Stack Overflow Question 1886-3184

[SO 1886-3184](https://stackoverflow.com/q/18863184) &mdash;
How can I prevent (not react to) a segmentation fault?

This code is intriguing, and seems to work.

It is interesting that you use the `write()` system call to check
whether the data is readable and the `read()` system call to check
whether the data is writable.

Revisiting it a few years later, I wonder whether there's a good reason
not to use `/dev/null` in place of a pipe.
It would be one file descriptor, not two, and there'd be no question of
'filling up' the pipe, etc.
So, the code should be simplifiable.
And more acceptable for use in another, bigger context.

However, testing shows that when the device is `/dev/null`, there isn't
as much checking done by the kernel.
The test programs are `memprobe.c` (using a pipe) and `badprobe.c`
(using `/dev/null`).

### memprobe - using pipe

    Readability:
    matrix is readable
    NULL is BAD (14: Bad address)
    Non-existent address is BAD (14: Bad address)
    Function probe_memory_ro() is readable

    Writeability:
    matrix is writeable
    NULL is BAD (14: Bad address)
    Non-existent address is BAD (14: Bad address)
    Function probe_memory_ro() is BAD (14: Bad address)

### badprobe - using /dev/null

    Readability:
    matrix is readable
    NULL is readable
    Non-existent address is readable
    Function probe_memory_ro() is readable

    Writeability:
    matrix is writeable
    NULL is writeable
    Non-existent address is writeable
    Function probe_memory_ro() is writeable

### Conclusion

Using `/dev/null` instead of a pipe won't work everywhere.

Test performed on a Mac running macOS 10.13.4 High Sierra with GCC 8.1.0.

### Multiple threads

One issue that the code in `memprobe.c` does not address is possibility
of multiple threads in a single program using the probe functions at the
same time.

Suppose two threads test at the 'the same time', one checking a pointer
to a 4-byte object, the other checking a pointer to an 8-byte object.
Each writes some data to the pipe; each attempts to read some data from
the pipe.
Since each only tries to read as much as it wrote, would it matter if
the 4-byte thread read the first 4 bytes of what the 8-byte thread
wrote, and the 8-byte thread gets the second 4 bytes of what it wrote
and the 4 bytes that the4-byte thread wrote?

Answer: YES

The write plus read works without changing the original data in the
memory in a single-threaded environment.
In the multithreaded code, you aren't guaranteed that idempotence.
Consequently, the code would need a mutex around it to allow the
operations to remain idempotent.

### Side discussion

I recently came across some code like this:

    if (!nullind && datum != NULL)
    {
        /* test the pointer and try to prevent the compiler
         * from optimizing the test out of existence */
        char test;
        test = (volatile)*((char *)datum);
        val->v_flags = V_FIXED;
        val->v_charp = (char *)datum;
    }
    else

The `volatile` cast includes an implicit `int`.
It should be written:

        test = *((volatile char *)datum);

There are subtle questions like "is the compiler allowed to omit the
read despite the mention of `volatile`.
I think the answer is "No", though the assignment to `test` (which is
otherwise unused) is superfluous as long as the value pointed at by
`datum` is used to access a byte.

But if the test is crucial, maybe it should use the memory probe
mechanism used in the answer here.
Otherwise, the code risks — invites, even — a crash because the
pointer is invalid.

    if (!nullind && datum != NULL)
    {
        if (memprobe_rw(datum, sizeof(char)) == 0)
            …datum does not point to read/write memory — what next…
        else
        {
            val->v_flags = V_FIXED;
            val->v_charp = (char *)datum;
        }
    }
    else

In the larger context, it would probably be sensible to use this:

    if (!nullind && datum != NULL && memprobe_rw(datum, sizeof(char)))
    {
        val->v_flags = V_FIXED;
        val->v_charp = (char *)datum;
    }
    else
    {
        /* Handle null (or invalid) pointer */
    }

That transform cannot be shown to be valid without knowing the details
of the `else` clause, but is in fact a sensible rewrite.
