/* SO 7918-2426 */

/*
**  Given matrix with rows = 5, cols = 6, r0 = 1, c0 = 4, the expected sequence is:
**  
**  [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
**  
**  
**  
**                   X   X   X   X   X   X   X   X
**  
**                   X   X   X   X   X   X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | O | X | X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X   X   X
**             +---+---+---+---+---+---+
**               X   X   X   X   X   X   X   X   X
**  
**  
**  
**  
**                   X   X   X   X   X   X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | O | X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X
**             +---+---+---+---+---+---+
**             | X | X | X | X | X | X | X
**             +---+---+---+---+---+---+
**               X   X   X   X   X   X   X
**  
**  
**  How many loops in the spiral?
**  Is it the max of:
**  - Distance from start to left edge
**  - Distance from start to right edge
**  - Distance from start to top edge
**  - Distance from start to bottom edge?
**  
**  Do you need to keep a matrix initialized to zero, with ones set when you traverse the square?
**  Or can you determine when you're done without that?
**  - Count the number of corners visited
**  - Stop on reaching the fourth?
**  - Probably too simplistic.
**  
**  The spiral always takes the form:
**  
**  
**                   42  43  44  45  46  47  48  49
**  
**                   41  20  21  22  23  24  25  50
**             +===+===+===+===+===+===+
**             | 69| 40| 19| 6 | 7 | 8 | 9   26  51
**             +---+---+---+---+---+---+
**             | 68| 39| 18| 5 | O | 1 | 10  27  52
**             +---+---+---+---+---+---+
**             | 67| 38| 17| 4 | 3 | 2 | 11  28  53
**             +---+---+---+---+---+---+
**             | 66| 37| 16| 15| 14| 13| 12  29  54
**             +---+---+---+---+---+---+
**             | 65| 36| 35| 34| 33| 32| 31  30  55
**             +===+===+===+===+===+===+
**               64  63  62  61  60  59  58  57  56
**  
**  
**  
**                   42  43  44  45  46  47  48  49
**  
**                   41  20  21  22  23  24  25  50
**  
**                   40  19  6   7   8   9   26  51
**             +---+---+---+---+---+---+
**             | 68| 39| 18| 5 | 0 | 1 | 10  27  52
**             +---+---+---+---+---+---+
**             | 67| 38| 17| 4 | 3 | 2 | 11  28  53
**             +---+---+---+---+---+---+
**             | 66| 37| 16| 15| 14| 13| 12  29  54
**             +---+---+---+---+---+---+
**             | 65| 36| 35| 34| 33| 32| 31  30  55
**             +---+---+---+---+---+---+
**             | 64| 63| 62| 61| 60| 59| 58  57  56
**             +---+---+---+---+---+---+
*/

#include <assert.h>
#include <stdio.h>

const int rstart = 1;
const int cstart = 4;
const int rows = 5;
const int cols = 6;

struct Position
{
    int row;
    int col;
};
enum { LEFT, RIGHT, UP, DOWN };

static char dirname(int dir)
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

int main(void)
{
    struct Position array[rows * cols];
    int next = 0;

    int corners_visited = 0;
    int r = rstart;
    int c = cstart;
    assert(r >= 0 && r < rows && c >= 0 && c < cols);

    const int tlr = 0;          /* Top Left Row */
    const int tlc = 0;          /* Top Left Col */
    const int trr = 0;          /* Top Right Row */
    const int trc = cols - 1;   /* Top Right Col */
    const int blr = rows - 1;   /* Bottom Left Row */
    const int blc = 0;          /* Bottom Left Col */
    const int brr = rows - 1;   /* Bottom Right Row */
    const int brc = cols - 1;   /* Bottom Right Col */

    /* Record new position */
    if (r >= 0 && r < rows && c >= 0 && c < cols)
    {
        array[next].row = r;
        array[next].col = c;
        next++;
        if ((r == tlr && c == tlc) || (r == blr && c == blc) ||
            (r == trr && c == trc) || (r == brr && c == brc))
            corners_visited++;
    }

    int n_steps = 1;
    int dir = RIGHT;
    int steps = 0;

    printf("r = %d, c = %d recorded", r, c);
    printf(" corners = %d", corners_visited);
    printf(" n_steps = %d, steps = %d, dir = %c\n", n_steps, steps, dirname(dir));

    while (corners_visited != 4)
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
        printf("r = %d, c = %d", r, c);

        /* Record new position */
        /* Horrid repetition! */
        if (r >= 0 && r < rows && c >= 0 && c < cols)
        {
            array[next].row = r;
            array[next].col = c;
            next++;
            printf(" recorded");
            if ((r == tlr && c == tlc) || (r == blr && c == blc) ||
                (r == trr && c == trc) || (r == brr && c == brc))
            {
                corners_visited++;
                printf(" corners = %d", corners_visited);
            }
        }

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
            printf(" n_steps = %d, steps = %d, dir = %c", n_steps, steps, dirname(dir));
            steps = 0;
        }
        assert(steps < n_steps && steps >= 0);
        putchar('\n');
    }

    /* Print sequence (though we could print as we go!) */
    assert(next == rows * cols);
    for (size_t i = 0; i < rows * cols; i++)
    {
        printf("[%d,%d]", array[i].row, array[i].col);
    }
    putchar('\n');

    return 0;
}
