### Stack Overflow Question 5208-4867

[SO 5208-4867](https://stackoverflow.com/q/52084867) &mdash;
Running wc using execvp() recognizers home/usr/foo.txt but not ~/foo.txt

Answer given:

When you type a file name such as `~/foo.txt` at the command line, the
shell expands it for you before running the command.
You therefore have to do that expansion in your C code if you want it to
work — or use a shell to do the expansion for you.
Neither the `execvp()` function nor the `wc` command has any problem
with `~`; there simply isn't a directory called `~` in the current
directory (and therefore there isn't a file called `foo.txt` in the
non-existent directory).

It's not all that hard to write the code to do the job (though doing it
properly per POSIX requires attention to detail — see [Tilde
expansion](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_01)).

However, there are also standard POSIX functions that can help and do
that job, notably
[`wordexp()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/wordexp.html).
Although the standard doesn't explicitly mention tilde expansion, it
does mention `WRDE_NOCMD` to suppress [command
substitution](http://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_03),
so it is supposed to do a thorough job and tilde expansion should be
included in a conforming implementation.

Here is some simple test code exercising the function:

    #include "stderr.h"
    #include <stdio.h>
    #include <wordexp.h>

    /*
    int wordexp(const char *restrict words, wordexp_t *restrict pwordexp,
           int flags);
    void wordfree(wordexp_t *pwordexp);
    */

    static void do_wordexp(const char *name)
    {
        wordexp_t wx = { 0 };
        if (wordexp(name, &wx, WRDE_NOCMD) != 0)
            err_remark("Failed to expand word [%s]\n", name);
        else
        {
            printf("Expansion of [%s]:\n", name);
            for (size_t i = 0; i < wx.we_wordc; i++)
                printf("%zu: [%s]\n", i+1, wx.we_wordv[i]);
            wordfree(&wx);
        }
    }

    int main(int argc, char **argv)
    {
        err_setarg0(argv[0]);

        if (argc <= 1)
            do_wordexp("~/.profile");
        else
        {
            for (int i = 1; i < argc; i++)
                do_wordexp(argv[i]);
        }
        return 0;
    }

And here are a couple of sample runs (program `wexp19` built from
`wexp19.c`):

    $ wexp19
    Expansion of [~/.profile]:
    1: [/Users/jonathanleffler/.profile]
    $ wexp19 '~informix/bin/oninit' '~/bin/rfmt'  '~/bin/al ~/bin/b?' '~/bin/f?' '$IXD/bin/onstat' ' ~/bin/ow '
    Expansion of [~informix/bin/oninit]:
    1: [/Users/informix/bin/oninit]
    Expansion of [~/bin/rfmt]:
    1: [/Users/jonathanleffler/bin/rfmt]
    Expansion of [~/bin/al ~/bin/b?]:
    1: [/Users/jonathanleffler/bin/al]
    2: [/Users/jonathanleffler/bin/bk]
    Expansion of [~/bin/f?]:
    1: [/Users/jonathanleffler/bin/fd]
    2: [/Users/jonathanleffler/bin/fl]
    3: [/Users/jonathanleffler/bin/fm]
    Expansion of [$IXD/bin/onstat]:
    1: [/opt/informix/12.10.FC6/bin/onstat]
    Expansion of [ ~/bin/ow ]:
    1: [/Users/jonathanleffler/bin/ow]
    $

Note in particular the result of expanding the quote-enclosed command
line argument `'~/bin/al ~/bin/b?'`; it is split and the words are
separately expanded.
The next to last argument expands the environment variable `$IXD` from
my environment, too, and the last example shows blanks are removed.
The single quotes on the command line are necessary to stop the shell
from doing what I want to demonstrate `wordexp()` doing.

Tests run on a Mac running macOS 10.13.6 High Sierra, and using GCC 8.2.0.  YMMV!
