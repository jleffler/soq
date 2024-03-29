/* SO 7073-1987 */
/* Tridiagonal matrix */

/*
** NxN tri-diagonal matrix X
** Linearized in row-major order into array Y with 3i*N-2 entries 
** Linearized in column-major order into array Z with 3i*N-2 entries 
** Non-zero elements have c = r + { -1, 0, +1 }
** Equivalently they have r = c + { -1, 0, +1 }
** With one-based indexing, the first row with an element on the lower
** diagonal is r = 2 and the last row with an element on the upper
** diagonal is r = N - 1.
** With zero-based indexing, the first row with an element on the lower
** diagonal is r = 1 and the last rows with an element on the upper
** diagonal is r = N - 2.
** In the linearized vectors, the notation is:
** - D = diagonal, L = lower diagonal, U = upper diagonal
**
** Row-Major Order with Zero-Based Indexing
** ========================================
**
** X   c = 0   1   2   3   4   5
**       +----------------------
** r = 0 | 1   2   0   0   0   0
** r = 1 | 3   4   5   0   0   0
** r = 2 | 0   6   7   8   0   0
** r = 3 | 0   0   9  10  11   0
** r = 4 | 0   0   0  12  13  14
** r = 5 | 0   0   0   0  15  16
**
**        D  U  L  D  U  L  D  U  L  D  U  L  D  U  L D
** Y = {  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 }
** Index  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
**
** Elements on main  diagonal at indexes: 0, 3, 6, 9, 12, 15
** Elements on upper diagonal at indexes: 1, 4, 7, 10, 13
** Elements on lower diagonal at indexes: 2, 5, 8, 11, 14
**
** Function get_rm_0():
** X[r,c] = 0         if |r - c| > 1
** X[r,c] = 3 * r + 0 if r == c + 0     Main diagonal
** X[r,c] = 3 * r + 1 if r == c - 1     Upper diagonal
** X[r,c] = 3 * r - 1 if r == c + 1     Lower diagonal
** Always subject to 0 <= r < N; 0 <= c < N
**
** Row-Major Order with One-Based Indexing
** =======================================
**
** X   c = 1   2   3   4   5   6
**       +----------------------
** r = 1 | 1   2   0   0   0   0
** r = 2 | 3   4   5   0   0   0
** r = 3 | 0   6   7   8   0   0
** r = 4 | 0   0   9  10  11   0
** r = 5 | 0   0   0  12  13  14
** r = 6 | 0   0   0   0  15  16
**
**        D  U  L  D  U  L  D  U  L  D  U  L  D  U  L D
** Y = {  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 }
** Index  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
**
** Elements on main  diagonal at indexes: 1, 4, 7, 10, 13, 16
** Elements on upper diagonal at indexes: 2, 5, 8, 11, 14
** Elements on lower diagonal at indexes: 3, 6, 9, 12, 15
**
** Function get_rm_1():
** X[r,c] = 0         if |r - c| > 1
** X[r,c] = 3 * r - 2 if r == c + 0     Main diagonal
** X[r,c] = 3 * r - 1 if r == c - 1     Upper diagonal
** X[r,c] = 3 * r - 3 if r == c + 1     Lower diagonal
** Always subject to 0 < r <= N; 0 <= c <= N
**
** Column-major instead of row-major order
** =======================================
**
** >You are correct.  Here you are considering row-major order.  I
** >wanted to store the elements in the array as:
** >
** > Z = { 1, 3, 2, 4, 6, 5, 7, 9, 8, 10, 12, 11, 13, 15, 14, 16 }
** >
** >as per your example
**
** Column-Major Order with One-Based Indexing
** ==========================================
**
** So, you can make a parallel argument to the one I gave.  Annotate
** your column-major array Z similarly to the way I annotated the
** row-major array Y:
**
**        D   L   U   D   L   U   D   L   U   D   L   U   D   L   U   D
** Z = {  1,  3,  2,  4,  6,  5,  7,  9,  8, 10, 12, 11, 13, 15, 14, 16 }
** Index  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16
**
** Elements on main  diagonal at indexes: 1, 4, 7, 10, 13, 16
** Elements on upper diagonal at indexes: 3, 6, 9, 12, 15
** Elements on lower diagonal at indexes: 2, 5, 8, 11, 14
**
** Function get_cm_1():
** X[r,c] = 0         if |c - r| > 1
** X[r,c] = 3 * c - 2 if c == r + 0 Main diagonal
** X[r,c] = 3 * c - 3 if c == r + 1 Upper diagonal
** X[r,c] = 3 * c - 1 if c == r - 1 Lower diagonal
** Always subject to 0 < r <= N; 0 < c <= N.
**
** Column-Major Order with Zero-Based Indexing
** ===========================================
**
**        D   L   U   D   L   U   D   L   U   D   L   U   D   L   U   D
** Z = {  1,  3,  2,  4,  6,  5,  7,  9,  8, 10, 12, 11, 13, 15, 14, 16 }
** Index  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
**
** Elements on main  diagonal at indexes:  0,  3,  6,  9, 12, 15
** Elements on upper diagonal at indexes:  2,  5,  8, 11, 14
** Elements on lower diagonal at indexes:  1,  4,  7, 10, 13
**
** Function get_cm_0():
** X[r,c] = 0         if |c - r| > 1
** X[r,c] = 3 * c + 0 if c == r + 0 Main diagonal
** X[r,c] = 3 * c - 1 if c == r + 1 Upper diagonal
** X[r,c] = 3 * c + 1 if c == r - 1 Lower diagonal
** Always subject to 0 <= r < N; 0 <= c < N.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum { N = 6 };

static const int X[N][N] =
{
    {  1,  2,  0,  0,  0,  0 },
    {  3,  4,  5,  0,  0,  0 },
    {  0,  6,  7,  8,  0,  0 },
    {  0,  0,  9, 10, 11,  0 },
    {  0,  0,  0, 12, 13, 14 },
    {  0,  0,  0,  0, 15, 16 },
};

static const int Y[3*N-2] =
{
    1,  2,  3,  4,  5,  6,  7,  8,
    9, 10, 11, 12, 13, 14, 15, 16,
};

static const int Z[3*N-2] =
{
     1,  3,  2,  4,  6,  5,  7,  9,
     8, 10, 12, 11, 13, 15, 14, 16,
};

/* rm = row major, cm = column major, 0 = zero-based, 1 = one-based */

static int get_rm_0(int r, int c)
{
    assert(r >= 0 && r < N);
    assert(c >= 0 && c < N);
    //printf("%s(): r = %d, c = %d\n", __func__, r, c);
    if (abs(r - c) > 1)         /* Off tridiagonal */
        return 0;
    int index;
    if (r == c)                 /* Main diagonal */
        index = 3 * r + 0;
    else if (r == c - 1)        /* Upper diagonal */
        index = 3 * r + 1;
    else
    {
        assert(r == c + 1);
        index = 3 * r - 1;      /* Lower diagonal */
    }
    //printf("%s(): r = %d, c = %d, i = %d, v = %d\n", __func__, r, c, index, Y[index]);
    return Y[index];
}

static int get_rm_1(int r, int c)
{
    assert(r > 0 && r <= N);
    assert(c > 0 && c <= N);
    //printf("%s(): r = %d, c = %d\n", __func__, r, c);
    if (abs(r - c) > 1)         /* Off tridiagonal */
        return 0;
    int index;
    if (r == c)                 /* Main diagonal */
        index = 3 * r - 2;
    else if (r == c - 1)        /* Upper diagonal */
        index = 3 * r - 1;
    else
    {
        assert(r == c + 1);
        index = 3 * r - 3;      /* Lower diagonal */
    }
    //printf("%s(): r = %d, c = %d, i = %d, v = %d\n", __func__, r, c, index, Y[index-1]);
    return Y[index-1];
}

static int get_cm_0(int r, int c)
{
    assert(r >= 0 && r < N);
    assert(c >= 0 && c < N);
    //printf("%s(): r = %d, c = %d\n", __func__, r, c);
    if (abs(r - c) > 1)         /* Off tridiagonal */
        return 0;
    int index;
    if (c == r)                 /* Main diagonal */
        index = 3 * c + 0;
    else if (c == r + 1)        /* Upper diagonal */
        index = 3 * c - 1;
    else
    {
        assert(c == r - 1);
        index = 3 * c + 1;      /* Lower diagonal */
    }
    //printf("%s(): r = %d, c = %d, i = %d, v = %d\n", __func__, r, c, index, Z[index]);
    return Z[index];
}

static int get_cm_1(int r, int c)
{
    assert(r > 0 && r <= N);
    assert(c > 0 && c <= N);
    //printf("%s(): r = %d, c = %d\n", __func__, r, c);
    if (abs(r - c) > 1)         /* Off tridiagonal */
        return 0;
    int index;
    if (c == r)                 /* Main diagonal */
        index = 3 * c - 2;
    else if (c == r + 1)        /* Upper diagonal */
        index = 3 * c - 3;
    else
    {
        assert(c == r - 1);
        index = 3 * c - 1;      /* Lower diagonal */
    }
    //printf("%s(): r = %d, c = %d, i = %d, v = %d\n", __func__, r, c, index, Z[index-1]);
    return Z[index-1];
}

static void dump_matrix(const char *tag, int rows, int cols,
        const int matrix[rows][cols], int base)
{
    printf("%s (%dx%d) %d-based:\n", tag, rows, cols, base);
    printf("     c =");
    for (int c = 0; c < cols; c++)
        printf("  %2d", c + base);
    putchar('\n');
    for (int r = 0; r < rows; r++)
    {
        printf("r = %d: {", r + base);
        for (int c = 0; c < cols; c++)
            printf("  %2d", matrix[r][c]);
        puts(" }");
    }
    putchar('\n');
}

static void dump_vector(const char *tag, int values, const int vector[values], int base)
{
    printf("Vector %s (%d) %d-based:\n", tag, values, base);
    int len = 0;
    const char *pad = "";
    for (int i = 0; i < values; i++)
    {
        len += printf("%s[%2d] = %2d,", pad, i + base, vector[i]);
        pad = " ";
        if (len > 80)
        {
            putchar('\n');
            len = 0;
            pad = "";
        }
    }
    if (len > 0)
        putchar('\n');
    putchar('\n');
}

static void reconstruct_matrix(const char *matrix_tag, const char *vector_tag,
        int values, const int vector[values],
        int rows, int cols, int (*getter)(int r, int c), int base)
{
    dump_vector(vector_tag, values, vector, base);
    printf("%s (%dx%d) %d-based:\n", matrix_tag, rows, cols, base);
    for (int r = 0 + base; r < rows + base; r++)
    {
        printf("r = %d: {", r);
        for (int c = 0 + base; c < cols + base; c++)
            printf("  %2d", (*getter)(r, c));
        puts(" }");
    }
    putchar('\n');
}

int main(void)
{
    dump_matrix("Tridiagonal matrix X", N, N, X, 0);
    reconstruct_matrix("Reconstructed Row-Major Matrix", "Y", 3 * N - 2, Y, N, N, get_rm_0, 0);

    dump_matrix("Tridiagonal matrix X", N, N, X, 1);
    reconstruct_matrix("Reconstructed Row-Major Matrix", "Y", 3 * N - 2, Y, N, N, get_rm_1, 1);

    puts("\n\n");

    dump_matrix("Tridiagonal matrix X", N, N, X, 0);
    reconstruct_matrix("Reconstructed Column-Major Matrix", "Z", 3 * N - 2, Z, N, N, get_cm_0, 0);
    dump_matrix("Tridiagonal matrix X", N, N, X, 1);
    reconstruct_matrix("Reconstructed Column-Major Matrix", "Z", 3 * N - 2, Z, N, N, get_cm_1, 1);

    return 0;
}
