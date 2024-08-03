/* SO 5630-7028 */

#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

/*
** NB: The original code used fmin() and fmax() from <math.h>, but doing
** so is dubious, yet there aren't standard integer functions for the
** job.  Hence, use static inline functions devised on the fly.
**
** It seems likely that using a struct Point { int x; int y; }; and
** struct Box { struct Point bl; struct Point tr; }; would be a good
** idea; it would reduce the length of the argument lists, at least.
** That said, maybe the names bl and tr are misnomers; there'd not be a
** problem if the bl member held the tl, br, or tr corner, etc, as long
** as the other member held the opposite corner of the box.  Of course,
** the structure could be normalized so bl.x <= tr.x && bl.y <= tr.y and
** so on.  Further, it would be feasible to swap either the
** x-coordinates or the y-coordinates or both.
*/

static inline int min(int i, int j) { return (i < j) ? i : j; }
static inline int max(int i, int j) { return (i > j) ? i : j; }
static noreturn void err_exit(const char *s);

static unsigned int recarea(int x1, int y1, int x2, int y2)
{
    int area = 0;
    area = (x2 - x1) * (y2 - y1);
    return abs(area);
}

static int overarea(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int top = min(y2, y4);
    int bottom = max(y1, y3);
    int left = max(x1, x3);
    int right = min(x2, x4);
    int overlaparea = 0;
    if (bottom < top && left < right)
        overlaparea = recarea(left, bottom, right, top);
    return abs(overlaparea);
}

int main(void)
{
    int testcases = 0;
    if (scanf("%d", &testcases) != 1)
        err_exit("failed to read number of test cases");
    for (int i = 0; i < testcases; i++)
    {
        int x1, x2, y1, y2, x3, x4, y3, y4;
        if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4)
            err_exit("failed to read first box");
        if (scanf("%d %d %d %d", &x3, &y3, &x4, &y4) != 4)
            err_exit("failed to read second box");
        int area = recarea(x1, y1, x2, y2) + recarea(x3, y3, x4, y4) -
                   overarea(x1, y1, x2, y2, x3, y3, x4, y4);
        printf("%d\n", area);
    }
    return 0;
}

static noreturn void err_exit(const char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(EXIT_FAILURE);
}
