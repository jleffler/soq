/* SO 5630-7028 */
/* Adapation of overlap73.c with configurable data type and range checking */

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

typedef long long Data;
#define PRI_DATA "lld"
#define SCN_DATA "lld"

typedef struct Point
{
    Data x;
    Data y;
} Point;

typedef struct Box
{
    struct Point bl;
    struct Point tr;
} Box;

static noreturn void err_exit(const char *fmt, ...);

static inline Data min_data(Data i, Data j) { return (i < j) ? i : j; }
static inline Data max_data(Data i, Data j) { return (i > j) ? i : j; }
static inline Data abs_data(Data i) { return (i >= 0) ? i : -i; }
static inline void swap(Data *a, Data *b) { Data c = *a; *a = *b; *b = c; }

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

static inline Data box_area(Box box)
{
    assert(box_is_normal(box));
    Data area = (box.tr.x - box.bl.x) * (box.tr.y - box.bl.y);
    return area;
}

static Data box_area_overlap(const Box *b1, const Box *b2)
{
    Box b0 =
    {
        .bl = { .x = max_data(b1->bl.x, b2->bl.x), .y = max_data(b1->bl.y, b2->bl.y) },
        .tr = { .x = min_data(b1->tr.x, b2->tr.x), .y = min_data(b1->tr.y, b2->tr.y) },
    };
    Data area = 0;
    if (box_is_normal(b0))
        area = box_area(b0);
    return area;
}

static inline void box_print(Box b)
{
    printf("[(%" PRI_DATA ",%" PRI_DATA "),(%" PRI_DATA ",%" PRI_DATA ")]",
           b.bl.x, b.bl.y, b.tr.x, b.tr.y);
}

static Data recarea(Data x1, Data y1, Data x2, Data y2)
{
    Data area = (x2 - x1) * (y2 - y1);
    return abs_data(area);
}

static Data overarea(Data x1, Data y1, Data x2, Data y2, Data x3, Data y3, Data x4, Data y4)
{
    Data top = min_data(y2, y4);
    Data bottom = max_data(y1, y3);
    Data left = max_data(x1, x3);
    Data right = min_data(x2, x4);
    Data overlaparea = 0;
    if (bottom < top && left < right)
        overlaparea = recarea(left, bottom, right, top);
    return abs_data(overlaparea);
}

enum { MIN_COORD = -999999, MAX_COORD = 1000000 };

static void check_coord(const char *tag, Data coord)
{
    if (coord < MIN_COORD || coord > MAX_COORD)
        err_exit("%s coordinate %" PRI_DATA " out of range [%d..%d]\n",
                 tag, coord, MIN_COORD, MAX_COORD);
}

static void check_data(Data x1, Data y1, Data x2, Data y2)
{
    check_coord("XBL", x1);
    check_coord("YBL", y1);
    check_coord("XTR", x2);
    check_coord("YTR", y2);
    if (x1 >= x2 || y1 >= y2)
        {
        err_exit("[(%" PRI_DATA ",%" PRI_DATA ") >= (%" PRI_DATA ",%" PRI_DATA ")]\n",
                 x1, y1, x2, y2);
        }
}

int main(void)
{
    int testcases = 0;
    if (scanf("%d", &testcases) != 1)
        err_exit("failed to read number of test cases\n");
    for (int i = 0; i < testcases; i++)
    {
        Data x1, x2, y1, y2, x3, x4, y3, y4;
        if (scanf("%" SCN_DATA " %" SCN_DATA " %" SCN_DATA " %" SCN_DATA "",
                 &x1, &y1, &x2, &y2) != 4)
            err_exit("failed to read first box\n");
        check_data(x1, y1, x2, y2);
        if (scanf("%" SCN_DATA " %" SCN_DATA " %" SCN_DATA " %" SCN_DATA "",
                  &x3, &y3, &x4, &y4) != 4)
            err_exit("failed to read second box\n");
        check_data(x3, y3, x4, y4);
        Data area = recarea(x1, y1, x2, y2) + recarea(x3, y3, x4, y4) -
                   overarea(x1, y1, x2, y2, x3, y3, x4, y4);
        printf("%" PRI_DATA "\n", area);

        Box b1 = { .bl = { .x = x1, .y = y1 }, .tr = { .x = x2, .y = y2 } };
        Box b2 = { .bl = { .x = x3, .y = y3 }, .tr = { .x = x4, .y = y4 } };
        box_normalize(&b1);
        box_normalize(&b2);
        Data a1 = box_area(b1);
        Data a2 = box_area(b2);
        Data o1 = box_area_overlap(&b1, &b2);    // Inconsistency with box_area()!
        
        printf("B1: ");
        box_print(b1);
        printf(", B2: ");
        box_print(b2);
        putchar('\n');
        printf("A1 = %" PRI_DATA "; A2 = %" PRI_DATA "; overlap = %" PRI_DATA "; total area = %" PRI_DATA "\n",
                a1, a2, o1, a1 + a2 - o1);
    }
    return 0;
}

static noreturn void err_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
