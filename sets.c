/* SO 31096894 - sets.c */
/* Set of elements 1..1024 - in C89/C90 */

#include "sets.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long Bits;
#define C_BITS(n)  ((Bits)(n))

enum { ARRAY_SIZE = MAX_ELEMENTS / (sizeof(Bits) * CHAR_BIT) };

struct Set
{
     Bits set[ARRAY_SIZE];
};

_Static_assert(sizeof(struct Set) == 128, "Incorrect size of struct Set");

Set *set_create(void)
{
    Set *set = malloc(sizeof(*set));
    if (set != 0)
        memset(set, 0, sizeof(*set));
    return set;
}

void set_destroy(Set *set)
{
    free(set);
}

void set_insert(Set *set, int value)
{
    assert(value >= 1 && value <= MAX_ELEMENTS);
    value--;  /* 0..1023 */
    int index = value / (sizeof(Bits) * CHAR_BIT);
    int bitnum = value % (sizeof(Bits) * CHAR_BIT);
    Bits mask = C_BITS(1) << bitnum;
    /* printf("I: %d (%d:%d:0x%.2lX)\n", value+1, index, bitnum, mask); */
    set->set[index] |= mask;
}

void set_delete(Set *set, int value)
{
    assert(value >= 1 && value <= MAX_ELEMENTS);
    value--;  /* 0..1023 */
    int index = value / (sizeof(Bits) * CHAR_BIT);
    int bitnum = value % (sizeof(Bits) * CHAR_BIT);
    Bits mask = C_BITS(1) << bitnum;
    /* printf("D: %d (%d:%d:0x%.2lX)\n", value+1, index, bitnum, mask); */
    set->set[index] &= ~mask;
}

/* C90 does not support <stdbool.h> */
int set_member(Set *set, int value)
{
    assert(value >= 1 && value <= MAX_ELEMENTS);
    value--;  /* 0..1023 */
    int index = value / (sizeof(Bits) * CHAR_BIT);
    int bitnum = value % (sizeof(Bits) * CHAR_BIT);
    Bits mask = C_BITS(1) << bitnum;
    /* printf("T: %d (%d:%d:0x%.2lX) = %d\n", value+1, index, bitnum, mask,
              (set->set[index] & mask) != 0); */
    return (set->set[index] & mask) != 0;
}

/* set1 intersect set2 */
void set_intersect(Set *set1, Set *set2, Set *result)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        result->set[i] = set1->set[i] & set2->set[i];
}

/* set1 union set2 */
void set_union(Set *set1, Set *set2, Set *result)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        result->set[i] = set1->set[i] | set2->set[i];
}

/* set1 minus set2 */
void set_difference(Set *set1, Set *set2, Set *result)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        result->set[i] = set1->set[i] & ~set2->set[i];
}

void set_empty(Set *set)
{
    int i;
    for (i = 0; i < ARRAY_SIZE; i++)
        set->set[i] = 0;
}

#include <stdio.h>
#include "stderr.h"

enum { NUMBERS_PER_LINE = 15 };

static void load_set(Set *set, int num1, int num2, int inc1, int inc2)
{
    int i;
    for (i = num1; i <= MAX_ELEMENTS; i += inc1)
        set_insert(set, i);
    for (i = num2; i <= MAX_ELEMENTS; i += inc2)
        set_delete(set, i);
}

static void dump_set(const char *tag, Set *set)
{
    int i;
    int n = 0;
    printf("Set %s:\n", tag);

    for (i = 1; i <= MAX_ELEMENTS; i++)
    {
        if (set_member(set, i))
        {
            printf(" %4d", i);
            if (++n % NUMBERS_PER_LINE == 0)
            {
                putchar('\n');
                n = 0;
            }
        }
    }
    if (n % NUMBERS_PER_LINE != 0)
        putchar('\n');
}

static void test_ops(void)
{
    Set *s1 = set_create();
    Set *s2 = set_create();
    Set *s3 = set_create();

    if (s1 == 0 || s2 == 0 || s3  == 0)
        err_syserr("Out of memory\n");

    load_set(s1, 1, 3, 4, 6);
    dump_set("S1", s1);

    load_set(s2, 2, 5, 7, 9);
    dump_set("S2", s2);

    set_union(s1, s2, s3);
    dump_set("S1 union S2", s3);

    set_empty(s3);
    set_intersect(s1, s2, s3);
    dump_set("S1 intersect S2", s3);

    set_empty(s3);
    set_difference(s1, s2, s3);
    dump_set("S1 minus S2", s3);

    set_empty(s3);
    set_difference(s2, s1, s3);
    dump_set("S2 minus S1", s3);

    set_destroy(s1);
    set_destroy(s2);
    set_destroy(s3);
}

static void test_set(void)
{
    Set *set = set_create();
    if (set == 0)
        err_syserr("Out of memory\n");
    load_set(set, 1, 3, 4, 6);
    dump_set("S0", set);
    set_destroy(set);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[argc-argc]);

    test_set();
    test_ops();

    return 0;
}
