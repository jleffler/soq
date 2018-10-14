/* SO 5223-3288 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"
#include "stderr.h"
#include "aomptr.h"

static void print_prime_pairs(int lo, int hi);

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    if (argc != 3)
        err_usage("low high");

    int lo = strtol(argv[1], 0, 0);
    if (lo <= 1 || lo >= 1000)
        err_error("low value %s out of range 2..999\n", argv[1]);
    int hi = strtol(argv[2], 0, 0);
    if (hi <= 1 || hi >= 1000)
        err_error("high value %s out of range 2..999\n", argv[2]);
    if (lo == hi)
        err_error("the range %d..%d is not interesting\n", lo, lo);
    if (lo > hi)
        err_error("please make the low value less than the high value (%d, %d)!\n",
                  lo, hi);

    print_prime_pairs(lo, hi);
    return 0;
}

typedef struct Set
{
    size_t  size;
    int     data[];
} Set;

/* Creeate set from array - no check for duplicate values */
static Set *new_set(size_t size, int data[size])
{
    size_t space = sizeof(Set) + size * sizeof(data[0]);
    Set *ns = malloc(space);
    if (ns == 0)
        err_syserr("failed to allocate %zu bytes memory\n", space);
    ns->size = size;
    for (size_t i = 0; i < size; i++)
        ns->data[i] = data[i];
    return ns;
}

static AoM_Pointer *find_prime_pairs(int lo, int hi)
{
    AoM_Pointer *pp = aomp_create(hi - lo);

    for (int i = lo; i <= hi; i++)
    {
        for (int j = i + 1; j <= hi; j++)
        {
            if (gcd(i, j) == 1)
            {
                int n[2] = { i, j };
                Set *sp = new_set(2, n);
                aomp_add(pp, sizeof(*sp) + sp->size * sizeof(sp->data[0]), sp);
            }
        }
    }
    return pp;
}

static void set_release(const AoM_Block *blk)
{
    free(blk->blk_data);
}

static void aomp_free(AoM_Pointer *aom, AoM_SimpleApply p_free)
{
    aomp_apply(aom, 0, aomp_length(aom), p_free);
    aomp_destroy(aom);
}

static void print_set(const Set *sp)
{
    const char *pad = "{ ";
    for (size_t i = 0; i < sp->size; i++)
    {
        printf("%s%d", pad, sp->data[i]);
        pad = ", ";
    }
    printf(" }\n");
}

static void print_aomp(const AoM_Block *bp)
{
    print_set(bp->blk_data);
}

static void print_prime_pairs(int lo, int hi)
{
    AoM_Pointer *pp = find_prime_pairs(lo, hi);
    printf("Prime pairs: (%zu)\n", aomp_length(pp));
    aomp_apply(pp, 0, aomp_length(pp), print_aomp);
    aomp_free(pp, set_release);
}

