/* SO 5208-4867 */
/* Influenced by SO 5246-1162: Preserve quotes when using wordexp */
#include "stderr.h"
#include <stdio.h>
#include <stdlib.h>
#include <wordexp.h>

static const char *worderror(int errnum)
{
    switch (errnum)
    {
    case WRDE_BADCHAR:
        return "One of the unquoted characters - <newline>, '|', '&', ';', '<', '>', '(', ')', '{', '}' - appears in an inappropriate context";
    case WRDE_BADVAL:
        return "Reference to undefined shell variable when WRDE_UNDEF was set in flags to wordexp()";
    case WRDE_CMDSUB:
        return "Command substitution requested when WRDE_NOCMD was set in flags to wordexp()";
    case WRDE_NOSPACE:
        return "Attempt to allocate memory in wordexp() failed";
    case WRDE_SYNTAX:
        return "Shell syntax error, such as unbalanced parentheses or unterminated string";
    default:
        return "Unknown error from wordexp() function";
    }
}

static void do_wordexp(const char *name)
{
    wordexp_t wx = { 0 };
    int rc;
    if ((rc = wordexp(name, &wx, WRDE_NOCMD | WRDE_SHOWERR | WRDE_UNDEF)) != 0)
        err_remark("Failed to expand word [%s]\n%d: %s\n", name, rc, worderror(rc));
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
    {
        char *buffer = 0;
        size_t buflen = 0;
        int length;
        while ((length = getline(&buffer, &buflen, stdin)) != -1)
        {
            buffer[length-1] = '\0';
            do_wordexp(buffer);
        }
        free(buffer);
    }
    else
    {
        for (int i = 1; i < argc; i++)
            do_wordexp(argv[i]);
    }
    return 0;
}

