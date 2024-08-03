/* SO 5630-7028 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

static unsigned int recarea(int x1, int y1, int x2, int y2)
{
    int area = 0;
    area = (x2 - x1) * (y2 - y1);
    return abs(area);
}

static unsigned int overarea(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int top = fmin(y2, y4);
    int bottom = fmax(y1, y3);
    int left = fmax(x1, x3);
    int right = fmin(x2, x4);
    int overlaparea = 0;
    if (bottom < top && left < right)
        overlaparea = recarea(left, bottom, right, top);
    return abs(overlaparea);
}

int main(void)
{
    int testcases = 0;
    scanf("%d", &testcases);
    for (int i = 0; i < testcases; i++)
    {
        int x1, x2, y1, y2, x3, x4, y3, y4;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        scanf("%d %d %d %d", &x3, &y3, &x4, &y4);
        int area = recarea(x1, y1, x2, y2) + recarea(x3, y3, x4, y4) -
                   overarea(x1, y1, x2, y2, x3, y3, x4, y4);
        printf("%d\n", area);
    }
    return 0;
}
