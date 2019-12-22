#include <stdbool.h>
#include <stdio.h>

static bool is_palindromic(int n)
{
    char number[12];
    int len = snprintf(number, sizeof(number), "%d", n);
    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        if (number[i] != number[j])
            return false;
    }
    return true;
}

int main(void)
{
    int f1 = 0, f2 = 0, pp = 0;
    for (int i = 999; i >- 500; i--)
    {
        for (int j = 999; j >= 500; j--)
        {
            if (is_palindromic(i * j) && i * j > pp)
            {
                f1 = i;
                f2 = j;
                pp = i * j;
                printf("f1 = %3d, f2 = %3d, pp = %6d\n", f1, f2, pp);
            }
        }
    }
    printf("f1 = %3d, f2 = %3d, pp = %6d\n", f1, f2, pp);
    return 0;
}
