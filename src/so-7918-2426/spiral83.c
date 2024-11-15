/* SO 7918-2426 */

/*
**  Given a matrix with rows = 5, cols = 6, r0 = 1, c0 = 4, the expected sequence is:
**
**  [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],
**   [3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],
**   [0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
**
**  Given a matrix with rows = 1, cols = 4, r0 = 0, c0 = 0, the expected sequence is:
**
**  [[0,0],[0,1],[0,2],[0,3]]
*/

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

struct Position
{
    int row;
    int col;
};
enum Direction { LEFT, RIGHT, UP, DOWN };

struct Control
{
    int rows;               /* Number of rows in matrix */
    int cols;               /* Number of columns in matrix */
    int count;              /* Number of cells in matrix */
    int next;               /* Index into array of cells visited */
    struct Position *posn;  /* Array for recording cells visited */ 
};

const int debug = 0;

static void dbg_printf(const char *fmt, ...)
{
    if (debug)
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

static inline char dirname(int dir)
{
    switch (dir)
    {
    case RIGHT: return 'R';
    case LEFT:  return 'L';
    case UP:    return 'U';
    case DOWN:  return 'D';
    default:    assert(0);
    }
}

/* Record new position */
static void record(int r, int c, struct Control *ctrl)
{
    dbg_printf("r = %d, c = %d", r, c);
    if (r >= 0 && r < ctrl->rows && c >= 0 && c < ctrl->cols)
    {
        ctrl->posn[ctrl->next].row = r;
        ctrl->posn[ctrl->next].col = c;
        ctrl->next++;
        dbg_printf(" recorded");
    }
}

static void spiral(int rows, int cols, int rstart, int cstart)
{
    struct Position array[rows * cols];

    struct Control ctrl =
    {
        .rows = rows,
        .cols = cols,
        .next = 0,
        .count = rows * cols,
        .posn = array,
    };

    int r = rstart;
    int c = cstart;
    assert(r >= 0 && r < rows && c >= 0 && c < cols);

    int n_steps = 1;
    int dir = RIGHT;
    int steps = 0;

    record(r, c, &ctrl);
    dbg_printf(" n_steps = %d, steps = %d, dir = %c\n", n_steps, steps, dirname(dir));

    while (ctrl.next != ctrl.count)
    {
        /* Move */
        switch (dir)
        {
            case RIGHT: c++; break;
            case LEFT:  c--; break;
            case UP:    r--; break;
            case DOWN:  r++; break;
            default:    assert(0);
        }

        record(r, c, &ctrl);

        if (++steps == n_steps)
        {
            /* Change length */
            if (dir == DOWN || dir == UP)
                n_steps++;
            /* Change direction */
            switch (dir)
            {
                case RIGHT: dir = DOWN;  break;
                case LEFT:  dir = UP;    break;
                case UP:    dir = RIGHT; break;
                case DOWN:  dir = LEFT;  break;
                default:    assert(0);
            }
            dbg_printf(" n_steps = %d, steps = %d, dir = %c", n_steps, steps, dirname(dir));
            steps = 0;
        }
        assert(steps < n_steps && steps >= 0);
        dbg_printf("\n");
    }

    /* Print sequence (though we could print as we go!) */
    assert(ctrl.next == rows * cols);
    printf("rows = %d, cols = %d, r0 = %d, c0 = %d:\n[", rows, cols, rstart, cstart);
    const char *pad = "";
    for (int i = 0; i < rows * cols; i++)
    {
        printf("%s[%d,%d]", pad, array[i].row, array[i].col);
        pad = ",";
    }
    printf("]\n");
}

int main(void)
{
    spiral(5, 6, 1, 4);
    spiral(1, 4, 0, 0);
    spiral(5, 1, 2, 0);
    spiral(1, 1, 0, 0);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
            spiral(5, 6, i, j);
    }

    return 0;
}
