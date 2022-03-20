/* SO 6366-2914 */
/*
** Sort values greater than N first in ascending order, and values less
** than N last in descending order, with values equal to N in the middle.
*/

#include <stdio.h>
#include <stdlib.h>

static int N;

static int comparator(const void *v1, const void *v2)
{
    int a = *(int *)v1;
    int b = *(int *)v2;

    if (a < N && b < N)
        return (a < b) - (a > b);   /* Descending */
    else if (a > N && b > N)
        return (a > b) - (a < b);   /* Ascending */
    else if (a > N && b < N)
        return -1;
    else if (a < N && b > N)
        return +1;
    else if (a == N && b > N)
        return +1;
    else if (b == N && a < N)
        return +1;
    else if (a == N && b < N)
        return -1;
    else if (b == N && a > N)
        return -1;
    else
        return 0;
}

static void dump_array(const char *tag, size_t n, int *data)
{
    printf("%s (%zu):\n", tag, n);
    const char *pad = "";
    size_t i;
    for (i = 0; i < n; i++)
    {
        if (i > 0 && i % 10 == 0)
        {
            putchar('\n');
            pad = "";
        }
        printf("%s%3d", pad, data[i]);
        pad = ",";
    }
    if (i % 10 != 0)
        putchar('\n');
    putchar('\n');
}

int main(void)
{
    // random -n 100 0 99 | commalist -B 8 -n 10 -W 2
    static int data[] =
    {
        22, 90, 87, 54, 81, 72, 68, 44, 82, 56,
        45, 66, 97, 69, 84,  7, 47, 27, 77, 11,
        99, 57, 95, 61, 90, 10, 98, 17, 29, 26,
         5, 39,  8, 61, 38, 90, 92, 85, 19, 39,
        76, 34, 97,  7, 23, 19, 27, 71,  8, 59,
        64, 25, 78, 28,  6, 65, 32, 47, 96,  3,
        55,  9, 75, 59,  5, 71, 83,  0, 95,  2,
        38, 61, 96, 94, 75, 40, 87, 75, 58, 49,
         4, 48, 58,  8, 99, 60, 91, 91, 46, 27,
        90, 85, 53, 60, 85, 46, 51, 33, 71, 92,
        13, 14, 60,  3, 94, 38,  2, 62, 33, 27,
        69, 33, 36, 66, 40, 63, 53, 34, 11,  4,
        56, 66, 86,  5, 95, 84, 69, 49, 49, 39,
        48, 91, 22, 35, 50, 64, 94, 35, 44, 97,
        70, 14, 28, 36, 68, 52, 69,  2, 54, 80,
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    N = 56;
    dump_array("Before", NUM_DATA, data);
    qsort(data, NUM_DATA, sizeof(data[0]), comparator);
    dump_array("After", NUM_DATA, data);
    return 0;
}
