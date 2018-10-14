#include "stderr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *v1, const void *v2)
{
    int i1 = *(const int *)v1;
    int i2 = *(const int *)v2;
    return (i1 > i2) - (i1 < i2);
}

static void dump_integers(const char *tag, size_t n_values, int *values)
{
    printf("%s (%zu):\n", tag, n_values);
    int length = 0;
    const char *pad = "";
    for (size_t i = 0; i < n_values; i++)
    {
        int nbytes = printf("%s%d", pad, values[i]);
        if (nbytes < 0)
            err_error("failed to print an integer\n");
        length += nbytes;
        pad = ", ";
        if (length >= 70)
        {
            putchar('\n');
            pad = "";
            length = 0;
        }
    }
    if (length != 0)
        putchar('\n');
}

/*
** Concept for general purpose copy-of-pointer (aoscopy.h, aomcopy.hh) array:
** A sorted array with duplicate entries consists of a sequence of units
** such that items [a..b) are duplicates and [b..c) are distinct.
** For each such unit, move [a+1..b) to a list of duplicates.
** If a != b, move [b..c) to [a+1..c-1-b).
**
** - i = 0
** - while i < num_values
** -     n = i
** -     m = i+1
** -     while cmp(data[n], data[m]) == 0 && m < num_values
** -         m++
** -     // n..m-1 are the same; if there's more than one, all but one moves to dups list
** -     x = m
** -     y = m+1
** -     while (r = cmp(data[y-1], data[y])) != 0 && y < num_values
** -         assert(r < 0)
** -         y++
** -     // x..y-1 are in monotonic increasing order
** -     if (m - 1 > n)
** -         move items n+1..m-1 to dups list
** -     move items x..y-1 to n+1
** - move items from dups list to tail of main list
** - free dups list
** - return number of unique items
*/

static size_t uniqify_int(int *values, size_t num_values)
{
    if (num_values < 2)
        return num_values;
    size_t i, j;
    for (i = 0, j = 1; j < num_values; j++)
    {
        if (values[i] != values[j])
        {
            //if (j > i + 1)
            //    values[++i] = values[j];
            //else
            //    ++i;
            i++;
            if (j > i)
                values[i] = values[j];
        }
    }
    return i + 1;
}

int main(int argc, char **argv)
{
    if (argc != 0)
        err_setarg0(argv[0]);

    size_t num_values = 0;
    size_t max_values = 0;
    int   *values = 0;

    int k;
    while (scanf("%d", &k) == 1)
    {
        if (num_values >= max_values)
        {
            assert(num_values == max_values);
            size_t new_num = num_values * 2 + 2;
            void *new_space = realloc(values, new_num * sizeof(values[0]));
            if (new_space == 0)
                err_syserr("failed to reallocate %zu bytes of memory: ", new_num * sizeof(values[0]));
            values = new_space;
            max_values = new_num;
        }
        values[num_values++] = k;
    }

    dump_integers("Unsorted", num_values, values);
    qsort(values, num_values, sizeof(values[0]), cmp_int);
    dump_integers("Sorted", num_values, values);
    size_t num_uniq = uniqify_int(values, num_values);
    dump_integers("Unique", num_uniq, values);

    free(values);

    return 0;
}

