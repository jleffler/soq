/* SO 5256-3870 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned ArrayRange(size_t num_values, int values[num_values])
{
    int large;
    int small;
    unsigned range;

    if (num_values < 1)
        return 0;

    large = values[0];
    small = values[0];

    for (size_t i = 1; i < num_values; i++)
    {
        if (values[i] > large)
            large = values[i];
        else if (values[i] < small)
            small = values[i];
    }

    if ((large >= 0 && small >= 0) || (large <= 0 && small <= 0))
    {
        /* Most common cases - both values of same sign; no overflow risk */
        /* Any mode of binary arithmetic */
        assert(large >= small);
        range = large - small;
    }
    else if ((-INT_MAX == INT_MIN) || (small != INT_MIN))
    {
        /*
        ** Two's complement arithmetic with values with different signs
        ** but the small value is not INT_MIN, or one's complement
        ** arithmetic or sign-magnitude arithmetic (which have negative
        ** zeros but no asymmetry in the positive vs negative ranges).
        */
        /* Different signs — therefore large is positive and small is negative */
        assert(large > 0 && small < 0);
        range = (unsigned)large + (unsigned)(-small);
    }
    else
    {
        /* Twos-complement arithmetic — small is INT_MIN */
        assert(-INT_MAX - 1 == INT_MIN);
        assert(small == INT_MIN && large > 0);
        range = (unsigned)large + INT_MAX + 1;
    }

    return range;
}

int main(void)
{
    int arrays[][2] =
    {
        { +345, +436 },
        { +436, +345 },
        { -199, -439 },
        { -439, -199 },
        { -999, +999 },
        { +999, -999 },
        { 0, 0 },
        { 0, INT_MAX },
        { 0, INT_MIN },
        { 0, INT_MAX },
        { -1000, INT_MAX },
        { +1000, INT_MAX },
        { -1000, INT_MIN },
        { +1000, INT_MIN },
        { INT_MIN, INT_MAX },
        { INT_MIN, INT_MIN },
        { INT_MAX, INT_MAX },
        { INT_MIN, -INT_MAX },
    };
    enum { NUM_ARRAYS = sizeof(arrays) / sizeof(arrays[0]) };

    for (int i = 0; i < NUM_ARRAYS; i++)
    {
        unsigned int range = ArrayRange(2, arrays[i]);
        printf("%+11d:%+-11d = %u\n", arrays[i][0], arrays[i][1], range);
    }

    return 0;
}
