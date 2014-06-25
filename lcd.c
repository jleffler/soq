/* SO 24233419 - 12-segment LCD digits */
/* Assuming no structures - simplifying assignment to display[y][x] */
#include <stdio.h>
#include <string.h>

enum { COL = 12 };

int main(void)
{
    const int lcd_segment[][COL] =
    {
        { 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1 }, // 0
        { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 }, // 1
        { 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 }, // 2
        { 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 }, // 3
        { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0 }, // 4
        { 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1 }, // 5
        { 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1 }, // 6
        { 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 }, // 7
        { 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, // 8
        { 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1 }, // 9
    };

    const char segment_c[] = "--|||--|||--";
    const char segment_x[] = { 1, 3, 0, 2, 4, 1, 3, 0, 2, 4, 1, 3 };
    const char segment_y[] = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 3, 4, 4 };

    char display[5][5];

    for (int digit = 0; digit < 10; digit++)
    {
        memset(display, ' ', sizeof(display));
        for (int segnum = 0; segnum < 12; segnum++)
        {
            if (lcd_segment[digit][segnum] == 1)
            {
                int x = segment_x[segnum];
                int y = segment_y[segnum];
                display[y][x] = segment_c[segnum];
            }
        }
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
                putchar(display[y][x]);
            putchar('\n');
        }
    }

    return 0;
}
