/*
** Demonstration of reading the words in a file and sorting them.
*/

#include "posixver.h"
#include <assert.h>
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

static void dump_array(const char *tag, size_t size, char *array[size])
{
    printf("%s:\n", tag);
    for (size_t i = 0; i < size; i++)
        printf("%.2zu: %s\n", i, array[i]);
}

int main(void)
{
    char **words = 0;
    size_t max_words = 0;
    size_t num_words = 0;
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
            if (num_words == max_words)
            {
                size_t newnum = (max_words + 2) * 2;
                void *newptrs = realloc(words, newnum * sizeof(*words));
                if (newptrs == 0)
                {
                    fprintf(stderr, "Out of memory (%zu bytes requested)\n",
                            newnum * sizeof(*words));
                    exit(1);
                }
                words = newptrs;
                max_words = newnum;
            }
            words[num_words++] = strdup(nxt_word);
            offset += nbytes;
        }
    }

    free(buffer);

    dump_array("Before sorting", num_words, words);
    qsort(words, num_words, sizeof(char *), compare);
    dump_array("After sort", num_words, words);

    for (size_t i = 0; i < num_words; i++)
        free(words[i]);
    free(words);

    /* Avoid an 'in use at exit (reachable)' record in valgrind */
    /* Mac OS X El Capitan 10.11.4, Valgrind 3.12.0.SVN */
    /* macOS High Sierra 10.13.4, Valgrind 3.14.0.GIT */
    fclose(stdin);

    return 0;
}
