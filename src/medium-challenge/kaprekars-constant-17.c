#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { KAPREKARS_CONSTANT = 6174 };

static int charcmp(const void *v1, const void *v2)
{
    int c1 = *(unsigned char *)v1;
    int c2 = *(unsigned char *)v2;
    return(c1 - c2);    /* No risk of overflow */
}

static void reverse(char *base, int len)
{
    int lo = 0;
    int hi = len - 1;
    while (lo < hi)
    {
        char t = base[lo];
        base[lo++] = base[hi];
        base[hi--] = t;
    }
}

static int KaprekarsConstant(int n)
{
    //assert(n >= 1000 && n < 10000);
    assert(n >= 0 && n < 10000 && n % 1111 != 0);
    char digits[12];
    snprintf(digits, sizeof(digits), "%.4d", n);
    //printf("raw: %s, ", digits);
    qsort(digits, 4, 1, charcmp);
    //printf("incr: %s, ", digits);
    int lo = atoi(digits);
    reverse(digits, 4);
    //printf("decr: %s, ", digits);
    int hi = atoi(digits);
    assert(hi > lo);
    //printf("diff: %4d\n", hi - lo);
    return hi - lo;
}

static int KaprekarsNumber(int i)
{
    int number = i;
    int count = 0;
    while (number != KAPREKARS_CONSTANT)
    {
        number = KaprekarsConstant(number);
        count++;
    }
    return count;
}

int main(void)
{
    for (int i = 1; i < 10000; i++)
    {
        if (i % 1111 != 0)
            printf("%.4d: %3d\n", i, KaprekarsNumber(i));
    }
    return 0;
}
