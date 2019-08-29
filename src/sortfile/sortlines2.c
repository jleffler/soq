/*
** Originally a demonstration that a comparator in an SO answer was incorrect.
** Now a simple demonstration of reading a file and sorting.
*/

#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Correct comparator */
static int compare(const void *p_lhs, const void *p_rhs)
{
    const char *lhs = *(char **)p_lhs;
    const char *rhs = *(char **)p_rhs;
    return strcmp(lhs, rhs);
}

/* Lines in array are terminated by a newline */
static void dump_array(const char *tag, size_t size, char *array[size])
{
    printf("%s:\n", tag);
    for (size_t i = 0; i < size; i++)
        printf("%.2zu: %s", i, array[i]);
}

int main(void)
{
    char **ptrs = 0;
    size_t numptrs = 0;
    char  *buffer = 0;
    size_t buflen = 0;
    size_t count = 0;

    while (getline(&buffer, &buflen, stdin) != -1)
    {
        if (count == numptrs)
        {
            size_t newnum = (numptrs + 2) * 2;
            void *newptrs = realloc(ptrs, newnum * sizeof(*ptrs));
            if (newptrs == 0)
            {
                fprintf(stderr, "Out of memory (%zu bytes requested)\n", newnum * sizeof(*ptrs));
                exit(1);
            }
            ptrs = newptrs;
            numptrs = newnum;
        }
        ptrs[count++] = buffer;
        buffer = 0;
        buflen = 0;
    }

    free(buffer);

    dump_array("Before sorting", count, ptrs);
    qsort(ptrs, count, sizeof(char *), compare);
    dump_array("After sort", count, ptrs);

    for (size_t i = 0; i < count; i++)
        free(ptrs[i]);
    free(ptrs);

    /* Avoid an 'in use at exit (reachable)' record in valgrind */
    /* Mac OS X El Capitan 10.11.4, Valgrind 3.12.0.SVN */
    /* macOS High Sierra 10.13.4, Valgrind 3.14.0.GIT */
    fclose(stdin);

    return 0;
}
