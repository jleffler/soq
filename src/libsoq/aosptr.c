/*
@(#)File:           aosptr.c
@(#)Purpose:        Array of Strings - Pointer Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2023
@(#)Derivation:     aosptr.c 1.8 2023/01/10 06:24:27
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "aosptr.h"          /* SSC: Self-sufficiency check */
#include <assert.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

struct AoS_Pointer
{
    size_t  num_str;
    size_t  max_str;
    char  **strings;
};

typedef struct
{
    FILE   *fp;
    size_t  index;
} AoS_Context;

#ifndef AOS_MIN_ALLOCATION
#define AOS_MIN_ALLOCATION 4
#endif

enum { MIN_ALLOCATION = AOS_MIN_ALLOCATION };

AoS_Pointer *aosp_create(size_t num_ptrs)
{
    AoS_Pointer *aos = malloc(sizeof(*aos));
    if (aos != 0)
    {
        aos->num_str = 0;
        aos->max_str = (num_ptrs < MIN_ALLOCATION) ? MIN_ALLOCATION : num_ptrs;
        aos->strings = calloc(aos->max_str, sizeof(aos->strings[0]));
        if (aos->strings == 0)
        {
            free(aos);
            aos = 0;
        }
    }
    return aos;
}

void aosp_destroy(AoS_Pointer *aos)
{
    assert(aos != 0);
    if (aos->strings != 0)
        free(aos->strings);
    aos->num_str = 0;
    aos->max_str = 0;
    aos->strings = 0;
    free(aos);
}

bool aosp_add(AoS_Pointer *aos, char *str)
{
    assert(aos != 0);
    assert(str != 0);
    assert(aos->num_str <= aos->max_str - 1);
    if (aos->num_str == aos->max_str - 1)
    {
        size_t new_size = (aos->max_str + 2) * 2;
        char **space = realloc(aos->strings, new_size * sizeof(aos->strings[0]));
        if (space == 0)
            return false;
        aos->max_str = new_size;
        aos->strings = space;
        for (size_t i = aos->num_str; i < aos->max_str; i++)
            aos->strings[i] = 0;
    }
    aos->strings[aos->num_str++] = str;
    return true;
}

bool aosp_set(AoS_Pointer *aos, size_t index, char *str)
{
    assert(aos != 0);
    assert(str != 0);
    assert(aos->num_str <= aos->max_str - 1);
    if (index >= aos->num_str)
        return false;
    aos->strings[index] = str;
    return true;
}

char **aosp_base(const AoS_Pointer *aos)
{
    assert(aos != 0);
    return aos->strings;
}

size_t aosp_length(const AoS_Pointer *aos)
{
    assert(aos != 0);
    return aos->num_str;
}

char *aosp_item_copy(const AoS_Pointer *aos, size_t index)
{
    assert(aos != 0);
    if (index >= aos->num_str)
        return 0;
    return strdup(aos->strings[index]);
}

const char *aosp_item(const AoS_Pointer *aos, size_t index)
{
    assert(aos != 0);
    if (index >= aos->num_str)
        return 0;
    return aos->strings[index];
}

void aosp_delete(AoS_Pointer *aos, size_t bos, size_t eos)
{
    assert(aos != 0);
    assert(bos <= eos);
    assert(eos <= aos->num_str);
    if (aos == 0 || bos > eos || eos >= aos->num_str)
        return;
    if (eos < aos->num_str - 1)
        memmove(&aos->strings[bos], &aos->strings[eos], (aos->num_str - eos) * sizeof(aos->strings[0]));
    aos->num_str = bos + (aos->num_str - eos);
}

void aosp_apply(const AoS_Pointer *aos, size_t bos, size_t eos, AoS_SimpleApply function)
{
    assert(aos != 0);
    if (eos == 0)
        eos = aos->num_str;
    assert(bos <= eos && eos <= aos->num_str);
    if (eos > aos->num_str)
        eos = 0;
    for (size_t i = bos; i < eos; i++)
        (*function)(aos->strings[i]);
}

extern void aosp_apply_ctxt(const AoS_Pointer *aos, size_t bos, size_t eos, AoS_ContextApply function, void *ctxt)
{
    assert(aos != 0);
    if (eos == 0)
        eos = aos->num_str;
    assert(bos <= eos && eos <= aos->num_str);
    if (eos > aos->num_str)
        eos = 0;
    for (size_t i = bos; i < eos; i++)
        (*function)(aos->strings[i], ctxt);
}

static void aosp_dump_ctxt(const char *str, void *ctxt)
{
    AoS_Context *cp = ctxt;
    fprintf(cp->fp, "%zu [%s]\n", cp->index++, str);
}

void aosp_dump(FILE *fp, const char *tag, const AoS_Pointer *aos)
{
    AoS_Context ctxt = { fp, 0 };
    fprintf(fp, "%s (0x%12" PRIXPTR "):\n", tag, (uintptr_t)aos);
    fprintf(fp, " - Number %zu, Allocated %zu\n", aos->num_str, aos->max_str);
    aosp_apply_ctxt(aos, 0, aosp_length(aos), aosp_dump_ctxt, &ctxt);
}

#ifdef TEST

#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "stderr.h"

static const char optstr[] = "hV";
static const char usestr[] = "[-hV]";
static const char hlpstr[] =
    "  -h  Print this help message and exit\n"
    "  -V  Print version information and exit\n"
    ;

static void aosp_applicator(const char *str)
{
    printf("[%s]\n", str);
}

static void aosp_applicator_ctxt(const char *str, void *ctxt)
{
    int *ip = ctxt;
    printf("%d [%s]\n", ++*ip, str);
}

static int aosp_cmp(const void *v1, const void *v2)
{
    const char *p1 = *(char * const *)v1;
    const char *p2 = *(char * const *)v2;
    return strcmp(p1, p2);
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
            err_version("AOSPTR", &"@(#)$Revision: 1.8 $ ($Date: 2023/01/10 06:24:27 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    AoS_Pointer *aos = aosp_create(0);
    assert(aos != 0);
    static char names[][16] =
    {
        "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon",
        "Nitrogen", "Oxygen", "Fluorine", "Neon",
    };
    enum { NUM_NAMES = sizeof(names) / sizeof(names[0]) };
    for (int i = 0; i < NUM_NAMES; i++)
        assert(aosp_add(aos, names[i]));
    for (int i = optind; i < argc; i++)
        assert(aosp_add(aos, argv[i]));
    aosp_apply(aos, 0, 0, aosp_applicator);

    char *item1 = aosp_item_copy(aos, 3);
    const char *item2 = aosp_item(aos, 4);
    assert(strcmp(item1, names[3]) == 0);
    assert(strcmp(item2, names[4]) == 0);
    assert(aosp_set(aos, 3, names[0]));

    qsort(aosp_base(aos), aosp_length(aos), sizeof(char *), aosp_cmp);

    int index = 0;
    aosp_apply_ctxt(aos, 2, aosp_length(aos) - 2, aosp_applicator_ctxt, &index);

    char **base = aosp_base(aos);
    size_t len = aosp_length(aos);
    assert(base[len] == 0);
    for (size_t i = 0; i < len; i++)
    {
        printf("aos[%zu] = [%s]\n", i, base[i]);
    }

    aosp_dump(stdout, "Before deleting [0..4)", aos);
    aosp_delete(aos, 0, 4);
    aosp_dump(stdout, "After deleting [0..4)", aos);

    free(item1);
    aosp_destroy(aos);

    return 0;
}

#endif /* TEST */
