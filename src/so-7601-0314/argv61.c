/* SO 7601-0314 */
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
        free_argv(&av);
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
