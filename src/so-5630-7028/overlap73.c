/* SO 5630-7028 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

typedef struct Point
{
    int x;
    int y;
} Point;

typedef struct Box
{
    struct Point bl;
    struct Point tr;
} Box;

static noreturn void err_exit(const char *s);

static inline int min(int i, int j) { return (i < j) ? i : j; }
static inline int max(int i, int j) { return (i > j) ? i : j; }
static inline void swap(int *a, int *b) { int c = *a; *a = *b; *b = c; }

static inline void box_normalize(Box *box)
{
    if (box->bl.x > box->tr.x)
        swap(&box->bl.x, &box->tr.x);
    if (box->bl.y > box->tr.y)
        swap(&box->bl.y, &box->tr.y);
}

static inline bool box_is_normal(Box box)
{
    if (box.bl.x > box.tr.x)
        return false;
    if (box.bl.y > box.tr.y)
        return false;
    return true;
}

static inline int box_area(Box box)
{
    assert(box_is_normal(box));
    int area = (box.tr.x - box.bl.x) * (box.tr.y - box.bl.y);
    return area;
}

static int box_area_overlap(const Box *b1, const Box *b2)
{
    Box b0 =
    {
        .bl = { .x = max(b1->bl.x, b2->bl.x), .y = max(b1->bl.y, b2->bl.y) },
        .tr = { .x = min(b1->tr.x, b2->tr.x), .y = min(b1->tr.y, b2->tr.y) },
    };
    int area = 0;
    if (box_is_normal(b0))
        area = box_area(b0);
    return area;
}

static inline void box_print(Box b)
{
    printf("[(%d,%d),(%d,%d)]", b.bl.x, b.bl.y, b.tr.x, b.tr.y);
}

static int recarea(int x1, int y1, int x2, int y2)
{
    int area = (x2 - x1) * (y2 - y1);
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

        Box b1 = { .bl = { .x = x1, .y = y1 }, .tr = { .x = x2, .y = y2 } };
        Box b2 = { .bl = { .x = x3, .y = y3 }, .tr = { .x = x4, .y = y4 } };
        box_normalize(&b1);
        box_normalize(&b2);
        int a1 = box_area(b1);
        int a2 = box_area(b2);
        int o1 = box_area_overlap(&b1, &b2);    // Inconsistency with box_area()!
        
        printf("B1: ");
        box_print(b1);
        printf(", B2: ");
        box_print(b2);
        putchar('\n');
        printf("A1 = %d; A2 = %d; overlap = %d; total area = %d\n",
                a1, a2, o1, a1 + a2 - o1);
    }
    return 0;
}

static noreturn void err_exit(const char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(EXIT_FAILURE);
}
