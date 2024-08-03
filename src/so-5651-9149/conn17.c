/* SO 5651-9149 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { SIZE = 50 };

extern void connectedvals(char array[SIZE][SIZE], char newarray[SIZE][SIZE], int x, int y, int value);

void connectedvals(char array[SIZE][SIZE], char newarray[SIZE][SIZE], int x, int y, int value)
{
    /*printf("a[%2d][%2d] = %d\n", x, y, array[x][y]);*/
    if (array[x][y] != value || newarray[x][y] != 0)
        return;
    newarray[x][y] = value;

    if (y + 1 < SIZE)
        connectedvals(array, newarray, x + 0, y + 1, value);
    if (y - 1 >= 0)
        connectedvals(array, newarray, x + 0, y - 1, value);
    if (x + 1 < SIZE)
        connectedvals(array, newarray, x + 1, y + 0, value);
    if (x - 1 >= 0)
        connectedvals(array, newarray, x - 1, y + 0, value);
}

static void dump_array(const char *tag, int rows, int cols, char array[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //putchar(' ');
            if (array[i][j] == 0)
                putchar('.');
            else
                printf("%d", array[i][j]);
        }
        putchar('\n');
    }
}

int main(void)
{
    char base[SIZE][SIZE] = { 0 };
    char trace[SIZE][SIZE] = { 0 };

    unsigned seed = time(0);
    printf("Seed: %u\n", seed);
    srand(seed);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            base[i][j] = (rand() % 12);
            if (base[i][j] > 9)
                base[i][j] = 0;
            if ((rand() % 3) == 0)
                base[i][j] = 5;
        }
    }

    dump_array("Base array", SIZE, SIZE, base);

    int i0 = rand() % SIZE;
    int j0 = rand() % SIZE;

    while (base[i0][j0] != 5)
    {
        i0 = rand() % SIZE;
        j0 = rand() % SIZE;
    }

    printf("i0 = %2d, j0 = %2d, base[%2d][%2d] = %d\n", i0, j0, i0, j0, base[i0][j0]);

    connectedvals(base, trace, i0, j0, base[i0][j0]);

    dump_array("Connected region", SIZE, SIZE, trace);

    return 0;
}

