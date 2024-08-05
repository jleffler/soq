/* SO 7300-4773 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matmaxfldwid.h"

/* SBS - side-by-side data */
typedef struct SBS_Data
{
    size_t ncols;
    size_t nrows;
    char   ***data;
    size_t *maxw;
} SBS_Data;

static SBS_Data *sbs_create(size_t nrows, size_t ncols)
{
    SBS_Data *sbs = malloc(sizeof(*sbs));
    if (sbs == 0)
        return 0;
    sbs->data = malloc(nrows * sizeof(sbs->data[0]));
    if (sbs->data == 0)
    {
        free(sbs);
        return 0;
    }
    sbs->data[0] = calloc(ncols * nrows, sizeof(sbs->data[0][0]));
    if (sbs->data[0] == 0)
    {
        free(sbs->data);
        free(sbs);
        return 0;
    }
    for (size_t i = 1; i < nrows; i++)
        sbs->data[i] = sbs->data[0] + i * ncols;
    sbs->maxw = calloc(ncols, sizeof(size_t));
    if (sbs->maxw == 0)
    {
        free(sbs->data[0]);
        free(sbs->data);
        free(sbs);
        return 0;
    }
    sbs->ncols = ncols;
    sbs->nrows = nrows;
    return sbs;
}

static void sbs_destroy(SBS_Data *sbs)
{
    for (size_t r = 0; r < sbs->nrows; r++)
    {
        for (size_t c = 0; c < sbs->ncols; c++)
            free(sbs->data[r][c]);
    }
    free(sbs->maxw);
    free(sbs->data[0]);
    free(sbs->data);
    free(sbs);
}

static int sbs_add(SBS_Data *sbs, size_t row, size_t col, const char *str)
{
    //printf("%s(): SBS: nrows = %zu, ncols = %zu; row = %zu, col = %zu (str = [%s])\n", __func__, sbs->nrows, sbs->ncols, row, col, str);
    assert(row < sbs->nrows && col < sbs->ncols);
    assert(sbs->data[row][col] == 0);
    assert(strchr(str, '\n') == 0);
    if (!(row < sbs->nrows && col < sbs->ncols))
        return -1;
    if (!(sbs->data[row][col] == 0))
        return -1;
    if (!(strchr(str, '\n') == 0))
        return -1;
    sbs->data[row][col] = strdup(str);
    size_t len = strlen(sbs->data[row][col]);
    if (len > sbs->maxw[col])
        sbs->maxw[col] = len;
    return 0;
}

static void sbs_print(FILE *fp, SBS_Data *sbs, const char *gap)
{
    for (size_t r = 0; r < sbs->nrows; r++)
    {
        size_t c;
        const char *pad = "";
        for (c = 0; c < sbs->ncols - 1; c++)
        {
            int fldwid = (int)sbs->maxw[c];
            const char *fldstr = (sbs->data[r][c] == 0) ? "" : sbs->data[r][c];
            fprintf(fp, "%s%-*.*s", pad, fldwid, fldwid, fldstr);
            pad = gap;
        }
        const char *fldstr = (sbs->data[r][c] == 0) ? "" : sbs->data[r][c];
        fprintf(fp, "%s%-s", pad, fldstr);
        fputc('\n', fp);
    }
}

static int dump_sbs_matrix(SBS_Data *sbs, size_t sbs_col, const char *tag, size_t rows, size_t cols, int matrix[rows][cols])
{
    //printf("%s(): SBS: nrows = %zu, ncols = %zu: MTX: rows = %zu, cols = %zu\n", __func__, sbs->nrows, sbs->ncols, rows, cols);
    assert(sbs->ncols > sbs_col);
    assert(sbs->nrows == rows + 1);
    int fldwid = max_field_width(rows, cols, matrix);
    int rowwid = cols * fldwid + (cols - 1) + 1;
    int hdrwid = snprintf(0, 0, "%s (%zux%zu):", tag, rows, cols) + 1;
    size_t buflen = (rowwid > hdrwid) ? rowwid : hdrwid;
    char *buffer = malloc(buflen);
    if (buffer == 0)
        return -1;
    snprintf(buffer, buflen, "%s (%zux%zu):", tag, rows, cols);
    sbs_add(sbs, 0, sbs_col, buffer);
    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        size_t offset = 0;
        for (size_t c = 0; c < cols; c++)
        {
            int fldlen = snprintf(buffer + offset, buflen - offset, "%s%*d", pad, fldwid, matrix[r][c]);
            assert(fldlen > 0);
            offset += fldlen;
            pad = " ";
        }
        sbs_add(sbs, r + 1, sbs_col, buffer);
    }
    free(buffer);
    return 0;
}

static void count_matrix_v1(size_t rows, size_t cols, int matrix[rows][cols], int result[rows][cols])
{
    for (size_t c = 0; c < cols; c++)
    {
        for (size_t r = 0; r < rows; r++)
        {
            int value = matrix[r][c];
            int count = 0;
            for (size_t i = r + 1; i < rows; i++)
            {
                if (value >= matrix[i][c])
                    count++;
            }
            result[r][c] = count;
        }
    }
}

static void count_matrix_v2(size_t rows, size_t cols, int matrix[rows][cols], int result[rows][cols])
{
    for (size_t c = 0; c < cols; c++)
    {
        for (size_t r = 0; r < rows; r++)
        {
            int value = matrix[r][c];
            int count = 0;
            for (size_t i = 0; i < rows; i++)
            {
                if (value >= matrix[i][c])
                    count++;
            }
            result[r][c] = count - 1;
        }
    }
}

static void test_matrix(const char *name, size_t rows, size_t cols, int matrix[rows][cols])
{
    int result[rows][cols];
    SBS_Data *sbs = sbs_create(rows + 1, 3);

    dump_sbs_matrix(sbs, 0, name, rows, cols, matrix);
    count_matrix_v1(rows, cols, matrix, result);
    dump_sbs_matrix(sbs, 1, "Result1", rows, cols, result);
    count_matrix_v2(rows, cols, matrix, result);
    dump_sbs_matrix(sbs, 2, "Result2", rows, cols, result);
    sbs_print(stdout, sbs, "    ");
    sbs_destroy(sbs);
    putchar('\n');
}

int main(void)
{
    /* Created by: gen_matrix -n N -L -99 -H +99 -r 5 -c 6 -E -w 3 -i */
    /* Random seed: 0x8E280D99 */
    int N[5][6] =
    {
        {  79, -40,  52,  26, -35,  86, },
        { -68,  13,  21, -34,  -9,  10, },
        {   7,  72,  68,  44,  45,  -3, },
        {  25,  78,  86,  81,  51, -33, },
        { -38, -89,  42,  61, -24,  69, },
    };
    enum { N_ROWS = 5, N_COLS = 6 };
    test_matrix("N", N_ROWS, N_COLS, N);

    /* Created by: gen_matrix -n matrix1 -L -9 -H +9 -r 8 -c 6 -E -w 2 -i */
    /* Random seed: 0x00B6E0F7 */
    int matrix1[8][6] =
    {
        { -3, -5,  5, -4,  7,  9, },
        {  9,  9, -9, -2,  4, -3, },
        {  2,  5, -8,  9, -7, -5, },
        {  5, -9, -5,  8,  2,  2, },
        {  5,  2, -5, -9,  4, -5, },
        {  1, -5, -3, -2,  4,  5, },
        {  8,  5,  3, -2,  1,  9, },
        {  4,  3,  2,  2,  9, -1, },
    };
    enum { MATRIX1_ROWS = 8, MATRIX1_COLS = 6 };
    test_matrix("Matrix 1", MATRIX1_ROWS, MATRIX1_COLS, matrix1);

    int M[2][2] =
    {
        {4, 6},
        {9, 2},
    };
    test_matrix("M", 2, 2, M);

    /* Created by: gen_matrix -n matrix2 -L -9999 -H +9999 -r 4 -c 3 -E -w 5 -i */
    /* Random seed: 0x75DCF407 */
    int matrix2[4][3] =
    {
        {  8008, -6894, -4062, },
        {  7755,  2443,  3067, },
        {   820, -1761, -9612, },
        {  -118, -6303, -2996, },
    };
    enum { MATRIX2_ROWS = 4, MATRIX2_COLS = 3 };
    test_matrix("Matrix 2", MATRIX2_ROWS, MATRIX2_COLS, matrix2);

    /* Created by: gen_matrix -n matrix3 -L -99 -H +99 -r 4 -c 4 -E -w 3 -i */
    /* Random seed: 0x313942FA */
    int matrix3[4][4] =
    {
        { -76, -85,  85, -77, },
        {  -2,  65,  68, -53, },
        { -26, -14,  60,  28, },
        { -86,  73, -16,  64, },
    };
    enum { MATRIX3_ROWS = 4, MATRIX3_COLS = 4 };
    test_matrix("Matrix 3", MATRIX3_ROWS, MATRIX3_COLS, matrix3);

    return 0;
}
