/* SO 4477-2009 */
/* Counting the probes for binary searches */

#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "stderr.h"

static int trace = 0;
static size_t counter = 0;

static const char optstr[] = "hx";
static const char usestr[] = "[-hx]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -x  Print verbose information\n"
    ;

static int binary_search(const int values[], int n, int value)
{
    int top = n - 1;
    int bottom = 0;

    counter = 0;
    while (top >= bottom)
    {
        int searchpos = bottom + (top - bottom) / 2;
        if (trace)
            printf("T = %2d, B = %2d, M = %2d, V = %d, S = %d\n",
                   top, bottom, searchpos, value, values[searchpos]);
        counter++;
        if (value == values[searchpos])
        {
            return searchpos;
        }
        else if (value > values[searchpos])
        {
            bottom = searchpos + 1;
        }
        else
        {
            top = searchpos - 1;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    const int data[] =
    {
        10, 12, 12, 12, 13, 14, 14, 17, 19, 19,
        19, 20, 20, 21, 21, 22, 23, 23, 24, 25,
        26, 26, 27, 30, 32, 32, 33, 33, 34, 34,
        35, 36, 37, 38, 40, 40, 40, 41, 42, 44,
        44, 46, 47, 49, 49, 49, 49, 50, 50, 51,
        52, 54, 56, 56, 57, 59, 60, 60, 61, 62,
        65, 65, 67, 68, 68, 68, 68, 68, 69, 72,
        74, 74, 74, 79, 86, 86, 87, 87, 87, 88,
        88, 89, 89, 89, 91, 91, 91, 92, 93, 93,
        93, 94, 95, 96, 97, 97, 98, 98, 98, 99,
    };
    enum { DATA_SIZE = sizeof(data) / sizeof(data[0]) };

    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'x':
            trace = 1;
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    assert(DATA_SIZE == 100);
    if (trace)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                printf("%3d", data[10 * i + j]);
            putchar('\n');
        }
    }
    putchar('\n');

    /* Check monotonic non-decreasing data */
    for (int j = 0; j < DATA_SIZE - 1; j++)
        assert(data[j] <= data[j+1]);

    int lo = data[0] - 1;
    int hi = data[DATA_SIZE - 1] + 2;

    for (int i = lo; i < hi; i++)
    {
        int r = binary_search(data, DATA_SIZE, i);
        printf("Size %3d, search %3d, result = %2d [%2d], probes %2zu\n",
               DATA_SIZE, i, r, (r == -1) ? -1 : data[r], counter);
    }

    return 0;
}
