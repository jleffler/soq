/* SO 5223-3288 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"
#include "stderr.h"
#include "aomptr.h"

/*
** Once you have a list of prime pairs between the two end points, you
** can start trying to combine pairs with exactly one element in common
** to see if they form a triple.  Once you have a list of triples, you
** can try to combine the triples with pairs that have exactly one
** element in common with the triple to form quadruples; and you can
** keep going until there are no N-tuples created by matching
** (N-1)-tuples with pairs.  Using a scheme like this, you'll need a
** variable length type to record N-tuples (from pairs upwards), rather
** than a specific type for pairs and another for triples and another
** for quadruples, etc
*/

static void print_prime_sets(int lo, int hi);

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

    print_prime_sets(lo, hi);
    return 0;
}

typedef struct Set
{
    size_t  size;
    int     data[];
} Set;

static inline size_t set_memsize(const Set *sp)
{
    return sizeof(*sp) + sp->size * sizeof(sp->data[0]);
}

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

/* Copy set and add extra value - no check for duplicate values */
static Set *copy_extend_set(const Set *op, int value)
{
    size_t space = sizeof(Set) + (op->size + 1) * sizeof(op->data[0]);
    Set *ns = malloc(space);
    if (ns == 0)
        err_syserr("failed to allocate %zu bytes memory\n", space);
    ns->size = op->size + 1;
    for (size_t i = 0; i < op->size; i++)
        ns->data[i] = op->data[i];
    ns->data[op->size] = value;
    return ns;
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

/* Do the two sets have exactly one element in common? */
static bool one_element_in_common(Set *sp1, Set *sp2)
{
    int count = 0;
    for (size_t i = 0; i < sp1->size; i++)
    {
        for (size_t j = 0; j < sp2->size; j++)
        {
            if (sp1->data[i] == sp2->data[j])
                count++;
        }
    }
    return (count == 1);
}

/* Find a (the) unique element in set sp2 not in sp1 */
static int unique_element_set2(Set *sp1, Set *sp2)
{
    assert(one_element_in_common(sp1, sp2));
    for (size_t i = 0; i < sp2->size; i++)
    {
        bool unmatched = true;
        for (size_t j = 0; j < sp1->size; j++)
        {
            if (sp1->data[j] == sp2->data[i])
            {
                unmatched = false;
                break;
            }
        }
        if (unmatched)
            return sp2->data[i];
    }
    assert(0);
    return -1;
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
                aomp_add(pp, set_memsize(sp), sp);
            }
        }
    }
    return pp;
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

/* Check whether value is mutually prime with each elements of a set */
static bool mutually_prime(const Set *sp, int val)
{
    for (size_t j = 0; j < sp->size; j++)
    {
        if (gcd(val, sp->data[j]) != 1)
            return false;
    }
    return true;
}

typedef struct Context
{
    AoM_Pointer *pairs;
    AoM_Pointer *ntuples;
} Context;

static void find_prime_tuples(const AoM_Block *bp, void *cp)
{
    AoM_Pointer *pairs = ((Context *)cp)->pairs;
    AoM_Pointer *ntuples = ((Context *)cp)->ntuples;
    Set *sp = bp->blk_data;
    size_t num_pairs = aomp_length(pairs);
    for (size_t i = 0; i < num_pairs; i++)
    {
        AoM_Block blk = aomp_item(pairs, i);
        Set *pp = blk.blk_data;
        if (one_element_in_common(sp, pp))
        {
            int v = unique_element_set2(sp, pp);
            if (mutually_prime(sp, v))
            {
                Set *np = copy_extend_set(sp, v);
                aomp_add(ntuples, set_memsize(np), np);
            }
        }
    }
}

static void print_prime_sets(int lo, int hi)
{
    AoM_Pointer *pp = find_prime_pairs(lo, hi);
    printf("Prime pairs: (%zu)\n", aomp_length(pp));
    aomp_apply(pp, 0, aomp_length(pp), print_aomp);

    AoM_Pointer *otuple = pp;
    size_t tuple_size = 3;
    while (aomp_length(otuple) > 0)
    {
        AoM_Pointer *ntuple = aomp_create(hi - lo);
        Context ctxt = { pp, ntuple };
        aomp_apply_ctxt(otuple, 0, aomp_length(otuple), find_prime_tuples, &ctxt);
        printf("Prime %zu-tuples: (%zu)\n", tuple_size++, aomp_length(ntuple));
        aomp_apply(ntuple, 0, aomp_length(ntuple), print_aomp);
        if (otuple != pp)
            aomp_free(otuple, set_release);
        otuple = ntuple;
    }

    if (otuple != pp)
        aomp_free(otuple, set_release);
    aomp_free(pp, set_release);
}

