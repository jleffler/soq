/*
** Attempt to code up multi-dimensional array handling in C.
**
** Not specifically in response to any question.  Created prior to
** 2013-04-16.  Code crashes — which is not what's supposed to happen.
** In theory, it might even handle more than 3 dimensions; it crashes on
** 3 at the moment.
*/

#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alignment
{
    char      c;
    union Strictest
    {
        long double ld;
        double      d;
        void       *vp;
        void      (*fp)(void);
        long long   ll;
        uintmax_t   mi;
    } u;
};

enum { ALIGNMENT = offsetof(struct Alignment, u.mi) };
enum { MAX_DIMS = 7 };

typedef struct Dimension
{
    size_t  number;
    size_t  size;
} Dimension;

typedef struct Array
{
    void      *base;
    size_t     ndims;
    Dimension  dim[];   /* Flexible array member */
} Array;

static void dump_array_info(FILE *fp, const char *tag, const Array *a)
{
    fprintf(fp, "Array Info: %s\n", tag);
    fprintf(fp, "Base Address: 0x%08" PRIXPTR "\n", (uintptr_t)a->base);
    fprintf(fp, "Dimensions: %zu\n", a->ndims);
    for (size_t i = 0; i < a->ndims; i++)
        fprintf(fp, "Dimension %zu: size %2zu number %zu\n", i, a->dim[i].size, a->dim[i].number);
}

static void dump_array_info_pointers(FILE *fp, const char *tag, const char *name, const Array *a)
{
    dump_array_info(fp, tag, a);
    fprintf(fp, "  %s: Address: 0x%08" PRIXPTR "\n", name, (uintptr_t)a->base);
}

static Array *make_array(size_t elem_size, size_t ndims, ...)
{
    if (ndims == 0 || ndims > MAX_DIMS)
        return(0);
    Array *a = (Array *)malloc(sizeof(*a) + ndims * sizeof(Dimension)); /*=C++=*/
    if (a == 0)
        return(0);

    va_list args;
    va_start(args, ndims);
    for (size_t i = 0; i < ndims; i++)
    {
        a->dim[i].number = va_arg(args, size_t);
        a->dim[i].size   = sizeof(void *);
    }
    va_end(args);
    a->dim[ndims-1].size = elem_size;
    a->ndims = ndims;
    a->base = 0;

    /* Total space needed
    ** For a concrete example: ndims == 3
    **
    ** nbytes[0] = a->dim[0].size * (a->dim[0].number)
    ** nbytes[1] = a->dim[1].size * (a->dim[0].number * a->dim[1].number)
    ** nbytes[2] = a->dim[2].size * (a->dim[0].number * a->dim[1].number * a->dim[2].number)
    */
    size_t nbytes[MAX_DIMS] = { 0 };
    size_t tbytes = 0;
    size_t product = 1;
    for (size_t i = 0; i < ndims; i++)
    {
        product   *= a->dim[i].number;
        nbytes[i]  = a->dim[i].size * product;
        tbytes    += nbytes[i];
    }

    /* Debugging dump */
    dump_array_info(stdout, "Space determination", a);
    for (size_t i = 0; i < ndims; i++)
        printf("Space[%zu] = %zu\n", i, nbytes[i]);
    printf("Total space = %zu\n", tbytes);

    /* Over-allocation by up to ALIGNMENT bytes */
    void *space = calloc(tbytes + ALIGNMENT, sizeof(char));
    if (space == 0)
    {
        free(a);
        return(0);
    }
    a->base = space;

    /*
    ** Memory layout for 3D [3][4][5] array of char.  'a->' prefix assumed for 'dim'.
    **
    ** Assuming 8-byte addresses.  Base = 0x1000.
    **
    **  Base points to &a[0]
    **  Start1 = Base + dim[0].size * dim[0].number; OK (0x1000 + 8 * 3 = 0x1018)
    **  Incr1  = dim[1].size * dim[1].number;        OK (8 * 4)
    **  +------+------+------+
    **  | a[0] | a[1] | a[2] |  [0x1000,0x1018)
    **  +------+------+------+
    **  a[0] = 0x1018    &a[0] = 0x1000
    **  a[1] = 0x1038    &a[1] = 0x1008
    **  a[2] = 0x1058    &a[2] = 0x1010
    **  a[n] = Start + n * Incr
    **
    **  a[0] points to &a[0][0]
    **  a[1] points to &a[1][0]
    **  a[2] points to &a[2][0]
    **  +---------+---------+---------+---------+
    **  | a[0][0] | a[0][1] | a[0][2] | a[0][3] | [0x1018,0x1038)
    **  +---------+---------+---------+---------+
    **  | a[1][0] | a[1][1] | a[1][2] | a[1][3] | [0x1038,0x1058)
    **  +---------+---------+---------+---------+
    **  | a[2][0] | a[2][1] | a[2][2] | a[2][3] | [0x1058,0x1078)
    **  +---------+---------+---------+---------+
    **  Start2 = Base + dim[0].size * dim[0].number + dim[1].size * dim[0].number * dim[1].number
    **  Start2 = 0x1000 + 8 * 3 + 8 * 3 * 4 = 0x1000 + 24 + 96 = 0x1078
    **  Start2 = Start1 + dim[1] * dim[0] * dim[1].size
    **  Incr2  = dim[2].size * dim[2].number = 1 * 5 = 5.
    **
    **  a[0][0] points to &a[0][0][0]
    **  a[0][1] points to &a[0][1][0]
    **  a[0][2] points to &a[0][2][0]
    **  a[0][3] points to &a[0][3][0]
    **  a[1][0] points to &a[1][0][0]
    **  a[1][1] points to &a[1][1][0]
    **  Etc...
    **  +------------+------------+------------+------------+------------+
    **  | a[0][0][0] | a[0][0][1] | a[0][0][2] | a[0][0][3] | a[0][0][4] | [0x1078,0x107D)
    **  +------------+------------+------------+------------+------------+
    **  | a[0][1][0] | a[0][1][1] | a[0][1][2] | a[0][1][3] | a[0][1][4] | [0x107D,0x1082)
    **  +------------+------------+------------+------------+------------+
    **  | a[0][2][0] | a[0][2][1] | a[0][2][2] | a[0][2][3] | a[0][2][4] | [0x1082,0x1087)
    **  +------------+------------+------------+------------+------------+
    **  | a[0][3][0] | a[0][3][1] | a[0][3][2] | a[0][3][3] | a[0][3][4] | [0x1087,0x108C)
    **  +------------+------------+------------+------------+------------+
    **
    **  Repeated a total of 4 times
    */
    char *data = (char *)space; /*=C++=*/

    for (size_t i = 0; i < ndims - 1; i++)
    {
        fprintf(stderr, "data: 0x%08" PRIXPTR "\n", (uintptr_t)data);
        /* XXX: Looping structure? */
        char *start = data + nbytes[i];
        fprintf(stderr, "start: 0x%08" PRIXPTR " (i = %zu, nbytes = %zu)\n",
                (uintptr_t)start, i, nbytes[i]);
        for (size_t j = 0; j < a->dim[i].number; j++)
        {
            fprintf(stderr, "LHS: addr[%zu]: 0x%08" PRIXPTR " (size = %zu)\n",
                    j, (uintptr_t)(data + j * a->dim[i].size), a->dim[i].size);
            fprintf(stderr, "RHS: addr[%zu]: 0x%08" PRIXPTR " (j = %zu, size = %zu)\n",
                    j, (uintptr_t)(start + j * a->dim[i+1].size), j, nbytes[i+1]);
            /* XXX: erroneous */
            *(void **)(data + j * a->dim[i].size) = start + j * nbytes[i+1];
        }
        data = start;
    }

    return(a);
}

static void free_array(Array *a)
{
    if (a != 0)
    {
        free(a->base);
        free(a);
    }
}

int main(void)
{
    //Alternative (non-varargs) interface
    //size_t sizes[] = { 3, 4, 5 };
    //enum { NUM_SIZES = sizeof(sizes) / sizeof(size[0]) };
    //extern Array *make_array(size_t elem_size, size_t ndims, size_t *dims);
    //Array *a = make_array(sizeof(char), NUM_SIZES, sizes);

    /* Approximately equivalent to char a[3][4][5]; */
    Array *a = make_array(sizeof(char), 3, (size_t)3, (size_t)4, (size_t)5);
    if (a->base == 0)
        fprintf(stderr, "Array allocation failed!\n");
    else
    {
        dump_array_info_pointers(stdout, "After allocation", "array", a);
        char ***b = (char ***)a->base;
        for (size_t i = 0; i < a->dim[0].number; i++)
        {
            for (size_t j = 0; j < a->dim[1].number; j++)
            {
                for (size_t k = 0; k < a->dim[2].number; k++)
                {
                    b[i][j][k] = i + j + k + 'A';
                    printf("array[%zu][%zu][%zu]: 0x%08" PRIXPTR ": 0x%08" PRIXPTR ": 0x%08" PRIXPTR ": %3d = %c\n",
                        i, j, k, (uintptr_t)&b[i], (uintptr_t)&b[i][j], (uintptr_t)&b[i][j][k],
                        b[i][j][k], b[i][j][k]);
                }
            }
        }
    }
    free_array(a);
    return(0);
}
