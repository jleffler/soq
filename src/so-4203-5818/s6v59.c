/*
** SO xxxx-yyyy
** Sort 6 named variables - no array or structure allowed
*/

#include <stdio.h>

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
        if (v1 > v2) { int t = v1; v1 = v2; v2 = t; swap = 1; }
        if (v2 > v3) { int t = v2; v2 = v3; v3 = t; swap = 1; }
        if (v3 > v4) { int t = v3; v3 = v4; v4 = t; swap = 1; }
        if (v4 > v5) { int t = v4; v4 = v5; v5 = t; swap = 1; }
        if (v5 > v6) { int t = v5; v5 = v6; v6 = t; swap = 1; }
    } while (swap != 0);

    printf("v1 = %d; v2 = %d; v3 = %d; v4 = %d; v5 = %d; v6 = %d\n", v1, v2, v3, v4, v5, v6);

    return 0;
}
