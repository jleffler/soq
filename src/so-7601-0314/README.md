### Stack Overflow Question 7601-0314

[SO 7601-0314](https://stackoverflow.com/q/76010314) &mdash;
Getting `malloc() mismatching next->prev_size` when trying to format a string like argv

### Answer

Ignoring issues with signal handling (because, AFAICT from the comments,
the argument parsing will not happen in a signal handler), this is what
I'd use:

```
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **argv;    /* Null-terminated vector of argument strings */
    char  *argb;    /* Data that elements of argv point to */
    size_t argc;    /* Number of arguments */
    /* av.argv[av.argc] == 0 */
} ArgVector;

static ArgVector make_argv(const char *buffer)
{
    ArgVector av =
    {
        /* At worst, there is one argument for every two characters */
        .argv = calloc(sizeof(av.argv[0]), (strlen(buffer) + 1) / 2 + 1),
        .argb = strdup(buffer),
        .argc = 0
    };

    if (av.argv == 0 || av.argb == 0)
    {
        free(av.argv);
        free(av.argb);
        av.argv = 0;
        av.argb = 0;
        return av;
    }

    char *s = av.argb;
    while (*s != '\0')
    {
        char c;
        while ((c = *s) != '\0' && isspace((unsigned char)c))
            s++;
        if (c != '\0')
        {
            av.argv[av.argc++] = s;
            while ((c = *s) != '\0' && !isspace((unsigned char)c))
                s++;
            if (c != '\0')
                *s++ = '\0';
        }
    }

    return av;
}

static void free_argv(ArgVector *av)
{
    if (av != 0)
    {
        free(av->argv);
        free(av->argb);
        av->argv = 0;
        av->argb = 0;
    }
}

int main(void)
{
    char   *buffer = 0;
    size_t  buflen = 0;
    ssize_t length;

    while ((length = getline(&buffer, &buflen, stdin)) > 0)
    {
        buffer[--length] = '\0';
        ArgVector av = make_argv(buffer);
        printf("line [%s]\n", buffer);
        printf("argc %zu\n", av.argc);
        for (size_t i = 0; i < av.argc; i++)
             printf("%zu = [%s]\n", i, av.argv[i]);
        free_argv(&av);
    }
    free(buffer);
    return 0;
}
```
The `ArgVector` structure encapsulates the key information — the
vector of pointers to strings (`argv`), the base (start) of the copy of
the input string (`argb`), and the number of arguments (`argc`).  The
elements of `argv` point into the string recorded by `argb`.

The function `free_argv()` releases allocated memory and makes the
structure safe for reuse.  The function `make_argv()` makes a
conservative estimate of how many space-separated arguments there could
be.  If the input string is a single letter, there is one argument and
the length calculation for `calloc()` gives the value `2` (allowing for
the null terminator).  If there are two letters separated by a space,
the length calculation gives the value `3`, and so on.  This is the
maximum number of arguments there can be; if the string is 30 letters
with no spacing, then it will over-allocate the `argv` array.  It would
be possible to `realloc()` the array to the correct size, but there is
limited benefit to doing that unless the over-allocation is egregiously
wrong — say, more than 128 bytes (or 16 too many arguments).  You'd
then need to capture the number of entries in the `argv` array, which is
easily done, but the current code doesn't do it.  The code checks that
the memory allocation succeeded and if there's a problem, resets the
structure.  It could actually call `free_argv()` to do that reset — it
probably should, in fact.

Assuming that the necessary memory was allocated, the main loop scans
over the copy of the string, skipping white space, then setting the next
argument pointer, then finding the end of the argument, and repeating.

When that's done, it returns the structure.

The main program uses POSIX
[`getline()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html)
to read the input because it makes life so easy.  The code should check
that the last character read was a newline before zapping it.  It would
be possible to use `buffer[strcspn(buffer, "\n")] = '\0';` to avoid
zapping the last character of a file that did not end with a newline.

The code does assume that `calloc()` sets the pointers to null —
that's the case on the vast majority of CPUs, and you're unlikely to
come across a system where that's a problem (but there used to be
systems where it could be a problem, once upon a quarter century or more
ago).

Sample run:
```none
  a  b  c
line [  a  b  c]
argc 3
0 = [a]
1 = [b]
2 = [c]
abc def  ghi jkl
line [abc def  ghi jkl   ]
argc 4
0 = [abc]
1 = [def]
2 = [ghi]
3 = [jkl]

line []
argc 0

line [    ]
argc 0
    dddd     eeeee    zzzzz
line [    dddd     eeeee    zzzzz      ]
argc 3
0 = [dddd]
1 = [eeeee]
2 = [zzzzz]
[ a = b + c ]
line [[ a = b + c ]]
argc 7
0 = [[]
1 = [a]
2 = [=]
3 = [b]
4 = [+]
5 = [c]
6 = []]
```
This gives you a solid basis to adapt to suit your requirements.  Note
that you need to track both `argv` and the `argb` in some way.  This
mechanism gives you a structure that is self-contained.  In the code in
the question, if it is permissible to zap the `buf` string, then you
could use that instead of making a copy.  The `argc` element is optional
but convenient; the null pointer at the end of `argv` also reliably
tells you how many arguments there are.

The parsing code can be made more complex to recognize quoted strings
and backslash escapes and other notations — splitting on white space
alone is fairly simplistic.

The functions are made `static` because they aren't accessed outside
this source file.  If they were going to be accessed outside the file,
there'd be a header defining the structure type and the two function
signatures — and both the file defining the functions and the files
using the functions would include that header to gain access to the
relevant information, and the functions would no longer be `static`, of
course.
