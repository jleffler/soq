/*
@(#)File:           aoscopy.c
@(#)Purpose:        Array of Strings - Copy Semantics
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2017-2018
@(#)Derivation:     aoscopy.c 1.7 2018/06/05 06:37:54
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "aoscopy.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct AoS_Copy
{
    size_t  num_str;
    size_t  max_str;
    char  **strings;
};

#ifndef AOS_MIN_ALLOCATION
#define AOS_MIN_ALLOCATION 4
#endif

enum { MIN_ALLOCATION = AOS_MIN_ALLOCATION };

AoS_Copy *aosc_create(size_t num_ptrs)
{
    AoS_Copy *aos = malloc(sizeof(*aos));
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

void aosc_destroy(AoS_Copy *aos)
{
    assert(aos != 0);
    if (aos->strings != 0)
    {
        for (size_t i = 0; i < aos->num_str; i++)
            free(aos->strings[i]);
        free(aos->strings);
    }
    aos->num_str = 0;
    aos->max_str = 0;
    aos->strings = 0;
    free(aos);
}

static inline size_t max_size(size_t a, size_t b) { return (a > b) ? a : b; }

static bool aosc_expand(AoS_Copy *aos, size_t extra)
{
    assert(aos->num_str <= aos->max_str - 1);
    if (aos->num_str + extra >= aos->max_str - 1)
    {
        size_t new_size = max_size((aos->max_str + 2) * 2, aos->num_str + extra + 2);
        char **space = realloc(aos->strings, new_size * sizeof(aos->strings[0]));
        if (space == 0)
            return false;
        aos->max_str = new_size;
        aos->strings = space;
        for (size_t i = aos->num_str; i < aos->max_str; i++)
            aos->strings[i] = 0;
    }
    return true;
}

/*
** Duplicate bytes (not necessarily a string) starting at str, with eos
** one byte beyond the end.  Ensure that the result is null-terminated.
*/
static char *dup_bytes(const char *str, const char *eos)
{
    assert(eos >= str);
    size_t len = eos - str;
    char *result = malloc(len + 1);
    if (result != 0)
    {
        memmove(result, str, len);
        result[len] = '\0';
    }
    return result;
}

bool aosc_addbytes(AoS_Copy *aos, const char *str, const char *eos)
{
    assert(aos != 0);
    assert(str != 0);
    assert(aos->num_str <= aos->max_str - 1);
    if (!aosc_expand(aos, 1))
        return false;
    if ((aos->strings[aos->num_str] = dup_bytes(str, eos)) == 0)
        return false;
    aos->num_str++;
    return true;
}

bool aosc_add(AoS_Copy *aos, const char *str)
{
    assert(aos != 0);
    assert(str != 0);
    assert(aos->num_str <= aos->max_str - 1);
    if (!aosc_expand(aos, 1))
        return false;
    if ((aos->strings[aos->num_str] = strdup(str)) == 0)
        return false;
    aos->num_str++;
    return true;
}

bool aosc_set(AoS_Copy *aos, size_t index, const char *str)
{
    assert(aos != 0);
    assert(str != 0);
    assert(aos->num_str <= aos->max_str - 1);
    if (index >= aos->num_str)
        return false;
    char *copy = strdup(str);
    if (copy == 0)
        return false;
    free(aos->strings[index]);
    aos->strings[index] = copy;
    return true;
}

char **aosc_base(AoS_Copy *aos)
{
    assert(aos != 0);
    return aos->strings;
}

size_t aosc_length(AoS_Copy *aos)
{
    assert(aos != 0);
    return aos->num_str;
}

char *aosc_item_copy(AoS_Copy *aos, size_t index)
{
    assert(aos != 0);
    if (index >= aos->num_str)
        return 0;
    return strdup(aos->strings[index]);
}

const char *aosc_item(AoS_Copy *aos, size_t index)
{
    assert(aos != 0);
    if (index >= aos->num_str)
        return 0;
    return aos->strings[index];
}

void aosc_apply(AoS_Copy *aos, size_t bos, size_t eos, AoS_SimpleApply function)
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

extern void aosc_apply_ctxt(AoS_Copy *aos, size_t bos, size_t eos, AoS_ContextApply function, void *ctxt)
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

static void aosc_applicator(const char *str)
{
    printf("[%s]\n", str);
}

static void aosc_applicator_ctxt(const char *str, void *ctxt)
{
    int *ip = ctxt;
    printf("%d [%s]\n", ++*ip, str);
}

static int aosc_cmp(const void *v1, const void *v2)
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
            err_version("AOSCOPY", &"@(#)$Revision: 1.7 $ ($Date: 2018/06/05 06:37:54 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    AoS_Copy *aos = aosc_create(0);
    assert(aos != 0);
    static const char *names[] =
    {
        "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon",
        "Nitrogen", "Oxygen", "Fluorine", "Neon",
    };
    enum { NUM_NAMES = sizeof(names) / sizeof(names[0]) };
    for (int i = 0; i < NUM_NAMES; i++)
        assert(aosc_add(aos, names[i]));
    for (int i = optind; i < argc; i++)
        assert(aosc_add(aos, argv[i]));
    aosc_addbytes(aos, names[3], &names[3][5]);
    aosc_apply(aos, 0, 0, aosc_applicator);

    char *item1 = aosc_item_copy(aos, 3);
    const char *item2 = aosc_item(aos, 4);
    assert(strcmp(item1, names[3]) == 0);
    assert(strcmp(item2, names[4]) == 0);
    assert(aosc_set(aos, 7, names[0]));

    qsort(aosc_base(aos), aosc_length(aos), sizeof(char *), aosc_cmp);

    int index = 0;
    aosc_apply_ctxt(aos, 2, aosc_length(aos) - 2, aosc_applicator_ctxt, &index);

    char **base = aosc_base(aos);
    size_t len = aosc_length(aos);
    assert(base[len] == 0);
    for (size_t i = 0; i < len; i++)
    {
        printf("aos[%zu] = [%s]\n", i, base[i]);
    }

    free(item1);
    aosc_destroy(aos);

    return 0;
}

#endif /* TEST */
