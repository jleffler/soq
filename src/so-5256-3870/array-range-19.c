/* SO 5256-3870 */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Paramterization for signed types */
typedef int SignedType;
typedef unsigned UnsignedType;
#define SIGNED_MAX  INT_MAX
#define SIGNED_MIN  INT_MIN
#define DATA_FMT    "11d"
#define RANGE_FMT   "u"

static UnsignedType ArrayRange(size_t num_values, SignedType values[num_values])
{
    if (num_values == 0)
        return 0;

    SignedType large = values[0];
    SignedType small = values[0];

    for (size_t i = 1; i < num_values; i++)
    {
        if (values[i] > large)
            large = values[i];
        else if (values[i] < small)
            small = values[i];
    }

    UnsignedType range;
    assert(small <= large);
    if (small >= 0 || large < 0 || (large == 0 && small != SIGNED_MIN))
    {
        /* Most common cases - both values of same sign; no overflow risk */
        /* Any mode of binary arithmetic */
        assert(large >= small);
        range = large - small;
    }
    else if ((-SIGNED_MAX == SIGNED_MIN) || (small != SIGNED_MIN))
    {
        /*
        ** Two's complement arithmetic with values with different signs
        ** but the small value is not SIGNED_MIN, or one's complement
        ** arithmetic or sign-magnitude arithmetic (which have negative
        ** zeros but no asymmetry in the positive vs negative ranges).
        */
        /* Different signs — therefore large is positive and small is negative */
        assert(large > 0 && small < 0);
        range = (UnsignedType)large + (UnsignedType)(-small);
    }
    else
    {
        /* Twos-complement arithmetic — small is SIGNED_MIN */
        assert(-SIGNED_MAX - 1 == SIGNED_MIN);
        assert(small == SIGNED_MIN && large >= 0);
        range = (UnsignedType)large + SIGNED_MAX + 1;
    }

    return range;
}

int main(void)
{
    SignedType arrays[][2] =
    {
        { +345, +436 },
        { +436, +345 },
        { -199, -439 },
        { -439, -199 },
        { -999, +999 },
        { +999, -999 },
        { 0, 0 },
        { 0, SIGNED_MAX },
        { 0, SIGNED_MIN },
        { 0, SIGNED_MAX },
        { -1000, SIGNED_MAX },
        { +1000, SIGNED_MAX },
        { -1000, SIGNED_MIN },
        { +1000, SIGNED_MIN },
        { SIGNED_MIN, SIGNED_MAX },
        { SIGNED_MIN, SIGNED_MIN },
        { SIGNED_MAX, SIGNED_MAX },
        { SIGNED_MIN, -SIGNED_MAX },
    };
    enum { NUM_ARRAYS = sizeof(arrays) / sizeof(arrays[0]) };

    for (int i = 0; i < NUM_ARRAYS; i++)
    {
        UnsignedType range = ArrayRange(2, arrays[i]);
        printf("%+" DATA_FMT ":%+-" DATA_FMT " = %" RANGE_FMT "\n",
               arrays[i][0], arrays[i][1], range);
    }

    return 0;
}
