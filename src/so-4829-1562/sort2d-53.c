/* SO 4829-1562 */

/*
**  + Enter a square matrix of dimensions n .
**  + Elements below main diagonal sort in ascending order.
**  + Elements above main diagonal sort in descending order.
**  + Elements on main diagonal sort :
**    - first even numbers in ascending order.
**    - then odd numbers in descending order.
*/

/* Variation 1: Using direct sorting of triangles of matrix without copying */

static inline int cmp_asc(int x, int y) { return (x > y) - (x < y); }
static inline int cmp_dsc(int x, int y) { return (x < y) - (x > y); }
static inline int cmp_eaod(int x, int y)
{
    int px = x & 1;
    int py = y & 1;
    if (px != py)
        return px - py;
    if (px == 1)
        return cmp_dsc(x, y);
    return cmp_asc(x, y);
}

#include <stdio.h>
//#include <stdlib.h>

static void print_matrix(const char *tag, size_t r, size_t c, int matrix[r][c])
{
    printf("%s:\n", tag);
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
            printf("%3d", matrix[i][j]);
        putchar('\n');
    }
}

static void sort_diagonal(size_t n, int matrix[n][n])
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            if (cmp_eaod(matrix[i][i], matrix[j][j]) > 0)
            {
                int t = matrix[i][i];
                matrix[i][i] = matrix[j][j];
                matrix[j][j] = t;
            }
        }
    }
}

/*
**   D0  U0  U1  U2  U3
**   L0  D1  U4  U5  U6
**   L1  L2  D3  U7  U8
**   L3  L4  L5  D4  U9
**   L6  L7  L8  L9  D5
**
** D0 = (0, 0); U0 = (0, 1); U1 = (0, 2); U2 = (0, 3); U3 = (0, 4);
** L0 = (1, 0); D1 = (1, 1); U4 = (1, 2); U5 = (1, 3); U6 = (1, 4);
** L1 = (2, 0); L2 = (2, 1); D2 = (2, 2); U7 = (2, 3); U8 = (2, 4);
** L3 = (3, 0); L4 = (3, 1); L5 = (3, 2); D3 = (3, 3); U9 = (3, 4);
** L6 = (4, 0); L7 = (4, 1); L8 = (4, 2); L9 = (4, 3); D4 = (4, 4); 
*/

static void init_lt_map(size_t n, size_t map[][2])
{
    size_t m = (n * (n - 1)) / 2;
    size_t r = 1;
    size_t c = 0;
    for (size_t i = 0; i < m; i++)
    {
        map[i][0] = r;
        map[i][1] = c++;
        if (c == r)
        {
            r++;
            c = 0;
        }
    }
    //print_matrix("LT map", m, 2, map);
}

/*
** It is probably best to create an array that does the mapping from
** an index to the row and column, with one such mapping for the lower
** triangle; one for the upper triangle.
*/

static void sort_lt(size_t n, int matrix[n][n])
{
    size_t m = (n * (n - 1)) / 2;
    size_t lt[m][2];
    init_lt_map(n, lt);

    for (size_t i = 0; i < m; i++)
    {
        size_t xi = lt[i][0];
        size_t yi = lt[i][1];
        for (size_t j = i + 1; j < m; j++)
        {
            size_t xj = lt[j][0];
            size_t yj = lt[j][1];
            if (cmp_asc(matrix[xi][yi], matrix[xj][yj]) > 0)
            {
                int t = matrix[xi][yi];
                matrix[xi][yi] = matrix[xj][yj];
                matrix[xj][yj] = t;
            }
        }
    }
}

static void init_ut_map(size_t n, size_t map[][2])
{
    size_t m = (n * (n - 1)) / 2;
    size_t r = 0;
    size_t c = 0;
    for (size_t i = 0; i < m; i++)
    {
        map[i][0] = r;
        map[i][1] = ++c;
        if (c == n - 1)
        {
            r++;
            c = r;
        }
    }
    //print_matrix("UT map", m, 2, ut);
}

static void sort_ut(size_t n, int matrix[n][n])
{
    size_t m = (n * (n - 1)) / 2;
    size_t ut[m][2];
    init_ut_map(n, ut);

    for (size_t i = 0; i < m; i++)
    {
        size_t xi = ut[i][0];
        size_t yi = ut[i][1];
        for (size_t j = i + 1; j < m; j++)
        {
            size_t xj = ut[j][0];
            size_t yj = ut[j][1];
            if (cmp_dsc(matrix[xi][yi], matrix[xj][yj]) > 0)
            {
                int t = matrix[xi][yi];
                matrix[xi][yi] = matrix[xj][yj];
                matrix[xj][yj] = t;
            }
        }
    }
}

static void test_matrix(const char *tag, size_t n, int matrix[n][n])
{
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Matrix %s (%zux%zu) - before", tag, n, n);
    print_matrix(buffer, n, n, matrix);
    //print_matrix("Before sorting diagonal", n, n, matrix);
    sort_diagonal(n, matrix);
    //print_matrix("After sorting diagonal", n, n, matrix);
    sort_lt(n, matrix);
    //print_matrix("After sorting lower triangle", n, n, matrix);
    sort_ut(n, matrix);
    //print_matrix("After sorting upper triangle", n, n, matrix);
    snprintf(buffer, sizeof(buffer), "Matrix %s (%zux%zu) - after", tag, n, n);
    print_matrix(buffer, n, n, matrix);
}

int main(void)
{
    int matrix1[5][5] =
    {
        { 1, 5, 4, 7, 2 },
        { 4, 8, 5, 9, 0 },
        { 2, 7, 6, 5, 3 },
        { 3, 1, 7, 4, 9 },
        { 2, 5, 1, 7, 3 },
    };
    test_matrix("SAMPLE1", 5, matrix1);

    // gen_matrix -i -n matrix2 -r 10 -c 10 -L 10 -H 99
    int matrix2[10][10] =
    {
        { 87, 32, 98, 58, 60, 71, 46, 81, 70, 14, },
        { 22, 92, 15, 98, 51, 26, 94, 67, 46, 56, },
        { 71, 89, 86, 16, 20, 89, 97, 89, 45, 92, },
        { 63, 13, 76, 19, 75, 19, 66, 89, 58, 41, },
        { 82, 68, 75, 26, 58, 20, 89, 87, 65, 66, },
        { 74, 83, 68, 92, 10, 98, 90, 21, 39, 63, },
        { 24, 65, 23, 68, 62, 44, 48, 22, 27, 59, },
        { 26, 27, 71, 71, 51, 31, 43, 69, 92, 10, },
        { 54, 19, 41, 50, 10, 89, 42, 52, 94, 54, },
        { 42, 50, 79, 48, 77, 18, 29, 40, 61, 63, },
    };
    test_matrix("SAMPLE 2", 10, matrix2);

    return 0;
}
