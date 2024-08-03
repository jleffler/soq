### Stack Overflow Question 5651-9149

[SO 5651-9149](https://stackoverflow.com/q/56519149) &mdash;
How to find connected cells with same value in an array?


There are a number of problems with the recursive solution, including:

1. You don't pass the search value to the recursive function, so
   different recursive calls can end up looking for different values.
2. You don't check whether you've already visited a given cell, so the
   recursion doesn't stop.

Here are two versions of the code that don't crash.

### `conn29.c` — minimally fixed

This code fixes point 2, and the result demonstrates point 1.

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

**Output**

    Base array (13x13):
     7 5 5 . . . . 3 7 5 3 9 4
     3 8 1 8 2 7 3 5 5 5 8 6 5
     5 4 5 6 . 5 5 5 . . 7 9 5
     5 3 9 5 5 3 . 5 . 4 5 9 5
     5 1 5 5 5 3 . 5 . 5 5 5 .
     . 5 7 5 3 2 2 4 8 . 8 3 6
     5 1 3 5 6 5 . 2 7 4 2 7 1
     8 . 4 5 5 7 9 . 5 . 5 . 7
     5 9 5 2 . 1 5 5 3 . . 5 5
     . 7 1 8 3 3 5 9 . . 3 3 3
     . 5 1 5 9 9 5 8 5 2 5 . 8
     4 2 9 9 . 5 5 5 . 5 2 4 3
     5 2 5 2 3 5 4 1 5 9 5 5 5
    i0 =  5, j0 =  3, base[ 5][ 3] = 5
    Connected region (13x13):
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . 5 5 3 . . . . . . .
     . . . 5 . 3 . . . . . . .
     . . . 5 . 2 2 4 . . . . .
     . . . 5 . . . . . . . . .
     . . . 5 5 7 . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .

### `conn11.c` — fixed fully

There is probably some room for improvement still, but this works.

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    enum { SIZE = 13 };

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

        connectedvals(base, trace, i0, j0, base[i0][j0]);

        dump_array("Connected region", SIZE, SIZE, trace);

        return 0;
    }

**Output**

    Base array (13x13):
     7 5 5 . . . . 3 7 5 3 9 4
     3 8 1 8 2 7 3 5 5 5 8 6 5
     5 4 5 6 . 5 5 5 . . 7 9 5
     5 3 9 5 5 3 . 5 . 4 5 9 5
     5 1 5 5 5 3 . 5 . 5 5 5 .
     . 5 7 5 3 2 2 4 8 . 8 3 6
     5 1 3 5 6 5 . 2 7 4 2 7 1
     8 . 4 5 5 7 9 . 5 . 5 . 7
     5 9 5 2 . 1 5 5 3 . . 5 5
     . 7 1 8 3 3 5 9 . . 3 3 3
     . 5 1 5 9 9 5 8 5 2 5 . 8
     4 2 9 9 . 5 5 5 . 5 2 4 3
     5 2 5 2 3 5 4 1 5 9 5 5 5
    i0 =  5, j0 =  3, base[ 5][ 3] = 5
    Connected region (13x13):
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . 5 5 . . . . . . . .
     . . 5 5 5 . . . . . . . .
     . . . 5 . . . . . . . . .
     . . . 5 . . . . . . . . .
     . . . 5 5 . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .
     . . . . . . . . . . . . .

The test harness is almost identical between the two programs.  The
difference is in the argument list for the initial call to
`connectedvals()` because the two implementations have different numbers
of arguments.

The choice of `13` for size is not accidental; it happens to produce a
neat result with the random number generator.  The matrix is generated
'at random', except that the result is skewed deliberately towards the
numbers 0 and 5.  You may well get a different result from the `rand()`
function on your machine; I was testing on a MacBook Pro running macOS
10.14.5 Mojave, using GCC 9.1.0 to compile.

There is provision for using the time as a seed — uncommenting one
line.  For initial testing, though, determinacy (repeatability) is more
beneficial than randomness.  There are many better ways of seeding
`rand()` than using the time; that is rather predictable.  However, such
refinements are out of scope for the question.

Note the use of the `enum { SIZE = 13 };`.  By changing just the one
number, the whole program adapts to new sizes.

