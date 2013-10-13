/* Code for http://stackoverflow.com/q/18801547 Transform matrix 2D to 1D */

/* Creating a semi-encapsulated interface for this code */

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct RC
{
    int row;
    int col;
} RC;

typedef struct RLE
{
    RC  curr;
    RC  size;
    int zigzag;
    int sequence;
} RLE;

static inline int max(int a, int b) { return (a > b) ? a : b; }
static inline int min(int a, int b) { return (a < b) ? a : b; }

static inline int get_num_zigzags(const RLE *rle)
{
    return rle->size.row + rle->size.col - 1;
}

static inline int get_max_row(const RLE *rle)
{
    return min(rle->zigzag, rle->size.row - 1);
}

static inline int get_min_row(const RLE *rle)
{
    return max(0, rle->zigzag - get_num_zigzags(rle) + rle->size.row);
}

static inline int get_max_col(const RLE *rle)
{
    return min(rle->zigzag, rle->size.col - 1);
}

static inline int get_min_col(const RLE *rle)
{
    return max(0, rle->zigzag - get_num_zigzags(rle) + rle->size.col);
}

static inline int get_row_from_col(const RLE *rle)
{
    return rle->zigzag - rle->curr.col;
}

static inline int get_col_from_row(const RLE *rle)
{
    return rle->zigzag - rle->curr.row;
}

static RLE RLE_init(int rows, int cols)
{
    RLE rle;
    assert(rows > 0 && cols > 0);
    assert(INT_MAX / rows >= cols);
    rle.curr.row = 0;
    rle.curr.col = 0;
    rle.size.row = rows;
    rle.size.col = cols;
    rle.zigzag = 0;
    rle.sequence = 0;
    return(rle);
}

static inline RC RLE_position(const RLE *rle)
{
    return rle->curr;
}

static inline int RLE_row(const RLE *rle)
{
    return rle->curr.row;
}

static inline int RLE_col(const RLE *rle)
{
    return rle->curr.col;
}

static inline int RLE_sequence(const RLE *rle)
{
    return rle->sequence;
}

static inline int RLE_zigzag(const RLE *rle)
{
    return rle->zigzag;
}

static inline RC RLE_size(const RLE *rle)
{
    return rle->size;
}

static inline bool RLE_finished(const RLE *rle)
{
    return(rle->sequence == rle->size.row * rle->size.col);
}

static void RLE_check(const RLE *rle)
{
    assert(rle->size.row > 0);
    assert(rle->size.col > 0);
    assert(rle->curr.row < rle->size.row && rle->curr.row >= 0);
    assert(rle->curr.col < rle->size.col && rle->curr.col >= 0);
    assert(rle->zigzag >= 0 && rle->zigzag < rle->size.row + rle->size.col - 1);
    assert(rle->sequence >= 0 && rle->sequence <= rle->size.row * rle->size.col);
}

#if defined(REL_DUMP_REQUIRED)
static void RLE_dump(const char *tag, const RLE *rle)
{
    printf("Dump RLE (%s):", tag);
    RC size = RLE_size(rle);
    assert(size.row == rle->size.row);
    assert(size.col == rle->size.col);
    printf("    Rows = %2d, Cols = %2d, Zigzags = %2d; ",
           rle->size.row, rle->size.col, rle->size.row + rle->size.col - 1);
    RC posn = RLE_position(rle);
    assert(posn.row == rle->curr.row);
    assert(posn.col == rle->curr.col);
    assert(posn.row == RLE_row(rle));
    assert(posn.col == RLE_col(rle));
    printf(" Position: r = %d, c = %d; ", RLE_row(rle), RLE_col(rle));
    assert(RLE_zigzag(rle) == rle->zigzag);
    assert(RLE_sequence(rle) == rle->sequence);
    printf(" Zigzag = %d, Sequence = %d\n", rle->zigzag, rle->sequence);
    RLE_check(rle);
}
#endif

static void RLE_next(RLE *rle)
{
    RLE_check(rle);

    /* Already finished? */
    if (RLE_finished(rle))
        return;
    rle->sequence++;
    /* Finished now? */
    if (RLE_finished(rle))
        return;

    if (rle->zigzag % 2 == 0)
    {
        if (rle->curr.col < get_max_col(rle))
        {
            /* Same zigzag */
            rle->curr.col++;
            rle->curr.row = get_row_from_col(rle);
        }
        else
        {
            /* Next zigzag */
            rle->zigzag++;
            rle->curr.row = get_min_row(rle);
            rle->curr.col = get_col_from_row(rle);
        }
    }
    else
    {
        if (rle->curr.row < get_max_row(rle))
        {
            /* Same zigzag */
            rle->curr.row++;
            rle->curr.col = get_col_from_row(rle);
        }
        else
        {
            /* Next zigzag */
            rle->zigzag++;
            rle->curr.col = get_min_col(rle);
            rle->curr.row = get_row_from_col(rle);
        }
    }
}

static void print_info(int rows, int cols)
{
    int n = rows + cols - 1;
    printf("R = %d, C = %d, N = %d\n", rows, cols, n);

    for (int zigzag = 0; zigzag < n; zigzag++)
    {
        int max_col = min(zigzag, cols-1);
        int min_col = max(0, zigzag - n + cols);
        int max_row = min(zigzag, rows-1);
        int min_row = max(0, zigzag - n + rows);
        printf("zigzag = %2d, min_col = %2d, max_col = %2d, min_row = %2d, max_row = %2d\n",
                zigzag, min_col, max_col, min_row, max_row);
    }

    for (int zigzag = 0; zigzag < n; zigzag++)
    {
        printf("%d:", zigzag);
        if (zigzag % 2 == 0)
        {
            int max_col = min(zigzag, cols-1);
            int min_col = max(0, zigzag - n + cols);
            for (int col = min_col; col <= max_col; col++)
                /* (row,col) */
                printf(" (r=%d,c=%d)", zigzag - col, col);
        }
        else
        {
            int max_row = min(zigzag, rows-1);
            int min_row = max(0, zigzag - n + rows);
            for (int row = min_row; row <= max_row; row++)
                printf(" (r=%d,c=%d)", row, zigzag - row);
        }
        putchar('\n');
    }
}

static void dump_matrix(const char *tag, int rows, int cols, int matrix[rows][cols])
{
    printf("%s (%d x %d):\n", tag, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%3d", matrix[i][j]);
        putchar('\n');
    }
}

static void dump_vector(const char *tag, int rows, int cols, int vector[rows * cols])
{
    printf("%s (%d : %d):\n", tag, rows, cols);
    for (int i = 0; i < rows * cols; i++)
    {
        printf("%3d", vector[i]);
        if (i % cols == cols - 1)
            putchar('\n');
    }
}

static void RLE_demonstration(int rows, int cols)
{
    int matrix[rows][cols];
    int vector[rows*cols];

    /* Set matrix */
    for (RLE rle = RLE_init(rows, cols); !RLE_finished(&rle); RLE_next(&rle))
    {
        //RLE_dump("Set Matrix", &rle);
        RC rc = RLE_position(&rle); 
        matrix[rc.row][rc.col] = RLE_sequence(&rle);
    }
    dump_matrix("Matrix", rows, cols, matrix);

    /* Convert matrix to vector */
    for (RLE rle = RLE_init(rows, cols); !RLE_finished(&rle); RLE_next(&rle))
    {
        //RLE_dump("Get Matrix", &rle);
        RC rc = RLE_position(&rle); 
        vector[RLE_sequence(&rle)] = matrix[rc.row][rc.col];
    }
    dump_vector("Vector", rows, cols, vector);
}

int main(int argc, char **argv)
{
    struct
    {
        int rows;
        int cols;
    } test[] =
    {
        { 4, 4 }, { 6, 4 },  { 4, 7 }, { 7, 14 }, { 6, 16 }, { 3, 33 },
    };
    enum { NUM_TEST = sizeof(test) / sizeof(test[0]) };

    /* argv != 0 avoids unused variable warning */
    int verbose = (argv != 0 && argc > 1) ? 1 : 0;

    for (int i = 0; i < NUM_TEST; i++)
    {
        if (verbose)
            print_info(test[i].rows, test[i].cols);
        RLE_demonstration(test[i].rows, test[i].cols);
    }

    return 0;
}
