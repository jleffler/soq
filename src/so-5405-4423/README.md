### Stack Overflow Question 5405-4423

[SO 5405-4423](https://stackoverflow.com/q/54054423) &mdash;
How To Avoid Abort Trap 6 Error at Runtime Using strncat()?

# Answer on SO

<sup> _I wrote the accompanying code in March 2018 to satisfy myself
about what goes on with `strncat()` for another question that got
deleted before I submitted an answer.  This is just retargeting that
code._</sup>

The `strncat()` function is (as I said in a
[comment](https://stackoverflow.com/questions/54054423/how-to-avoid-abort-trap-6-error-at-runtime-using-strncat#comment94943480_54054423))
evil and vile.  It is inconsistent with the `strncpy()` interface, too
— and different from anything you'll encounter anywhere else.  After
reading this, you will decide (with luck) that you should never use
`strncat()`.

# TL;DR — Never use `strncat()`

The C standard defines
[`strncat()`](https://port70.net/~nsz/c/c11/n1570.html#7.24.3.2) (and
POSIX agrees —
[`strncat()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/strncat.html))

> ### C11 §7.24.3.2 The `strncat` function
>
> **Synopsis**
>
>     #include <string.h>
>     char *strncat(char * restrict s1, const char * restrict s2, size_t n);
>
> **Description**
>
> The `strncat` function appends not more than `n` characters (a null
> character and characters that follow it are not appended) from the
> array pointed to by `s2` to the end of the string pointed to by `s1`.
> The initial character of `s2` overwrites the null character at the end
> of `s1`.  A terminating null character is always appended to the
> result.<sup>309)</sup> If copying takes place between objects that
> overlap, the behavior is undefined.
>
> **Returns**
>
> The `strncat` function returns the value of `s1`.
>
> <sup>309)</sup> Thus, the maximum number of characters that can end up
> in the array pointed to by `s1` is `strlen(s1)+n+1`.

The footnote identifies the biggest trap with `strncat()` — you can't
safely use:

    char *source = …;

    char target[100] = "";

    strncat(target, source, sizeof(target));

This is contrary to what occurs with most other functions that take an
array size argument **<sup>1</sup>** in C code.

To safely use `strncat()`, you should know:

* `target`
* `sizeof(target)` — or, for dynamically allocated space, the
   allocated length
* `strlen(target)` — you must know the length of what is already in
   the target string
* `source`
* `strlen(source)` — if you are concerned about whether the source
   string was truncated; not needed if you don't care

With that information, you could use:

    strncat(target, source, sizeof(target) - strlen(target) - 1);

However, doing that would be a little silly; if you know
`strlen(target)`, you can avoid making `strncat()` find it out again by
using:

    strncat(target + strlen(target), source, sizeof(target) - strlen(target) - 1);

Note that `strncat()` guarantees null termination, unlike
[`strncpy()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/strncpy.html).
That means that you could use:

    size_t t_size = sizeof(target);
    size_t t_length = strlen(target);
    strncpy(target + t_length, source, t_size - t_length - 1);
    target[t_size - 1] = '\0';

and you would be guaranteed the same result if the source string is too
long to be appended to the target.


## Demo Code

Multiple programs that illustrate aspects of `strncat()`.  Note that on
macOS, there is a macro definition of `strncat()` in `<string.h>` which
invokes a different function — `__builtin___strncat_chk` — which
validates the uses of `strncat()`.  For compactness of the command
lines, I've dropped two warning compiler options that I normally use —
`-Wmissing-prototypes -Wstrict-prototypes` — but that doesn't affect
any of the compilations.

### `strncat19.c`

This demonstrates one safe use of `strncat()`:

    #include <stdio.h>
    #include <string.h>

    int main(void)
    {
        char spare1[16] = "abc";
        char buffer[16] = "";
        char spare2[16] = "xyz";
        strncat(buffer, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", sizeof(buffer) - 1);
        printf("%zu: [%s]\n", strlen(buffer), buffer);
        printf("spare1 [%s]\n", spare1);
        printf("spare2 [%s]\n", spare2);
        return 0;
    }

It compiles cleanly (with Apple's `clang` from XCode 10.1 (`Apple LLVM
version 10.0.0 (clang-1000.11.45.5)`) and GCC 8.2.0, even with stringent
warnings set:

    $ gcc -O3 -g -std=c11 -Wall -Wextra -Werror strncat19.c -o strncat19
    $ ./strncat19
    15: [ABCDEFGHIJKLMNO]
    spare1 [abc]
    spare2 [xyz]
    $

### `strncat29.c`

This is similar to `strncat19.c` but (a) allows you to specify a string
to be copied on the command line, and (b) incorrectly uses
`sizeof(buffer)` instead of `sizeof(buffer) - 1` for the length.

    #include <stdio.h>
    #include <string.h>

    int main(int argc, char **argv)
    {
        const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (argc == 2)
            data = argv[1];
        char spare1[16] = "abc";
        char buffer[16] = "";
        char spare2[16] = "xyz";
        strncat(buffer, data, sizeof(buffer));
        printf("%zu: [%s]\n", strlen(buffer), buffer);
        printf("spare1 [%s]\n", spare1);
        printf("spare2 [%s]\n", spare2);
        return 0;
    }

This code doesn't compile with the stringent warning options:

    $ clang -O3 -g -std=c11 -Wall -Wextra -Werror strncat29.c -o strncat29
    strncat29.c:12:27: error: the value of the size argument in 'strncat' is too large, might lead to a buffer
          overflow [-Werror,-Wstrncat-size]
        strncat(buffer, data, sizeof(buffer));
                              ^~~~~~~~~~~~~~
    strncat29.c:12:27: note: change the argument to be the free space in the destination buffer minus the terminating null byte
        strncat(buffer, data, sizeof(buffer));
                              ^~~~~~~~~~~~~~
                              sizeof(buffer) - strlen(buffer) - 1
    1 error generated.
    $ gcc -O3 -g -std=c11 -Wall -Wextra -Werror strncat29.c -o strncat29
    In file included from /usr/include/string.h:190,
                     from strncat29.c:2:
    strncat29.c: In function ‘main’:
    strncat29.c:12:5: error: ‘__builtin___strncat_chk’ specified bound 16 equals destination size [-Werror=stringop-overflow=]
         strncat(buffer, data, sizeof(buffer));
         ^~~~~~~
    cc1: all warnings being treated as errors
    $

Even with no warnings requested, the warning is given by GCC, but
because the `-Werror` option is absent, it produces an executable:

    $ gcc -o strncat29 strncat29.c
    In file included from /usr/include/string.h:190,
                     from strncat29.c:2:
    strncat29.c: In function ‘main’:
    strncat29.c:12:5: warning: ‘__builtin___strncat_chk’ specified bound 16 equals destination size [-Wstringop-overflow=]
         strncat(buffer, data, sizeof(buffer));
         ^~~~~~~
    $ ./strncat29
    Abort trap: 6
    $ ./strncat29 ZYXWVUTSRQPONMK
    15: [ZYXWVUTSRQPONMK]
    spare1 [abc]
    spare2 [xyz]
    $ ./strncat29 ZYXWVUTSRQPONMKL
    Abort trap: 6
    $

That is the `__builtin__strncat_chk` function at work.

### `strncat97.c`

This code also takes an optional string argument; it also pays attention
to whether there is another argument on the command line, and if so, it
invokes the `strncat()` function directly, rather than letting the macro
check it first:

    #include <stdio.h>
    #include <string.h>

    /*
    ** Demonstrating that strncat() should not be given sizeof(buffer) as
    ** the size, even if the string is empty to start with.  The use of
    ** (strncat) inhibits the macro expansion on macOS; the code behaves
    ** differently when the __strncat_chk function (on High Sierra or
    ** earlier - it's __builtin__strncat_chk on Mojave) is called instead.
    ** You get an abort 6 (but no other useful message) when the buffer
    ** length is too long.
    */

    int main(int argc, char **argv)
    {
        const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (argc >= 2)
            data = argv[1];
        char spare1[16] = "abc";
        char buffer[16] = "";
        char spare2[16] = "xyz";
        size_t len = (argc == 2) ? sizeof(buffer) : sizeof(buffer) - 1;
        if (argc < 3)
            strncat(buffer, data, len);
        else
            (strncat)(buffer, data, len);
        printf("buffer %2zu: [%s]\n", strlen(buffer), buffer);
        printf("spare1 %2zu: [%s]\n", strlen(spare1), spare1);
        printf("spare2 %2zu: [%s]\n", strlen(spare2), spare2);
        return 0;
    }

Now the compilers produce different results:

    $ gcc -O3 -g -std=c11 -Wall -Wextra -Werror strncat97.c -o strncat97
    strncat97.c: In function ‘main’:
    strncat97.c:26:9: error: ‘strncat’ output truncated copying 15 bytes from a string of length 26 [-Werror=stringop-truncation]
             (strncat)(buffer, data, len);
             ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cc1: all warnings being treated as errors
    $ clang -O3 -g -std=c11 -Wall -Wextra -Werror strncat97.c -o strncat97
    $

This demonstrates an advantage of using more than one compiler —
different compilers detect different problems on occasion.  This code is
messy trying to used different numbers of options to do multiple things.
It suffices to show:

    $ ./strncat97
    0x7ffee7506420: buffer 15: [ABCDEFGHIJKLMNO]
    0x7ffee7506430: spare1  3: [abc]
    0x7ffee7506410: spare2  3: [xyz]
    $ ./strncat97 ABCDEFGHIJKLMNOP
    Abort trap: 6
    $ ./strncat97 ABCDEFGHIJKLMNO
    0x7ffeea141410: buffer 15: [ABCDEFGHIJKLMNO]
    0x7ffeea141420: spare1  3: [abc]
    0x7ffeea141400: spare2  3: [xyz]
    $

### `strncat37.c`

This is the all-singing, all-dancing version of the programs above, with
option handling via `getopt()`.  It also uses my error reporting
routines; the code for them is available in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository on GitHub as files `stderr.c` and `stderr.h` in the
[src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.

    #include "stderr.h"
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>

    /*
    ** Demonstrating that strncat() should not be given sizeof(buffer) as
    ** the size, even if the string is empty to start with.  The use of
    ** (strncat) inhibits the macro expansion on macOS; the code behaves
    ** differently when the __strncat_chk function (on High Sierra or
    ** earlier - it's __builtin__strncat_chk on Mojave) is called instead.
    ** You get an abort 6 (but no other useful message) when the buffer
    ** length is too long.
    */

    static const char optstr[] = "fhlmsV";
    static const char usestr[] = "[-fhlmsV] [string]";
    static const char hlpstr[] =
        "  -f  Function is called directly\n"
        "  -h  Print this help message and exit\n"
        "  -l  Long buffer length -- sizeof(buffer)\n"
        "  -m  Macro cover for the function is used (default)\n"
        "  -s  Short buffer length -- sizeof(buffer)-1 (default)\n"
        "  -V  Print version information and exit\n"
        ;

    int main(int argc, char **argv)
    {
        err_setarg0(argv[0]);

        int f_flag = 0;
        int l_flag = 0;
        int opt;

        while ((opt = getopt(argc, argv, optstr)) != -1)
        {
            switch (opt)
            {
            case 'f':
                f_flag = 1;
                break;
            case 'h':
                err_help(usestr, hlpstr);
                /*NOTREACHED*/
            case 'l':
                l_flag = 1;
                break;
            case 'm':
                f_flag = 0;
                break;
            case 's':
                l_flag = 0;
                break;
            case 'V':
                err_version(err_getarg0(), &"@(#)$Revision$ ($Date$)"[4]);
                /*NOTREACHED*/
            default:
                err_usage(usestr);
                /*NOTREACHED*/
            }
        }

        if (optind < argc - 1)
            err_usage(usestr);

        const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (optind != argc)
            data = argv[optind];
        char spare1[16] = "abc";
        char buffer[16] = "";
        char spare2[16] = "xyz";
        size_t len = l_flag ? sizeof(buffer) : sizeof(buffer) - 1;

        printf("Specified length: %zu\n", len);
        printf("Copied string: [%s]\n", data);
        printf("Copied %s\n", f_flag ? "using strncat() function directly"
                                     : "using strncat() macro");

        if (f_flag)
            (strncat)(buffer, data, len);
        else
            strncat(buffer, data, len);

        printf("%p: buffer %2zu: [%s]\n", (void *)buffer, strlen(buffer), buffer);
        printf("%p: spare1 %2zu: [%s]\n", (void *)spare1, strlen(spare1), spare1);
        printf("%p: spare2 %2zu: [%s]\n", (void *)spare2, strlen(spare2), spare2);
        return 0;
    }

As before, Clang and GCC have different views on the acceptability of
the code (and `-Werror` means the warning from GCC is treated as an
error):

    $ clang -O3 -g -I./inc -std=c11 -Wall -Wextra -Werror strncat37.c -o strncat37 -L./lib  -lsoq
    $ gcc -O3 -g -I./inc -std=c11 -Wall -Wextra -Werror strncat37.c -o strncat37 -L./lib  -lsoq
    strncat37.c: In function ‘main’:
    strncat37.c:80:9: error: ‘strncat’ output may be truncated copying between 15 and 16 bytes from a string of length 26 [-Werror=stringop-truncation]
             (strncat)(buffer, data, len);
             ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cc1: all warnings being treated as errors
    $

When run:


    $ ./strncat37 -h
    Usage: strncat37 [-fhlmsV] [string]
      -f  Function is called directly
      -h  Print this help message and exit
      -l  Long buffer length -- sizeof(buffer)
      -m  Macro cover for the function is used (default)
      -s  Short buffer length -- sizeof(buffer)-1 (default)
      -V  Print version information and exit

    $ ./strncat37
    Specified length: 15
    Copied string: [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    Copied using strncat() macro
    0x7ffedff4e400: buffer 15: [ABCDEFGHIJKLMNO]
    0x7ffedff4e410: spare1  3: [abc]
    0x7ffedff4e3f0: spare2  3: [xyz]
    $ ./strncat37 -m -s
    Specified length: 15
    Copied string: [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    Copied using strncat() macro
    0x7ffeeaf043f0: buffer 15: [ABCDEFGHIJKLMNO]
    0x7ffeeaf04400: spare1  3: [abc]
    0x7ffeeaf043e0: spare2  3: [xyz]
    $ ./strncat37 -m -l
    Specified length: 16
    Copied string: [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    Copied using strncat() macro
    Abort trap: 6
    $ ./strncat37 -f -s
    Specified length: 15
    Copied string: [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    Copied using strncat() function directly
    0x7ffeef0913f0: buffer 15: [ABCDEFGHIJKLMNO]
    0x7ffeef091400: spare1  3: [abc]
    0x7ffeef0913e0: spare2  3: [xyz]
    $ ./strncat37 -f -l
    Specified length: 16
    Copied string: [ABCDEFGHIJKLMNOPQRSTUVWXYZ]
    Copied using strncat() function directly
    0x7ffeed8d33f0: buffer 16: [ABCDEFGHIJKLMNOP]
    0x7ffeed8d3400: spare1  0: []
    0x7ffeed8d33e0: spare2  3: [xyz]
    $

The default behaviour is also the correct behaviour; the program doesn't
crash and doesn't produce unexpected side-effects.  When run using the
macro and with too long a length specified (`-m -l`), the program
crashes.  When run using the function and too long a length (`-f -l`),
the program overwrites the first byte of array `spare1` with the null
added after the end of `buffer`, and shows 16 bytes of data instead of
15.

<hr>

**<sup>1</sup>** One exception is in `scanf()` when you use `%31s` or
similar; the number specified is the number of non-null characters that
can be stored in the string; it will add a null byte after reading 31
other characters.  So again, the maximum size that can be used safely is
`sizeof(string) - 1`.

You can find the code for `strncatXX.c` in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository on GitHub in the
[src/so-5405-4423](https://github.com/jleffler/soq/tree/master/src/so-5405-4423)
sub-directory.

<hr>

# Analysis of Code from Question

Taking the code from the question and changing `int main(){` to `int
main(void){` because my default compilation options generate an error
(it would be a warning if I didn't use `-Werror`) for the non-prototype
`main()`, and adding `return 0;` at the end of `main()`, what's left
gives me these errors compiling with GCC 8.2.0 on a Mac running macOS
10.14.2 Mojave:

    $ gcc -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes so-5405-4423-v1.c -o so-5405-4423-v1
    In file included from /opt/gcc/v8.2.0/lib/gcc/x86_64-apple-darwin17.7.0/8.2.0/include-fixed/stdio.h:425,
                     from so-5405-4423-v1.c:1:
    so-5405-4423-v1.c: In function ‘main’:
    so-5405-4423-v1.c:32:29: error: ‘%d’ directive writing between 1 and 2 bytes into a region of size between 1 and 100 [-Werror=format-overflow=]
                 sprintf(result, "%s%d, ", text, i); // Format the text and store it in result
                                 ^~~~~~~~
    so-5405-4423-v1.c:32:29: note: directive argument in the range [0, 10]
    so-5405-4423-v1.c:32:13: note: ‘__builtin___sprintf_chk’ output between 4 and 104 bytes into a destination of size 100
                 sprintf(result, "%s%d, ", text, i); // Format the text and store it in result
                 ^~~~~~~
    so-5405-4423-v1.c:37:29: error: ‘ ’ directive writing 1 byte into a region of size between 0 and 99 [-Werror=format-overflow=]
                 sprintf(result, "%s%d ", text, i); // Format the text and store it in result
                                 ^~~~~~~
    so-5405-4423-v1.c:37:13: note: ‘__builtin___sprintf_chk’ output between 3 and 102 bytes into a destination of size 100
                 sprintf(result, "%s%d ", text, i); // Format the text and store it in result
                 ^~~~~~~
    cc1: all warnings being treated as errors
    $

The compiler notes that `text` is a string that can contain 0 to 99
characters, so it could in theory cause an overflow when concatenated
with a number and the `", "` (or the `" "` for one iteration).  The fact
that it is initialized to `"String No."` means that there isn't an
overflow risk, but you can mitigate that by using a shorter length for
`text` — say `20` instead of `100`.

I admit that this warning, which is relatively new in GCC, is not always
as helpful as all that (and this is a case where the code is OK, but the
warning still appears).  I usually _do_ fix the problem, if only because
it currently shows up with my default options and code doesn't compile
with any warnings with `-Werror` and I'm not ready to do without that
level of protection.  I don't use `clang`'s `-Weverything` option raw;
it produces warnings which are definitely counter-productive (at least
AFAIAC).  However, I countermand the 'everything' options that don't
work for me.  If a `-Wall` or `-Wextra` option was too painful, for some
reason, I'd countermand it, but cautiously.  I'd review the pain level,
and aim to deal with whatever the symptom is.

You also have the loop:

    for(j = 0; j < 10; j++){ // Now loop to change the line

        strcpy(lines[i], line); // Copy the line of text into each line of the array

        fputs(lines[i], file); // Put each line into the file

    }


Unfortunately, when this loop runs, `i` is equal to `10`, which is out
of bounds of the array `lines`.  This can lead to a crash.  Presumably,
the index should be `j` instead of `i`.

Here's an instrumented version of your code (`so-5405-4423-v2.c`):

    #include <stdio.h>
    #include <string.h>

    char line[1001];
    char lines[11][1001];
    char info[100];

    char *extra_info(char string_1[], char string_2[], char string_3[],
                     char string_4[], char string_5[]);

    int main(void)
    {
        char result[100], text[20];
        const char filename[] = "test.txt";
        FILE *file;

        strcpy(text, "String No.");

        file = fopen(filename, "w+");
        if (file == NULL)
        {
            fprintf(stderr, "Failed to open file '%s' for writing/update\n", filename);
            return 1;
        }

        for (int i = 0; i < 10; i++)
        {
            if (i != 9)
                sprintf(result, "%s%d, ", text, i);
            else
                sprintf(result, "%s%d ", text, i);

            fprintf(stderr, "Iteration %d:\n", i);
            fprintf(stderr, "1 result (%4zu): [%s]\n", strlen(result), result);
            fprintf(stderr, "1 line   (%4zu): [%s]\n", strlen(line), line);
            extra_info("st", "nd", "rd", "th", "th");
            fprintf(stderr, "2 line   (%4zu): [%s]\n", strlen(line), line);
            fprintf(stderr, "1 info   (%4zu): [%s]\n", strlen(info), info);
            strncat(line, info, 100);
            fprintf(stderr, "3 line   (%4zu): [%s]\n", strlen(line), line);
            printf("%s", result);
            strncat(line, result, 15);
            fprintf(stderr, "3 line   (%4zu): [%s]\n", strlen(line), line);
        }

        fprintf(stderr, "4 line   (%4zu): [%s]\n", strlen(line), line);
        strncat(line, "\n\n", 2);

        for (int j = 0; j < 10; j++)
        {
            strcpy(lines[j], line);
            fputs(lines[j], file);
        }

        fclose(file);

        return 0;
    }

    char *extra_info(char string_1[], char string_2[], char string_3[],
                     char string_4[], char string_5[])
    {
        char text[100];

        sprintf(text, " 1%s", string_1);
        fprintf(stderr, "EI 1: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_1), string_1, strlen(line), line);
        strncat(line, text, 100);

        sprintf(text, ", 2%s", string_2);
        fprintf(stderr, "EI 2: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_2), string_2, strlen(line), line);
        strncat(line, text, 100);

        sprintf(text, ", 3%s", string_3);
        fprintf(stderr, "EI 3: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_3), string_3, strlen(line), line);
        strncat(line, text, 100);

        sprintf(text, ", 4%s", string_4);
        fprintf(stderr, "EI 4: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_4), string_4, strlen(line), line);
        strncat(line, text, 100);

        sprintf(text, ", 5%s.", string_5);
        fprintf(stderr, "EI 5: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_5), string_5, strlen(line), line);
        strncat(line, text, 100);

        fprintf(stderr, "EI 6: copy (%zu) [%s] to info\n", strlen(line), line);
        strcpy(info, line);

        return line;
    }

When run, it produces output similar to:

    Iteration 0:
    1 result (  13): [String No.0, ]
    1 line   (   0): []
    EI 1: add (2) [st] to (0) []
    EI 2: add (2) [nd] to (4) [ 1st]
    EI 3: add (2) [rd] to (9) [ 1st, 2nd]
    EI 4: add (2) [th] to (14) [ 1st, 2nd, 3rd]
    EI 5: add (2) [th] to (19) [ 1st, 2nd, 3rd, 4th]
    EI 6: copy (25) [ 1st, 2nd, 3rd, 4th, 5th.] to info
    2 line   (  25): [ 1st, 2nd, 3rd, 4th, 5th.]
    1 info   (  25): [ 1st, 2nd, 3rd, 4th, 5th.]
    3 line   (  50): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.]
    3 line   (  63): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0, ]
    Iteration 1:
    1 result (  13): [String No.1, ]
    1 line   (  63): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0, ]
    EI 1: add (2) [st] to (63) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0, ]
    EI 2: add (2) [nd] to (67) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st]
    EI 3: add (2) [rd] to (72) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd]
    EI 4: add (2) [th] to (77) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd]
    EI 5: add (2) [th] to (82) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th]
    EI 6: copy (88) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.] to info
    2 line   (  88): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.]
    1 info   (  88): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.]
    3 line   ( 176): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.]
    3 line   ( 189): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1, ]
    Iteration 2:
    1 result (  13): [String No.2, ]
    1 line   ( 189): [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1, ]
    EI 1: add (2) [st] to (189) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1, ]
    EI 2: add (2) [nd] to (193) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1,  1st]
    EI 3: add (2) [rd] to (198) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1,  1st, 2nd]
    EI 4: add (2) [th] to (203) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1,  1st, 2nd, 3rd]
    EI 5: add (2) [th] to (208) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1,  1st, 2nd, 3rd, 4th]
    EI 6: copy (214) [ 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th. 1st, 2nd, 3rd, 4th, 5th.String No.0,  1st, 2nd, 3rd, 4th, 5th.String No.1,  1st, 2nd, 3rd, 4th, 5th.] to info
    String No.0, String No.1, Abort trap: 6

When you observe that 214 bytes are copied from `line` (which is big
enough to hold that string) to `info` (which is not — it is but 100
bytes long), the ensuing crash is not very surprising.  It isn't
entirely clear what the desired behaviour is.

On my Mac, the `lldb` debugger reports the crash in `__strcpy_chk`;
AFAICT, it's in the line highlighted at the end of `extra_info()`:

    frame #6: 0x00007fff681bbe84 libsystem_c.dylib`__strcpy_chk + 83
    frame #7: 0x00000001000017cc so-5405-4423-v2`extra_info(string_1=<unavailable>, string_2=<unavailable>, string_3="rd", string_4="th", string_5="th") at so-5405-4423-v2.c:86

So, while it apparently isn't `strncat()` that causes the crash here,
the way that `strncat()` _is_ used is not obviously correct — IMO, it
is incorrect, but views may differ.  And I still stand by my basic
conclusion: **Do not use `strncat()`**.

