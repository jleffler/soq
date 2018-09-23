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

