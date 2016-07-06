/* SO 18579583 Segmentation fault error in 3d array memory allocation */
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
    int ***d0 = (int***)xmalloc(no1 * sizeof(int**));
    int **d1 = (int **)xmalloc(no1 * no1 * sizeof(int *));
    int *d2 = (int *)xmalloc(no1 * no1  * 2 * sizeof(int));

    if (d0 == 0 || d1 == 0 || d2 == 0)
    {
        free(d0);
        free(d1);
        free(d2);
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
        free(a[0][0]);
        free(a[0]);
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
                        printf("Oops: a[%d][%d][%d] = %.6d%s", l, h, k, a[l][h][k], pad[k]);
                }
            }
        }
    }

    destroy_3d_array(a);
}

int main(int argc, char **argv)
{
    int no1 = 5;
    int fail_limit = 4;

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

