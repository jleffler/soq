/* Code for https://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

#include <stdio.h>

static inline int max(int a, int b) { return ((a) > (b) ? (a) : (b)); }
static inline int min(int a, int b) { return ((a) < (b) ? (a) : (b)); }

void dezigzag(int rows, int cols, int out[rows * cols], int in[rows][cols]);

void dezigzag(int rows, int cols, int out[rows * cols], int in[rows][cols])
{
    int n = 0;
    for (int diag = 0; diag < (rows + cols - 1); diag++)
    {
        for (int i = max(0, diag - (rows - 1)); i <= min(cols - 1, diag); i++)
        {
            int x = diag % 2 == 0 ? i      : diag-i;
            int y = diag % 2 == 0 ? diag-i : i;
            printf("v[%2d] = m[%d][%d] = %2d (D = %2d)\n", n, y, x, in[y][x], diag);
            out[n++] = diag % 2 == 0 ? in[diag - i][i] : in[i][diag - i];
        }
    }
}

void fonc(int tab2[3][4], int vect[3 * 4]);

void fonc(int tab2[3][4], int vect[3 * 4])
{
    static const struct ZigZag
    {
        unsigned char y, x;
    } zigzag[3*4] =
    {
        { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 2 },
        { 1, 1 }, { 2, 0 }, { 3, 0 }, { 2, 1 },
        { 1, 2 }, { 2, 2 }, { 3, 1 }, { 3, 2 },
    };

    for (int i = 0; i < 3*4; i++)
        vect[i] = tab2[zigzag[i].x][zigzag[i].y];
}

static void dump_vector(int rows, int cols, int vector[rows * cols])
{
    puts("Vector:");
    int limit = rows * cols;
    for (int i = 0; i < limit; i++)
    {
        printf("%3d", vector[i]);
        if (i % cols == cols - 1)
            putchar('\n');
    }
}

static void dump_matrix(int rows, int cols, int matrix[rows][cols])
{
    puts("Matrix:");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%3d", matrix[i][j]);
        putchar('\n');
    }
}

int main(void)
{

    if (1)
    {
    enum { ROWS = 3, COLS = 4 };
    int matrix[ROWS][COLS] =
    {
        {  1,  2,  6,  7, },
        {  3,  5,  8, 11, },
        {  4,  9, 10, 12, },
    };
    int vector[ROWS*COLS];

    dump_matrix(ROWS, COLS, matrix);
    dezigzag(ROWS, COLS, vector, matrix);
    dump_vector(ROWS, COLS, vector);
    }

    if (1)
    {
    enum { ROWS = 4, COLS = 4 };
    int matrix[ROWS][COLS] =
    {
        {  1,  2,  6,  7, },
        {  3,  5,  8, 13, },
        {  4,  9, 12, 14, },
        { 10, 11, 15, 16, },
    };
    int vector[ROWS*COLS];

    dump_matrix(ROWS, COLS, matrix);
    dezigzag(ROWS, COLS, vector, matrix);
    dump_vector(ROWS, COLS, vector);
    }

    if (0)
    {
    enum { ROWS = 3, COLS = 4 };
    int matrix[ROWS][COLS] =
    {
        {  1,  2,  6,  7, },
        {  3,  5,  8, 11, },
        {  4,  9, 10, 12, },
    };
    int vector[ROWS*COLS];

    dump_matrix(ROWS, COLS, matrix);
    fonc(matrix, vector);
    dump_vector(ROWS, COLS, vector);
    }

    if (0)
    {
    int out[64] = {-1};
    int in[8][8];

    for (int i = 0; i < 64; i++)
        in[i % 8][i / 8] = i;

    dump_matrix(8, 8, in);
    dezigzag(8, 8, out, in);
    dump_vector(8, 8, out);
    }

    if (0)
    {
    int out[64] = {-1};
    int tab2[8][8] =
    {
        {  1,  2,  6,  7, 15, 16, 28, 29 },
        {  3,  5,  8, 14, 17, 27, 30, 43 },
        {  4,  9, 13, 18, 26, 31, 42, 44 },
        { 10, 12, 19, 25, 32, 41, 45, 54 },
        { 11, 20, 24, 33, 40, 46, 53, 55 },
        { 21, 23, 34, 39, 47, 52, 56, 61 },
        { 22, 35, 38, 48, 51, 57, 60, 62 },
        { 36, 37, 49, 50, 58, 59, 63, 64 },
    };

    dump_matrix(8, 8, tab2);
    dezigzag(8, 8, out, tab2);
    dump_vector(8, 8, out);
    }

    return 0;
}
