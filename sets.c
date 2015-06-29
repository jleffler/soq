/* SO 31096894 - sets.c */

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

Set *create(void)
{
    Set *set = malloc(sizeof(*set));
    if (set != 0)
        memset(set, 0, sizeof(*set));
    return set;
}

void destroy(Set *set)
{
    free(set);
}

void insert(Set *set, int value)
{
    assert(value >= 1 && value <= MAX_ELEMENTS);
    value--;  /* 0..1023 */
    int index = value / (sizeof(Bits) * CHAR_BIT);
    int bitnum = value % (sizeof(Bits) * CHAR_BIT);
    Bits mask = C_BITS(1) << bitnum;
    /* printf("I: %d (%d:%d:0x%.2lX)\n", value+1, index, bitnum, mask); */
    set->set[index] |= mask;
}

void delete(Set *set, int value)
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
int in_set(Set *set, int value)
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

#include <stdio.h>

enum { NUMBERS_PER_LINE = 15 };

int main(void)
{
    Set *set = create();
    if (set != 0)
    {
        int i;
        int n = 0;
        for (i = 1; i <= MAX_ELEMENTS; i += 4)
             insert(set, i);
        for (i = 3; i <= MAX_ELEMENTS; i += 6)
             delete(set, i);

        for (i = 1; i <= MAX_ELEMENTS; i++)
        {
             if (in_set(set, i))
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
        destroy(set);
    }
    return 0;
}
