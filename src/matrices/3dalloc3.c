/* SO 1857-9583 Segmentation fault error in 3d array memory allocation */
/*
** It appears that 3dalloc2.c was known-to-be-buggy in the releasing of
** memory on allocation failure, and 3dalloc3.c contained the fix for
** the problem.  Careful testing of 3dalloc2.c showed the bug, and
** fixing produced essentially the same fix a second time.  Mildly
** exasperating that there was no annotation about this.  So, after some
** work, the files 3dalloc2.c and 3dalloc3.c are the same.
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
    *a = (int***)xmalloc(no1 * sizeof(int**));
    if (*a == 0)
        return 0;

    for (int l = 0; l < no1; l++)
    {
        if (((*a)[l]=(int**)xmalloc((no1+1)*sizeof(int*))) == 0)
        {
            for (int l1 = 0; l1 < l; l1++)
                xfree((*a)[l1]);
            xfree(*a);
            *a = 0;
            return 0;
        }
    }

    for (int l = 0; l < no1; l++)
    {
        for (int h = 0; h < no1; h++)
        {
            if (((*a)[l][h]=(int*)xmalloc(2*sizeof(int))) == 0)
            {
                /* Release prior items in current (partial) row */
                for (int h1 = 0; h1 < h; h1++)
                    xfree((*a)[l][h1]);
                /* Release items in prior (complete) rows */
                for (int l1 = 0; l1 < l; l1++)
                {
                    for (int h1 = 0; h1 < no1; h1++)
                        xfree((*a)[l1][h1]);
                }
                /* Release entries in first (complete) level of array */
                for (int l0 = 0; l0 < no1; l0++)
                    xfree((*a)[l0]);
                xfree(*a);
                *a = 0;
                return 0;
            }
        }
    }

    for (int l = 0; l < no1; l++)
        for (int h = 0; h < no1; h++)
            for (int k = 0; k < 2; k++)
                (*a)[l][h][k] = 10000 * l + 100 * h + k;

    return *a;
}

static void destroy_3d_array(int no1, int ***a)
{
    if (a != 0)
    {
        for (int l = 0; l < no1; l++)
        {
            for (int h = 0; h < no1; h++)
                xfree(a[l][h]);
            xfree(a[l]);
        }
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

    destroy_3d_array(no1, a);
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
