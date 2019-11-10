/*
** Demonstration of reading the words in a file and sorting them.
** Using package aoscopy.[ch] (and stderr.[ch]) from libsoq.
*/

#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aoscopy.h"
#include "stderr.h"

static int compare(const void *p_lhs, const void *p_rhs)
{
    const char *lhs = *(char **)p_lhs;
    const char *rhs = *(char **)p_rhs;
    return strcmp(lhs, rhs);
}

static void dump_aosc(const char *tag, AoS_Copy *aos)
{
    size_t size = aosc_length(aos);
    char **array = aosc_base(aos);
    printf("%s (%zu entries):\n", tag, size);
    for (size_t i = 0; i < size; i++)
        printf("%.2zu: %s\n", i, array[i]);
}

int main(void)
{
    err_setarg0("sortwords2");

    AoS_Copy *aos = aosc_create(100);
    if (aos == 0)
        err_syserr("failed to allocate an AoS_Copy structure: ");

    char  *buffer = 0;
    size_t buflen = 0;
    ssize_t linelen;

    while ((linelen = getline(&buffer, &buflen, stdin)) != -1)
    {
        int offset = 0;
        int nbytes;
        assert(linelen < 1024 * 1024);
        char nxt_word[linelen + 1];
        while (sscanf(buffer + offset, "%s%n", nxt_word, &nbytes) == 1)
        {
            if (!aosc_add(aos, nxt_word))
                err_syserr("Failed to add word [%.64s]\n", nxt_word);
            offset += nbytes;
        }
    }

    free(buffer);

    dump_aosc("Before sorting", aos);
    qsort(aosc_base(aos), aosc_length(aos), sizeof(char *), compare);
    dump_aosc("After sort", aos);

    aosc_destroy(aos);

    /* Avoid an 'in use at exit (reachable)' record in valgrind */
    /* macOS Mojave 10.14.6 with Valgrind 3.14.0.GIT */
    fclose(stdin);

    return 0;
}
