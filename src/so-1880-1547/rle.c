/* Code for http://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

#include <stdio.h>

static inline int max(int a, int b) { return (a > b) ? a : b; }
static inline int min(int a, int b) { return (a < b) ? a : b; }

static void print_info(int r, int c)
{
    int n = r + c - 1;
    printf("R = %d, C = %d, N = %d\n", r, c, n);
    for (int i = 0; i < n; i++)
    {
        /*
        int max_x = min(i, c-1);
        int min_x = max(0, i - n + c);
        int max_y = min(i, r-1);
        int min_y = max(0, i - n + r);
        printf("i = %d, min_x = %d, max_x = %d, min_y = %d, max_y = %d\n",
                i, min_x, max_x, min_y, max_y);
        */
        printf("%d:", i);
        if (i % 2 == 0)
        {
            int max_x = min(i, c-1);
            int min_x = max(0, i - n + c);
            for (int j = min_x; j <= max_x; j++)
                printf(" (%d,%d)", j, i - j);
        }
        else
        {
            int max_y = min(i, r-1);
            int min_y = max(0, i - n + r);
            for (int j = min_y; j <= max_y; j++)
                printf(" (%d,%d)", i - j, j);
        }
        putchar('\n');
    }

}

int main(void)
{
    struct test
    {
        int rows;
        int cols;
    } tests[] = { { 4, 4 }, { 6, 4 }, { 4, 7 } };

    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
        print_info(tests[i].rows, tests[i].cols);

    return 0;
}
