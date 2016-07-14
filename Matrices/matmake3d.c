/* SO 18579583 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int fail_after = 0;
static int num_allocs = 0;

static void *xmalloc(size_t size)
{
    if (fail_after > 0 && num_allocs++ >= fail_after)
    {
        fputs("Out of memory\n", stdout);
        return 0;
    }
    return malloc(size);
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
                free((*a)[l1]);
            free(*a);
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
                    free((*a)[l][h1]);
                /* Release items in prior (complete) rows */
                for (int l1 = 0; l1 < l; l1++)
                {
                    for (int h1 = 0; h1 < no1; h1++)
                        free((*a)[l1][h1]);
                }
                /* Release entries in first (complete) level of array */
                for (int l1 = 0; l1 < no1; l1++)
                    free((*a)[l1]);
                free(*a);
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
                free(a[l][h]);
            free(a[l]);
        }
        free(a);
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
                        printf("a[%d][%d][%d] = %.6d%s", l, h, k, a[l][h][k], pad[k]);
                }
            }
        }
    }

    destroy_3d_array(no1, a);
}

int main(int argc, char **argv)
{
    int no1 = 5;
    int fail_limit = 33;

    if (argc == 2)
        fail_limit = atoi(argv[1]);

    for (fail_after = 0; fail_after < fail_limit; fail_after++)
    {
        printf("Fail after: %d\n", fail_after);
        num_allocs = 0;
        test_allocation(no1);
    }

    return 0;
}
