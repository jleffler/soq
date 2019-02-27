/*
** SO xxxx-yyyy
** Sort 6 named variables - no array or structure allowed
*/

#include <stdio.h>

static int test_and_swap(int *p1, int *p2)
{
    if (*p1 > *p2)
    {
        int t = *p1;
        *p1 = *p2;
        *p2 = t;
        return 1;
    }
    return 0;
}

int main(void)
{
    int v1 = 93;
    int v2 = 81;
    int v3 = 63;
    int v4 = 84;
    int v5 = 14;
    int v6 = 87;

    int swap;

    printf("v1 = %d; v2 = %d; v3 = %d; v4 = %d; v5 = %d; v6 = %d\n", v1, v2, v3, v4, v5, v6);
    do
    {
        swap = 0;
        swap += test_and_swap(&v1, &v2);
        swap += test_and_swap(&v2, &v3);
        swap += test_and_swap(&v3, &v4);
        swap += test_and_swap(&v4, &v5);
        swap += test_and_swap(&v5, &v6);
    } while (swap != 0);
    printf("v1 = %d; v2 = %d; v3 = %d; v4 = %d; v5 = %d; v6 = %d\n", v1, v2, v3, v4, v5, v6);

    return 0;
}
