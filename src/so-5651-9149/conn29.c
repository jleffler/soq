/* SO 5651-9149 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { SIZE = 13 };

static
void connectedvals(char array[SIZE][SIZE], char newarray[SIZE][SIZE], int x, int y)
{
    if (newarray[x][y] != 0)
        return;
    int height = array[x][y];
    newarray[x][y] = array[x][y];
    int up = y + 1;
    int down = y - 1;
    int left = x - 1;
    int right = x + 1;

    if (up < SIZE)
    {
        if (array[x][up] == height)
        {
            newarray[x][up] = height;
            up++;
            connectedvals(array, newarray, x, up);
        }
    }

    if (down >= 0)
    {
        if (array[x][down] == height)
        {
            newarray[x][down] = height;
            down--;
            connectedvals(array, newarray, x, down);
        }
    }

    if (right < SIZE)
    {
        if (array[right][y] == height)
        {
            newarray[right][y] = height;
            right++;
            connectedvals(array, newarray, right, y);
        }
    }

    if (left >= 0)
    {
        if (array[left][y] == height)
        {
            newarray[left][y] = height;
            left--;
            connectedvals(array, newarray, left, y);
        }
    }
}


static void dump_array(const char *tag, int rows, int cols, char array[rows][cols])
{
    printf("%s (%dx%d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            putchar(' ');
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

    // srand(time(0));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            base[i][j] = (rand() % 12);
            if (base[i][j] > 9)
                base[i][j] = 0;
            if ((rand() % 4) == 0)
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

    connectedvals(base, trace, i0, j0);

    dump_array("Connected region", SIZE, SIZE, trace);

    return 0;
}

