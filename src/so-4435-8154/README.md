### Stack Overflow Question 4435-8154

[SO 4435-8154](http://stackoverflow.com/q/44358154) &mdash;
C — fix dimension matrix

This code deals with positive integers of essentially arbitrary size.
Note that the code uses a number of small functions to do the work —
it makes it _so_ much easier.
The use of `width + 2` in the calls to `print_line()` allows for the
space before and after the number.

If the code needed to deal with negative numbers too, then it would
check for the minimum value too, and would use the wider of the maximum
and minimum values to control the layout.
It might well rewrite the `max_element()` function to compute both the
maximum and minimum, and it might be redesignated as `cell_width()` or
some such name.

Using a size of 0 to `snprintf()` allows you to use a null pointer too,
and it returns the number of characters it would have written — but
doesn't write anything anywhere.
There are other ways that would also work, but this is by far the
simplest way of doing it.

### Code

    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    static int max_element(int rows, int cols, int matrix[rows][cols])
    {
        int max = matrix[0][0];
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (matrix[i][j] > max)
                    max = matrix[i][j];
            }
        }
        return max;
    }

    static void print_line(int wid, int cols)
    {
        assert(wid <= 20);
        putchar('+');
        for (int i = 0; i < cols; i++)
            printf("%*.*s+", wid, wid, "--------------------");
        putchar('\n');
    }

    static void print_row(int width, int cols, int vector[cols])
    {
        putchar('|');
        for (int i = 0; i < cols; i++)
            printf(" %*d |", width, vector[i]);
        putchar('\n');
    }

    static void print_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
    {
        printf("\n%s:\n", tag);
        int max = max_element(rows, cols, matrix);
        int width = snprintf(0, 0, "%d", max);

        print_line(width + 2, cols);
        for (int i = 0; i < rows; i++)
        {
            print_row(width, cols, matrix[i]);
            print_line(width + 2, cols);
        }
    }

    static void test_matrix(int rows, int cols)
    {
        int matrix[rows][cols];
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                matrix[i][j] = (1234 * j + i * 81);
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%dx%d matrix", rows, cols);
        print_matrix(buffer, rows, cols, matrix);
    }

    static void random_matrix(int rows, int cols)
    {
        int matrix[rows][cols];
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                matrix[i][j] = rand();
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%dx%d random matrix", rows, cols);
        print_matrix(buffer, rows, cols, matrix);
    }

    int main(void)
    {
        test_matrix(3, 3);
        test_matrix(5, 7);
        test_matrix(11, 7);
        srand(time(0));
        random_matrix(6, 6);
        return 0;
    }



### Example output:

    3x3 matrix:
    +------+------+------+
    |    0 | 1234 | 2468 |
    +------+------+------+
    |   81 | 1315 | 2549 |
    +------+------+------+
    |  162 | 1396 | 2630 |
    +------+------+------+

    5x7 matrix:
    +------+------+------+------+------+------+------+
    |    0 | 1234 | 2468 | 3702 | 4936 | 6170 | 7404 |
    +------+------+------+------+------+------+------+
    |   81 | 1315 | 2549 | 3783 | 5017 | 6251 | 7485 |
    +------+------+------+------+------+------+------+
    |  162 | 1396 | 2630 | 3864 | 5098 | 6332 | 7566 |
    +------+------+------+------+------+------+------+
    |  243 | 1477 | 2711 | 3945 | 5179 | 6413 | 7647 |
    +------+------+------+------+------+------+------+
    |  324 | 1558 | 2792 | 4026 | 5260 | 6494 | 7728 |
    +------+------+------+------+------+------+------+

    11x7 matrix:
    +------+------+------+------+------+------+------+
    |    0 | 1234 | 2468 | 3702 | 4936 | 6170 | 7404 |
    +------+------+------+------+------+------+------+
    |   81 | 1315 | 2549 | 3783 | 5017 | 6251 | 7485 |
    +------+------+------+------+------+------+------+
    |  162 | 1396 | 2630 | 3864 | 5098 | 6332 | 7566 |
    +------+------+------+------+------+------+------+
    |  243 | 1477 | 2711 | 3945 | 5179 | 6413 | 7647 |
    +------+------+------+------+------+------+------+
    |  324 | 1558 | 2792 | 4026 | 5260 | 6494 | 7728 |
    +------+------+------+------+------+------+------+
    |  405 | 1639 | 2873 | 4107 | 5341 | 6575 | 7809 |
    +------+------+------+------+------+------+------+
    |  486 | 1720 | 2954 | 4188 | 5422 | 6656 | 7890 |
    +------+------+------+------+------+------+------+
    |  567 | 1801 | 3035 | 4269 | 5503 | 6737 | 7971 |
    +------+------+------+------+------+------+------+
    |  648 | 1882 | 3116 | 4350 | 5584 | 6818 | 8052 |
    +------+------+------+------+------+------+------+
    |  729 | 1963 | 3197 | 4431 | 5665 | 6899 | 8133 |
    +------+------+------+------+------+------+------+
    |  810 | 2044 | 3278 | 4512 | 5746 | 6980 | 8214 |
    +------+------+------+------+------+------+------+

    6x6 random matrix:
    +------------+------------+------------+------------+------------+------------+
    |   70985332 | 1197050839 | 1206645977 | 1410856818 | 1903593599 |  486245387 |
    +------------+------------+------------+------------+------------+------------+
    | 1150942474 | 1504951989 |  665684757 | 1921393676 | 1151912593 |  629872846 |
    +------------+------------+------------+------------+------------+------------+
    | 1326026659 | 2092252894 | 1597153480 | 1960434507 |  181163228 | 1826045197 |
    +------------+------------+------------+------------+------------+------------+
    |  652826702 |  564427991 |  905975938 | 1078532736 | 2137713272 | 1145548194 |
    +------------+------------+------------+------------+------------+------------+
    | 1037601203 | 1396205181 |  466666298 |  650191642 | 1374131158 |  983232668 |
    +------------+------------+------------+------------+------------+------------+
    |  304787411 |  813518582 | 1925910872 | 1910498120 |  566412896 | 2054019568 |
    +------------+------------+------------+------------+------------+------------+

Testing was done on a Mac running macOS Sierra 10.12.5 using GCC 7.1.0.
Compilation command line (source code in `pm79.c`):

    gcc -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes \
        -Wstrict-prototypes -Wold-style-definition pm79.c -o pm79

I very seldom compile with less restrictive options than those — I don't trust the result.

<hr>

Another way to format the line — with no limit on the cell width:

    #include <string.h>

    static void print_line(int wid, int cols)
    {
        char buffer[wid + 1];
        memset(buffer, '-', wid);
        buffer[wid] = '\0';
        putchar('+');
        for (int i = 0; i < cols; i++)
            printf("%s+", buffer);
        putchar('\n');
    }

