/* Sort 3 items - fixed comparisons */
/* Based on code for SO 4203-5818 */
#include <assert.h>
#include <stdio.h>

static inline void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

/* Interesting: 4 of 6 permutations work, 2 fail */
#if P_01_02_12 + P_01_12_02 + \
    P_02_01_12 + P_02_12_01 + \
    P_12_01_02 + P_12_02_01 > 1
#error Too many of the control macros (P_[01][12]_[01][12]_[01][12]) are set
#endif
#if P_01_02_12 + P_01_12_02 + \
    P_02_01_12 + P_02_12_01 + \
    P_12_01_02 + P_12_02_01 == 0
#define P_02_01_12 1
#endif

#define P_STRING(x) static char const variant[] = #x

#ifdef P_01_02_12
P_STRING(P_01_02_12);
#endif
#ifdef P_01_12_02
P_STRING(P_01_12_02);
#endif
#ifdef P_02_01_12
P_STRING(P_02_01_12);
#endif
#ifdef P_02_12_01
P_STRING(P_02_12_01);
#endif
#ifdef P_12_01_02
P_STRING(P_12_01_02);
#endif
#ifdef P_12_02_01
P_STRING(P_12_02_01);
#endif

#if P_02_01_12
/* Working */
static void sort_3(int *a)
{
    if (a[0] > a[2]) swap(&a[0], &a[2]);
    if (a[0] > a[1]) swap(&a[0], &a[1]);
    if (a[1] > a[2]) swap(&a[1], &a[2]);
}
#endif /* 0 */

#if P_12_01_02
/* Triggers assertion */
static void sort_3(int *a)
{
    if (a[1] > a[2]) swap(&a[1], &a[2]);
    if (a[0] > a[1]) swap(&a[0], &a[1]);
    if (a[0] > a[2]) swap(&a[0], &a[2]);
}
#endif /* 0 */

#if P_01_12_02
/* Triggers assertion */
static void sort_3(int *a)
{
    if (a[0] > a[1]) swap(&a[0], &a[1]);
    if (a[1] > a[2]) swap(&a[1], &a[2]);
    if (a[0] > a[2]) swap(&a[0], &a[2]);
}
#endif /* 0 */

#if P_12_02_01
/* Working */
static void sort_3(int *a)
{
    if (a[1] > a[2]) swap(&a[1], &a[2]);
    if (a[0] > a[2]) swap(&a[0], &a[2]);
    if (a[0] > a[1]) swap(&a[0], &a[1]);
}
#endif /* 0 */

#if P_02_12_01
/* Working */
static void sort_3(int *a)
{
    if (a[0] > a[2]) swap(&a[0], &a[2]);
    if (a[1] > a[2]) swap(&a[1], &a[2]);
    if (a[0] > a[1]) swap(&a[0], &a[1]);
}
#endif /* 0 */

#if P_01_02_12
/* Working */
static void sort_3(int *a)
{
    if (a[0] > a[1]) swap(&a[0], &a[1]);
    if (a[0] > a[2]) swap(&a[0], &a[2]);
    if (a[1] > a[2]) swap(&a[1], &a[2]);
}
#endif /* 0 */

static void print_3(int *a)
{
    const char *pad = "";
    for (int i = 0; i < 3; i++)
    {
        printf("%s%d", pad, a[i]);
        pad = " ";
    }
}

static void check_3(int *a)
{
    assert(a[0] <= a[1]);
    assert(a[1] <= a[2]);
}

int main(void)
{
    printf("Variant: %s\n", variant);
    fflush(stdout);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                int a[3] = { i, j, k };
                print_3(a);
                fputs(" : ", stdout);
                sort_3(a);
                print_3(a);
                putchar('\n');
                check_3(a);
            }
        }
    }
    return 0;
}

