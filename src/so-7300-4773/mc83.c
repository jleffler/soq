/* SO 7300-4773 - original code */
/* Reformatted and modified enough to compile under stringent compilation options */
#include <stdio.h>
int main(void)
{
    int M[2][2] =
    {
        {4, 6},
        {9, 2},
    };
    int i, j, row, col;
    int arr[2][2] = {0};
    int t;
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            t = M[i][j];
            for (col = 0; col < 2; ++col)
            {
                for (row = 0; row < 2; ++row)
                {
                    if (row == i && col == j)
                        continue;
                    else if (t >= M[row][col])
                        arr[i][j] += 1;
                }
            }
        }
    }
    printf("The Matrix:\n");
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
            printf("%d  ", arr[i][j]);
        printf("\n");
    }
    return 0;
}
