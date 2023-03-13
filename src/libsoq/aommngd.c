/*
@(#)File:           aommngd.c
@(#)Purpose:        Array of Memory Blocks - Memory Managed Data
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018-2023
@(#)Derivation:     aommngd.c 1.5 2023/01/17 03:17:51
*/

/*TABSTOP=4*/

#include "aommngd.h"         /* SSC: Self-sufficiency check */
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "imageprt.h"
#include "memdup.h"

struct AoM_Managed
{
    size_t         num_blk;
    size_t         max_blk;
    AoM_Block     *blk_arr;
    AoM_BlkCopy    blk_cpy;
    AoM_BlkFree    blk_rel;
};

typedef struct
{
    FILE          *fp;
    AoM_PrintData  printer;
    void          *u_context;
    size_t         index;
} AoM_Context;

#ifndef AOM_MIN_ALLOCATION
#define AOM_MIN_ALLOCATION 4
#endif

enum { MIN_ALLOCATION = AOM_MIN_ALLOCATION };

AoM_Managed *aomm_create(size_t num_ptrs, AoM_BlkCopy copier, AoM_BlkFree release)
{
    assert(copier != 0 && release != 0);
    AoM_Managed *aom = malloc(sizeof(*aom));
    if (aom != 0)
    {
        aom->num_blk = 0;
        aom->max_blk = (num_ptrs < MIN_ALLOCATION) ? MIN_ALLOCATION : num_ptrs;
        aom->blk_arr = calloc(aom->max_blk, sizeof(aom->blk_arr[0]));
        aom->blk_cpy = copier;
        aom->blk_rel = release;
        if (aom->blk_arr == 0)
        {
            free(aom);
            aom = 0;
        }
    }
    return aom;
}

void aomm_destroy(AoM_Managed *aom)
{
    assert(aom != 0);
    if (aom->blk_arr != 0)
    {
        for (size_t i = 0; i < aom->num_blk; i++)
            (*aom->blk_rel)(aom->blk_arr[i].blk_size, aom->blk_arr[i].blk_data);
        free(aom->blk_arr);
    }
    /* Maximize the probability that a dangling pointer blows up */
    /* A modern optimizer may optimize these assignments away */
    aom->num_blk = 0;
    aom->max_blk = 0;
    aom->blk_arr = 0;
    aom->blk_cpy = 0;
    aom->blk_rel = 0;
    free(aom);
}

bool aomm_add(AoM_Managed *aom, size_t blk_size, const void *blk_data)
{
    assert(aom != 0);
    assert(blk_data != 0 && blk_size != 0);
    assert(aom->num_blk <= aom->max_blk - 1);
    if (aom->num_blk == aom->max_blk - 1)
    {
        size_t new_size = (aom->max_blk + 2) * 2;
        AoM_Block *space = realloc(aom->blk_arr, new_size * sizeof(aom->blk_arr[0]));
        if (space == 0)
            return false;
        aom->max_blk = new_size;
        aom->blk_arr = space;
        for (size_t i = aom->num_blk; i < aom->max_blk; i++)
            aom->blk_arr[i] = (AoM_Block){ .blk_data = 0, .blk_size = 0 };
    }
    aom->blk_arr[aom->num_blk] = (*aom->blk_cpy)(blk_size, blk_data);
    if (aom->blk_arr[aom->num_blk].blk_data == 0)
        return false;
    aom->num_blk++;
    return true;
}

bool aomm_set(AoM_Managed *aom, size_t index, size_t blk_size, const void *blk_data)
{
    assert(aom != 0);
    assert(blk_data != 0 && blk_size != 0);
    assert(aom->num_blk <= aom->max_blk - 1);
    if (index >= aom->num_blk)
        return false;
    AoM_Block blk = (*aom->blk_cpy)(blk_size, blk_data);
    if (blk.blk_data == 0)
        return false;
    (*aom->blk_rel)(aom->blk_arr[index].blk_size, aom->blk_arr[index].blk_data);
    aom->blk_arr[index] = blk;
    return true;
}

AoM_Block *aomm_base(const AoM_Managed *aom)
{
    assert(aom != 0);
    return aom->blk_arr;
}

size_t aomm_length(const AoM_Managed *aom)
{
    assert(aom != 0);
    return aom->num_blk;
}

AoM_Block aomm_item_copy(const AoM_Managed *aom, size_t index)
{
    assert(aom != 0);
    if (index >= aom->num_blk)
        return (AoM_Block){ .blk_data = 0, .blk_size = 0 };
    AoM_Block *ptr = &aom->blk_arr[index];
    AoM_Block blk = (*aom->blk_cpy)(ptr->blk_size, ptr->blk_data);
    return blk;
}

AoM_Block aomm_item(const AoM_Managed *aom, size_t index)
{
    assert(aom != 0);
    if (index >= aom->num_blk)
        return (AoM_Block){ .blk_data = 0, .blk_size = 0 };
    return aom->blk_arr[index];
}

void aomm_apply(const AoM_Managed *aom, size_t bos, size_t eos, AoM_SimpleApply function)
{
    assert(aom != 0);
    if (eos == 0)
        eos = aom->num_blk;
    assert(bos <= eos && eos <= aom->num_blk);
    if (eos > aom->num_blk)
        eos = 0;
    for (size_t i = bos; i < eos; i++)
        (*function)(&aom->blk_arr[i]);
}

extern void aomm_apply_ctxt(const AoM_Managed *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt)
{
    assert(aom != 0);
    if (eos == 0)
        eos = aom->num_blk;
    assert(bos <= eos && eos <= aom->num_blk);
    if (eos > aom->num_blk)
        eos = 0;
    for (size_t i = bos; i < eos; i++)
        (*function)(&aom->blk_arr[i], ctxt);
}

static void aomm_dump_block(FILE *fp, const AoM_Block *blk, void *context)
{
    assert(context == NULL);
    image_print_compressed(fp, 0, blk->blk_data, blk->blk_size);
}

static void aomm_dump_ctxt(const AoM_Block *blk, void *ctxt)
{
    AoM_Context *cp = ctxt;
    fprintf(cp->fp, "%zu\n", cp->index++);
    (*cp->printer)(cp->fp, blk, cp->u_context);
}

void aomm_dump(FILE *fp, const char *tag, const AoM_Managed *aom, AoM_PrintData printer, void *u_ctxt)
{
    if (printer == NULL)
    {
        printer = aomm_dump_block;
        u_ctxt = NULL;
    }
    AoM_Context s_ctxt = { fp, printer, u_ctxt, 0 };
    fprintf(fp, "%s (0x%12" PRIXPTR "):\n", tag, (uintptr_t)aom);
    fprintf(fp, " - Number %zu, Allocated %zu\n", aom->num_blk, aom->max_blk);
    aomm_apply_ctxt(aom, 0, aomm_length(aom), aomm_dump_ctxt, &s_ctxt);
}

void aomm_delete(AoM_Managed *aom, size_t bos, size_t eos)
{
    assert(aom != 0);
    assert(bos <= eos);
    assert(eos <= aom->num_blk);
    if (aom == 0 || bos > eos || eos > aom->num_blk)
        return;
    for (size_t i = bos; i < eos; i++)
    {
        (*aom->blk_rel)(aom->blk_arr[i].blk_size, aom->blk_arr[i].blk_data);
        /* Zeroing the memory is not strictly necessary */
        memset(&aom->blk_arr[i], '\0', sizeof(aom->blk_arr[i]));
    }
    if (eos < aom->num_blk)
        memmove(&aom->blk_arr[bos], &aom->blk_arr[eos], (aom->num_blk - eos) * sizeof(aom->blk_arr[0]));
    aom->num_blk = bos + (aom->num_blk - eos);
}

#ifdef TEST

#undef NDEBUG
#include <unistd.h>
#include "stderr.h"

struct NoneSuch
{
    int   number;
    char *name;
    char *value;
};

static const char optstr[] = "hV";
static const char usestr[] = "[-hV]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

static AoM_Block aomm_blk_copy(size_t blk_size, const void *blk_data)
{
    AoM_Block blk = { 0, 0 };
    assert(blk_size == sizeof(struct NoneSuch));
    const struct NoneSuch *op = blk_data;
    struct NoneSuch *np = malloc(sizeof(*np));
    if (np != 0)
    {
        np->number = op->number;
        np->name = strdup(op->name);
        np->value = strdup(op->value);
        if (np->name == 0 || np->value == 0)
        {
            free(np->name);
            free(np->value);
            free(np);
        }
        else
        {
            blk.blk_size = blk_size;
            blk.blk_data = np;
        }
    }
    return blk;
}

static void aomm_blk_free(size_t blk_size, void *blk_data)
{
    struct NoneSuch *np = blk_data;
    assert(blk_size == sizeof(struct NoneSuch));
    if (np != 0)
    {
        free(np->name);
        free(np->value);
        free(np);
    }
}

static void aomm_applicator(const AoM_Block *ptr)
{
    struct NoneSuch *np = ptr->blk_data;
    printf("(%p) %d: '%s' = '%s'\n", (void *)np, np->number, np->name, np->value);
}

static void aomm_applicator_ctxt(const AoM_Block *ptr, void *ctxt)
{
    int *ip = ctxt;
    printf("%d - (%zu) ", ++*ip, ptr->blk_size);
    struct NoneSuch *np = ptr->blk_data;
    printf("(%p) %d: '%s' = '%s'\n", (void *)np, np->number, np->name, np->value);
}

static inline size_t min_size(size_t a, size_t b) { return (a < b) ? a : b; }

/* Compare name as strings, then value, then number */
static int aomm_cmp(const void *v1, const void *v2)
{
    const AoM_Block *p1 = (const AoM_Block *)v1;
    const AoM_Block *p2 = (const AoM_Block *)v2;
    const struct NoneSuch *b1 = p1->blk_data;
    const struct NoneSuch *b2 = p2->blk_data;

    int rc = strcmp(b1->name, b2->name);
    if (rc != 0)
        return rc;
    rc = strcmp(b1->value, b2->value);
    if (rc != 0)
        return rc;
    return (b1->number > b2->number) - (b1->number < b2->number);
}

typedef struct
{
    size_t  num_bytes;
} AoM_Test_Context;

static void print_bytes(FILE *fp, size_t offset, size_t nbytes, void *vp)
{
    unsigned char *data = vp;
    fprintf(fp, "0x%.4zX: ", offset);
    for (size_t i = 0; i < nbytes; i++)
        fprintf(fp, " 0x%.2X", data[i]);
    fputc('\n', fp);
}

static void aomm_print_minimal(FILE *fp, const AoM_Block *blk, void *context)
{
    assert(context != NULL);
    AoM_Test_Context *cp = context;
    assert(cp->num_bytes == sizeof(struct NoneSuch));
    struct NoneSuch *data = blk->blk_data;
    print_bytes(fp, offsetof(struct NoneSuch, number), sizeof(data->number), &data->number);
    print_bytes(fp, offsetof(struct NoneSuch, name),   sizeof(data->name),   data->name);
    print_bytes(fp, offsetof(struct NoneSuch, value),  sizeof(data->value),  data->value);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'V':
            err_version("AOMCOPY", &"@(#)$Revision: 1.5 $ ($Date: 2023/01/17 03:17:51 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    enum { BLK_SIZE = 16 };
    static char strings[][10] =
    {
        "H",  "Hydrogen",
        "He", "Helium",
        "Li", "Lithium",
        "Be", "Beryllium",
        "B",  "Boron",
        "C",  "Carbon",
        "N",  "Nitrogen",
        "O",  "Oxygen",
        "Fl", "Fluorine",
        "Ne", "Neon",
    };
    static struct NoneSuch names[] =
    {
        {  1, strings[ 0], strings[ 1], },
        {  2, strings[ 2], strings[ 3], },
        {  3, strings[ 4], strings[ 5], },
        {  4, strings[ 6], strings[ 7], },
        {  5, strings[ 8], strings[ 9], },
        {  6, strings[10], strings[11], },
        {  7, strings[12], strings[13], },
        {  8, strings[14], strings[15], },
        {  9, strings[16], strings[17], },
        { 10, strings[18], strings[19], },
    };
    enum { NUM_NAMES = sizeof(names) / sizeof(names[0]) };

    AoM_Managed *aom = aomm_create(4, aomm_blk_copy, aomm_blk_free);
    assert(aom != 0);
    for (int i = 0; i < NUM_NAMES; i++)
        assert(aomm_add(aom, sizeof(names[i]), &names[i]));

    aomm_apply(aom, 0, 0, aomm_applicator);

    AoM_Block item1 = aomm_item_copy(aom, 3);
    struct NoneSuch *np = item1.blk_data;
    assert(strcmp(np->name, names[3].name) == 0);
    assert(strcmp(np->value, names[3].value) == 0);
    aomm_blk_free(item1.blk_size, item1.blk_data);

    AoM_Block item2 = aomm_item(aom, 4);
    np = item2.blk_data;
    assert(strcmp(np->name, names[4].name) == 0);
    assert(strcmp(np->value, names[4].value) == 0);

    aomm_add(aom, sizeof(struct NoneSuch),
             &(struct NoneSuch){ sizeof("Hydrogenation"), (char []){ "Hy" }, (char []){ "Hydrogenation"} });

    qsort(aomm_base(aom), aomm_length(aom), sizeof(AoM_Block), aomm_cmp);

    int index = 0;
    printf("Sorted data (skipping first two and last two):\n");
    aomm_apply_ctxt(aom, 2, aomm_length(aom) - 2, aomm_applicator_ctxt, &index);

    AoM_Block *base = aomm_base(aom);
    size_t len = aomm_length(aom);
    for (size_t i = 0; i < len; i++)
    {
        np = base[i].blk_data;
        printf("aom[%zu] (%zu) %p = [%d] [%s] [%s]\n", i, base[i].blk_size,
               base[i].blk_data, np->number, np->name, np->value);
    }

    aomm_dump(stdout, "Before deleting", aom, NULL, NULL);
    aomm_delete(aom, 2, 5);
    AoM_Test_Context ctxt = { sizeof(struct NoneSuch) };
    aomm_dump(stdout, "After deleting", aom, aomm_print_minimal, &ctxt);

    aomm_destroy(aom);

    return 0;
}

#endif /* TEST */
