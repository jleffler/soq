/* SO 28800127 Universal formula to calculate the number of days in month */

#include <stdio.h>
#include <stdbool.h>

static inline bool leapyear(int yy)
{
    if (yy %   4 != 0) return false;
    if (yy % 100 != 0) return true;
    if (yy % 400 != 0) return false;
    return true;
}

static inline int old_dim(int mm)
{
    //printf("mm = %d ", mm);
    //printf("(mm + (mm/8)) %% 2 = %d ", (mm + (mm/8)) % 2);
    //printf("2 %% mm = %d ", 2 % mm);
    //printf("2 * (1/mm) = %d ", 2 * (1/mm));
    //printf("DIM %2d = %2d\n", mm, (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm)));
    return (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm));
}

static inline int new_dim(int mm, int yyyy)
{
    //printf("yyyy = %4d mm = %d ", yyyy, mm);
    //printf("(mm + (mm/8)) %% 2 = %d ", (mm + (mm/8)) % 2);
    //printf("2 %% mm = %d ", 2 % mm);
    //printf("2 * (1/mm) = %d ", 2 * (1/mm));
    //printf("(mm == 2) * leapyear(yyyy) = %d\n", ((mm == 2) * leapyear(yyyy)));
    return (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm) + ((mm == 2) * leapyear(yyyy)));
}

int main(void)
{
    /*28 + (x + Math.floor(x/8)) % 2 + 2 % x + 2 * Math.floor(1/x);*/
    for (int mm = 1; mm <= 12; mm++)
        printf("mm = %2d, DIM = %2d\n", mm, old_dim(mm));

    for (int yyyy = 1900; yyyy < 2101; yyyy += 5)
    {
        for (int mm = 1; mm <= 12; mm++)
            printf("yyyy = %4d, mm = %2d: DIM = %2d\n", yyyy, mm, new_dim(mm, yyyy));
    }

    return 0;
}
