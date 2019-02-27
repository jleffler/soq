/* Code for https://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

#include <stdio.h>

void fonc(int tab2[8][8], int *vect);

void fonc(int tab2[8][8], int *vect)
{
    int i = 0;
    int j = 0;
    int k = 0;

    vect[k] = tab2[i][j];
    printf("v[%2d] = m[%2d][%2d] = %d\n", k, i, j, tab2[i][j]);

    while (i != 8 && j != 8)
    {
        // bas
        i = i;
        j = j+1;
        vect[k++] = tab2[i][j];
        printf("v[%2d] = m[%2d][%2d] = %d\n", k, i, j, tab2[i][j]);

        // descente
        while (j != 0)
        {
            i = i+1;
            j = j-1;
            vect[k++] = tab2[i][j];
            printf("v[%2d] = m[%2d][%2d] = %d\n", k, i, j, tab2[i][j]);
        }

        // droite
        i = i;
        j = j+1;
        vect[k++] = tab2[i][j];
        printf("v[%2d] = m[%2d][%2d] = %d\n", k, i, j, tab2[i][j]);

        // montée
        while (i != 0)
        {
            i = i-1;
            j = j+1;
            printf("v[%2d] = m[%2d][%2d] = %d\n", k, i, j, tab2[i][j]);
            vect[k++] = tab2[i][j];
        }
    }
}

int main(void)
{
    int vect[64];
    int tab2[8][8] =
    {
        {1, 2, 6, 7, 15, 16, 28, 1},
        {3, 5, 8, 14, 17, 27, 29, 1},
        {4, 9, 13, 18, 26, 30, 39, 1},
        {10, 12, 19, 25, 31, 38, 40, 1},
        {11, 20, 24, 32, 37, 41, 46, 1},
        {21, 23, 33, 36, 42, 45, 47, 1},
        {22, 34, 35, 43, 44, 48, 49, 1},
        {22, 34, 35, 43, 44, 48, 49, 1}
    };

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%3d", tab2[i][j]);
        putchar('\n');
    }

    fonc(tab2, vect);

    for (int i = 0; i < 8 * 8; i++)
    {
        printf("%3d", vect[i]);
        if (i % 8 == 7)
            putchar('\n');
    }

    return 0;
}
