/*
@(#)File:           aomcopy.c
@(#)Purpose:        Array of Memory Blocks - Copy Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2023
@(#)Derivation:     aomcopy.c 1.4 2023/01/17 02:48:54
*/

/*TABSTOP=4*/

#include "aomcopy.h"         /* SSC: Self-sufficiency check */
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "imageprt.h"
#include "memdup.h"

struct AoM_Copy
{
    size_t     num_blk;
    size_t     max_blk;
    AoM_Block *blk_arr;
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

AoM_Copy *aomc_create(size_t num_ptrs)
{
    AoM_Copy *aom = malloc(sizeof(*aom));
    if (aom != 0)
    {
        aom->num_blk = 0;
        aom->max_blk = (num_ptrs < MIN_ALLOCATION) ? MIN_ALLOCATION : num_ptrs;
        aom->blk_arr = calloc(aom->max_blk, sizeof(aom->blk_arr[0]));
        if (aom->blk_arr == 0)
        {
            free(aom);
            aom = 0;
        }
    }
    return aom;
}

void aomc_destroy(AoM_Copy *aom)
{
    assert(aom != 0);
    if (aom->blk_arr != 0)
    {
        for (size_t i = 0; i < aom->num_blk; i++)
            free(aom->blk_arr[i].blk_data);
        free(aom->blk_arr);
    }
    aom->num_blk = 0;
    aom->max_blk = 0;
    aom->blk_arr = 0;
    free(aom);
}

bool aomc_add(AoM_Copy *aom, size_t blk_size, const void *blk_data)
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
    if ((aom->blk_arr[aom->num_blk].blk_data = memdup(blk_data, blk_size)) == 0)
        return false;
    aom->blk_arr[aom->num_blk].blk_size = blk_size;
    aom->num_blk++;
    return true;
}

bool aomc_set(AoM_Copy *aom, size_t index, size_t blk_size, const void *blk_data)
{
    assert(aom != 0);
    assert(blk_data != 0 && blk_size != 0);
    assert(aom->num_blk <= aom->max_blk - 1);
    if (index >= aom->num_blk)
        return false;
    void *copy = memdup(blk_data, blk_size);
    if (copy == 0)
        return false;
    free(aom->blk_arr[index].blk_data);
    aom->blk_arr[index].blk_data = copy;
    aom->blk_arr[index].blk_size = blk_size;
    return true;
}

AoM_Block *aomc_base(const AoM_Copy *aom)
{
    assert(aom != 0);
    return aom->blk_arr;
}

size_t aomc_length(const AoM_Copy *aom)
{
    assert(aom != 0);
    return aom->num_blk;
}

AoM_Block aomc_item_copy(const AoM_Copy *aom, size_t index)
{
    assert(aom != 0);
    if (index >= aom->num_blk)
        return (AoM_Block){ .blk_data = 0, .blk_size = 0 };
    AoM_Block *ptr = &aom->blk_arr[index];
    AoM_Block blk = { .blk_data = memdup(ptr->blk_data, ptr->blk_size), .blk_size = ptr->blk_size };
    return blk;
}

AoM_Block aomc_item(const AoM_Copy *aom, size_t index)
{
    assert(aom != 0);
    if (index >= aom->num_blk)
        return (AoM_Block){ .blk_data = 0, .blk_size = 0 };
    return aom->blk_arr[index];
}

void aomc_apply(const AoM_Copy *aom, size_t bos, size_t eos, AoM_SimpleApply function)
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

extern void aomc_apply_ctxt(const AoM_Copy *aom, size_t bos, size_t eos, AoM_ContextApply function, void *ctxt)
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

static void aomc_dump_block(FILE *fp, const AoM_Block *blk, void *context)
{
    assert(context == NULL);
    image_print_compressed(fp, 0, blk->blk_data, blk->blk_size);
}

static void aomc_dump_ctxt(const AoM_Block *blk, void *ctxt)
{
    AoM_Context *cp = ctxt;
    fprintf(cp->fp, "%zu\n", cp->index++);
    (*cp->printer)(cp->fp, blk, cp->u_context);
}

void aomc_dump(FILE *fp, const char *tag, const AoM_Copy *aom, AoM_PrintData printer, void *u_ctxt)
{
    if (printer == NULL)
    {
        printer = aomc_dump_block;
        u_ctxt = NULL;
    }
    AoM_Context s_ctxt = { fp, printer, u_ctxt, 0 };
    fprintf(fp, "%s (0x%12" PRIXPTR "):\n", tag, (uintptr_t)aom);
    fprintf(fp, " - Number %zu, Allocated %zu\n", aom->num_blk, aom->max_blk);
    aomc_apply_ctxt(aom, 0, aomc_length(aom), aomc_dump_ctxt, &s_ctxt);
}

void aomc_delete(AoM_Copy *aom, size_t bos, size_t eos)
{
    assert(aom != 0);
    assert(bos <= eos);
    assert(eos <= aom->num_blk);
    if (aom == 0 || bos > eos || eos > aom->num_blk)
        return;
    for (size_t i = bos; i < eos; i++)
        free(aom->blk_arr[i].blk_data);
    if (eos < aom->num_blk)
        memmove(&aom->blk_arr[bos], &aom->blk_arr[eos], (aom->num_blk - eos) * sizeof(aom->blk_arr[0]));
    aom->num_blk = bos + (aom->num_blk - eos);
}

#ifdef TEST

#undef NDEBUG
#include <unistd.h>
#include "stderr.h"

static const char optstr[] = "hV";
static const char usestr[] = "[-hV]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

static void aomc_applicator(const AoM_Block *ptr)
{
    image_print(stdout, 0, ptr->blk_data, ptr->blk_size);
}

static void aomc_applicator_ctxt(const AoM_Block *ptr, void *ctxt)
{
    int *ip = ctxt;
    printf("%d\n", ++*ip);
    image_print(stdout, 0, ptr->blk_data, ptr->blk_size);
}

static inline size_t min_size(size_t a, size_t b) { return (a < b) ? a : b; }

static int aomc_cmp(const void *v1, const void *v2)
{
    const AoM_Block *p1 = (const AoM_Block *)v1;
    const AoM_Block *p2 = (const AoM_Block *)v2;

    int rc = memcmp(p1->blk_data, p2->blk_data, min_size(p1->blk_size, p2->blk_size));
    if (rc != 0 || p1->blk_size == p2->blk_size)
        return rc;
    if (p1->blk_size < p2->blk_size)
        return -1;
    return +1;
}

typedef struct
{
    size_t  num_bytes;
} AoM_Test_Context;

static void print_bytes(FILE *fp, size_t offset, size_t nbytes, unsigned char *data)
{
    fprintf(fp, "0x%.4zX: ", offset);
    for (size_t i = 0; i < nbytes; i++)
        fprintf(fp, " 0x%.2X", data[i]);
    fputc('\n', fp);
}

static void aomc_print_minimal(FILE *fp, const AoM_Block *blk, void *context)
{
    //assert(context != NULL);
    AoM_Test_Context *cp = context;
    unsigned char *buffer = blk->blk_data;
    if (blk->blk_size <= 2 * cp->num_bytes)
    {
        /* Print all the data */
        print_bytes(fp, 0, blk->blk_size, buffer);
    }
    else
    {
        /* Print the first few bytes and the last few */
        print_bytes(fp, 0, cp->num_bytes, buffer);
        fputs("...\n", fp);
        buffer += blk->blk_size - cp->num_bytes;
        size_t offset = blk->blk_size - cp->num_bytes;
        print_bytes(fp, offset, cp->num_bytes, buffer);
    }
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
            err_version("AOMCOPY", &"@(#)$Revision: 1.4 $ ($Date: 2023/01/17 02:48:54 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    enum { BLK_SIZE = 16 };
    static const char names[][BLK_SIZE] =
    {
        "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon",
        "Nitrogen", "Oxygen", "Fluorine", "Neon",
    };
    enum { NUM_NAMES = sizeof(names) / sizeof(names[0]) };

    AoM_Copy *aom = aomc_create(0);
    assert(aom != 0);
    for (int i = 0; i < NUM_NAMES; i++)
        assert(aomc_add(aom, strlen(names[i]) + 1, names[i]));
    for (int i = optind; i < argc; i++)
        assert(aomc_add(aom, strlen(argv[i]) + 1, argv[i]));

    aomc_apply(aom, 0, 0, aomc_applicator);

    AoM_Block item1 = aomc_item_copy(aom, 3);
    assert(strcmp(item1.blk_data, names[3]) == 0);
    free(item1.blk_data);

    AoM_Block item2 = aomc_item(aom, 4);
    assert(strcmp(item2.blk_data, names[4]) == 0);
    aomc_add(aom, sizeof("Hydrogenation"), "Hydrogenation");
    aomc_add(aom, sizeof("Hydro-electric generation"), "Hydro-electric generation");
    aomc_add(aom, sizeof("Neonatal Clinic"), "Neonatal Clinic");
    aomc_add(aom, sizeof("Neon"), "Neon");
    aomc_add(aom, sizeof("Neo"), "Neo");

    assert(aomc_set(aom, 7, strlen(names[0]) + 1, names[0]));

    qsort(aomc_base(aom), aomc_length(aom), sizeof(AoM_Block), aomc_cmp);

    int index = 0;
    printf("Sorted data (skipping first two and last two):\n");
    aomc_apply_ctxt(aom, 2, aomc_length(aom) - 2, aomc_applicator_ctxt, &index);

    AoM_Block *base = aomc_base(aom);
    size_t len = aomc_length(aom);
    for (size_t i = 0; i < len; i++)
    {
        printf("aom[%zu] (%zu) = [%s]\n", i, base[i].blk_size, (char *)base[i].blk_data);
    }

    aomc_dump(stdout, "Before deleting", aom, NULL, NULL);
    aomc_delete(aom, 2, 5);
    enum { MIN_BYTES = 4 };
    AoM_Test_Context ctxt = { MIN_BYTES };
    aomc_dump(stdout, "After deleting", aom, aomc_print_minimal, &ctxt);

    aomc_destroy(aom);

    return 0;
}

#endif /* TEST */
