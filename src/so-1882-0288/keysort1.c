/* https://stackoverflow.com/q/18820288 Sorting based on key from a file */

/*
** Input format
**
** Key: 1 rec:A B C D E F ...
** Key: 2 rec:1 2 3 4 5 6 ...
**
** Sorting on the key number in column 2 of the records.
**
** Read from standard input; write to standard output.
*/

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void err_exit(const char *fmt, ...);

typedef struct data
{
    char *line;
    int   key;
} data;

static int cmp_data(const void *v1, const void *v2)
{
    const data *d1 = v1;
    const data *d2 = v2;
    if (d1->key < d2->key)
        return -1;
    else if (d1->key > d2->key)
        return +1;
    else
        return 0;
}

int main(void)
{
    char buffer[4096];
    data *array = 0;
    size_t array_len = 0;
    size_t array_max = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != 0)
    {
        if (array_len >= array_max)
        {
            size_t new_size = (array_max + 2) * 2;
            void *space = realloc(array, new_size * sizeof(data));
            if (space == 0)
                err_exit("Out of memory (1)");
            array = space;
            array_max = new_size;
        }
        array[array_len].line = strdup(buffer);
        if (array[array_len].line == 0)
            err_exit("Out of memory (2)");
        if (sscanf(array[array_len].line, "%*[^:]: %d", &array[array_len].key) != 1)
            err_exit("Format error - no number in right place in: %.20s...\n",
                     array[array_len].line);
        //printf("%3zu:%.10d: %s", array_len, array[array_len].key,
        //       array[array_len].line);
        array_len++;
    }

    qsort(array, array_len, sizeof(data), cmp_data);

    for (size_t i = 0; i < array_len; i++)
        fputs(array[i].line, stdout);

    return 0;
}

void err_exit(const char *fmt, ...)
{
    int errnum = errno;
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
    exit(EXIT_FAILURE);
}
