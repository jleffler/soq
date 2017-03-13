/* Sort 3 items - flexible comparisons */
/* Based on code for SO 4203-5818 */
#include <assert.h>
#include <stdio.h>
#include "stderr.h"
#include <string.h>
#include <ctype.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static int pairs[3][2] = { { 0, 1 }, { 0, 2 }, { 1, 2 }, };

static void sort_3(int *a)
{
    for (int i = 0; i < 3; i++)
    {
        int p1 = pairs[i][0];
        int p2 = pairs[i][1];
        if (a[p1] > a[p2])
            swap(&a[p1], &a[p2]);
    }
}

#if 0
static int known[][3][2] =
{
    { { 0, 1 }, { 0, 2 }, { 1, 2 } },   /* Works */
    { { 0, 1 }, { 1, 2 }, { 0, 2 } },   /* Fails */
    { { 0, 2 }, { 0, 1 }, { 1, 2 } },   /* Works */
    { { 0, 2 }, { 1, 2 }, { 0, 1 } },   /* Works */
    { { 1, 2 }, { 0, 1 }, { 0, 2 } },   /* Fails */
    { { 1, 2 }, { 0, 2 }, { 0, 1 } },   /* Works */
    { { 0, 1 }, { 1, 2 }, { 0, 1 } },   /* Works */
    { { 1, 2 }, { 0, 1 }, { 1, 2 } },   /* Works */
};
#endif /* 0 */

static void print_3(int *a)
{
    const char *pad = "";
    for (int i = 0; i < 3; i++)
    {
        printf("%s%d", pad, a[i]);
        pad = " ";
    }
}

static void check_3(int *a)
{
    assert(a[0] <= a[1]);
    assert(a[1] <= a[2]);
}

/* Command-line argument processing - 1 argument */
static void convert_arg(int n, char *argn)
{
    int c0;
    int c1;
    if (strlen(argn) != 2 ||
        !isdigit(argn[0]) || !isdigit(argn[1]) ||
        (c0 = argn[0] - '0') > 2 || (c1 = argn[1] - '0') > 2 ||
        (c0 >= c1))
        err_error("Argument %d ('%s') is not a pair of non-decreasing distinct digits from the set 0, 1, 2\n",
                    n+1, argn);
    pairs[n][0] = c0;
    pairs[n][1] = c1;
}

/* Command-line argument processing - 3 arguments */
static void convert_3(char **args)
{
    for (int i = 0; i < 3; i++)
        convert_arg(i, args[i]);
}

static void print_variant(void)
{
    printf("Variant:");
    const char *pad = " ";
    for (int i = 0; i < 3; i++)
    {
        printf("%s%d%d", pad, pairs[i][0], pairs[i][1]);
        pad = ":";
    }
    putchar('\n');
    fflush(stdout);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc != 1 && argc != 4)
        err_usage("[ 01 02 12 ]");
    if (argc == 4)
        convert_3(&argv[1]);

    print_variant();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int a[3] = { i, j, k };
                print_3(a);
                fputs(" : ", stdout);
                sort_3(a);
                print_3(a);
                putchar('\n');
                check_3(a);
            }
        }
    }
    return 0;
}

