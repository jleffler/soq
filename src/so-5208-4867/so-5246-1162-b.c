/* SO 5246-1162 */
#include <stdio.h>
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

static void expansion_demo(char const *str)
{
    printf("Before expansion: [%s]\n", str);
    wordexp_t exp;
    int rc;
    if ((rc = wordexp(str, &exp, 0)) == 0)
    {
        for (size_t i = 0; i < exp.we_wordc; i++)
            printf("After expansion %zu: [%s]\n", i, exp.we_wordv[i]);
        wordfree(&exp);
    }
    else
        printf("Expansion failed (%d: %s)\n", rc, worderror(rc));
}

int main(void)
{
    char const *str1 = "\\''\\\"\"\"\\\"TEST1\\\"\"\"\\\"'\\'";
    expansion_demo(str1);

    char const *str2 = "'\\'\"\\\"\\\"\"TEST2\"\\\"\\\"\"\\''";
    expansion_demo(str2);

    return 0;
}
