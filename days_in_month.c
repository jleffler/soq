/* SO 28800127 Universal formula to calculate the number of days in month */
#include <assert.h>
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
    //printf("mm = %2d; ", mm);
    //printf("(mm + (mm/8)) %% 2 = %d; ", (mm + (mm/8)) % 2);
    //printf("2 %% mm = %d; ", 2 % mm);
    //printf("2 * (1/mm) = %d; ", 2 * (1/mm));
    //printf("DIM %2d = %2d:  ", mm, (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm)));
    return (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm));
}

static inline int new_dim(int mm, int yyyy)
{
    //printf("yyyy = %4d mm = %2d; ", yyyy, mm);
    //printf("(mm + (mm/8)) %% 2 = %d; ", (mm + (mm/8)) % 2);
    //printf("2 %% mm = %d; ", 2 % mm);
    //printf("2 * (1/mm) = %d; ", 2 * (1/mm));
    //printf("(mm == 2) * leapyear(yyyy) = %d:  ", ((mm == 2) * leapyear(yyyy)));
    return (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm) + ((mm == 2) * leapyear(yyyy)));
}
 
static inline int alt_dim(int mm, int yyyy)
{
    printf("yyyy = %4d mm = %2d; ", yyyy, mm);
    printf("(mm + (mm/8)) %% 2 = %d; ", (mm + (mm/8)) % 2);
    printf("2 %% mm = %d; ", 2 % mm);
    printf("2 * (1/mm) = %d; ", 2 * (1/mm));
    printf("(1 - 1/mm) * (1 - ((2 %% mm) / 2)) * leapyear(yyyy) = %d:  ",
            (1 - 1/mm) * (1 - ((2 % mm) / 2)) * leapyear(yyyy));
    return (28 + (mm + (mm/8)) % 2 + 2 % mm + 2 * (1/mm) +
            (1 - 1/mm) * (1 - ((2 % mm) / 2)) * leapyear(yyyy));
}

int main(void)
{
    /*28 + (x + Math.floor(x/8)) % 2 + 2 % x + 2 * Math.floor(1/x);*/
    for (int mm = 1; mm <= 12; mm++)
        printf("mm = %2d, DIM = %2d\n", mm, old_dim(mm));

    for (int yyyy = 1900; yyyy < 2101; yyyy += 5)
    {
        for (int mm = 1; mm <= 12; mm++)
        {
            int dim1 = new_dim(mm, yyyy);
            int dim2 = alt_dim(mm, yyyy);
            printf("yyyy = %4d, mm = %2d: DIM = %2d (%2d)\n", yyyy, mm, dim1, dim2);
            assert(dim1 == dim2);
        }
    }

    return 0;
}
