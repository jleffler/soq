/* SO 1857-9583 Segmentation fault error in 3d array memory allocation */
/*
** Closely related to 3dalloc2.c and 3dalloc3.c, but using far fewer
** memory allocations, which dramatically simplifies the error recovery.
*/
#include "posixver.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int fail_after = 0;
static int num_allocs = 0;
static int debug = 0;

static void xfree(void *vp)
{
    if (debug)
    {
        static int free_counter = 0;
        printf("free :%.2d: %p\n", ++free_counter, vp);
    }
    free(vp);
}

static void *xmalloc(size_t size)
{
    if (fail_after > 0 && num_allocs++ >= fail_after)
    {
        fputs("Out of memory\n", stdout);
        return 0;
    }
    void *vp = malloc(size);
    if (debug)
    {
        static int alloc_counter = 0;
        printf("alloc:%.2d: %p (%zu)\n", ++alloc_counter, vp, size);
    }
    return vp;
}

static int ***allocate_3d_array(int no1, int ****a)
{
    int ***d0 = (int***)xmalloc(no1 * sizeof(int**));
    int **d1 = (int **)xmalloc(no1 * no1 * sizeof(int *));
    int *d2 = (int *)xmalloc(no1 * no1  * 2 * sizeof(int));

    if (d0 == 0 || d1 == 0 || d2 == 0)
    {
        xfree(d0);
        xfree(d1);
        xfree(d2);
        *a = 0;
        return 0;
    }

    for (int l = 0; l < no1; l++)
    {
        d0[l] = &d1[l * no1];
        for (int h = 0; h < no1; h++)
        {
            d0[l][h] = &d2[(l * no1 + h) * 2];
            for (int k = 0; k < 2; k++)
                d0[l][h][k] = l * 10000 + h * 100 + k;
        }
    }

    *a = d0;
    return *a;
}

static void destroy_3d_array(int ***a)
{
    if (a != 0)
    {
        xfree(a[0][0]);
        xfree(a[0]);
        xfree(a);
    }
}

static void test_allocation(int no1)
{
    int ***a = 0;
    int ***b = allocate_3d_array(no1, &a);
    const char *pad[] = { "  ", "\n" };
    assert(b == a);

    if (a != 0)
    {
        for (int l = 0; l < no1; l++)
        {
            for (int h = 0; h < no1; h++)
            {
                for (int k = 0; k < 2; k++)
                {
                    if (a[l][h][k] != l * 10000 + h * 100 + k)
                        printf("Oops: a[%d][%d][%d] = %.6d%s", l, h, k, a[l][h][k], pad[k]);
                }
            }
        }
    }

    destroy_3d_array(a);
}

static const char helpstr[] =
    "  -d       Turn debug printing on\n"
    "  -h       Print this help message and exit\n"
    "  -n loop  Minimum number of failures (default 0)\n"
    "  -s size  Size of array to allocate (default 5)\n"
    "  -x loop  Maximum number of failures (default 33)\n"
    ;

int main(int argc, char **argv)
{
    int no1 = 5;
    int min = 0;
    int max = 33;
    int opt;

    while ((opt = getopt(argc, argv, "dhn:s:x:")) != -1)
    {
        switch (opt)
        {
        case 'd':
            debug = 1;
            break;
        case 'h':
            puts(helpstr);
            return EXIT_SUCCESS;
        case 'n':
            min = atoi(optarg);
            break;
        case 's':
            no1 = atoi(optarg);
            break;
        case 'x':
            max = atoi(optarg);
            break;
        default:
            return EXIT_FAILURE;
        }
    }

    for (fail_after = min; fail_after < max; fail_after++)
    {
        printf("Fail after: %d (size %d)\n", fail_after, no1);
        num_allocs = 0;
        test_allocation(no1);
    }

    return 0;
}

