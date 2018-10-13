/* SO 5256-3870 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Paramterization for unsigned types */
typedef unsigned UnsignedType;
#define UNSIGNED_MAX    UINT_MAX
#define UNSIGNED_MIN    0U

static UnsignedType ArrayRange(size_t num_values, UnsignedType values[num_values])
{
    if (num_values == 0)
        return 0;

    UnsignedType large = values[0];
    UnsignedType small = values[0];

    for (size_t i = 1; i < num_values; i++)
    {
        if (values[i] > large)
            large = values[i];
        else if (values[i] < small)
            small = values[i];
    }

    return large - small;
}

int main(void)
{
    UnsignedType arrays[][2] =
    {
        { +345, +436 },
        { +436, +345 },
        { +1000, UNSIGNED_MAX },
        { +1000, UNSIGNED_MIN },
        { UNSIGNED_MIN, UNSIGNED_MAX },
        { UNSIGNED_MIN, UNSIGNED_MIN },
        { UNSIGNED_MAX, UNSIGNED_MAX },
        { UNSIGNED_MAX, UNSIGNED_MIN },
    };
    enum { NUM_ARRAYS = sizeof(arrays) / sizeof(arrays[0]) };

    for (size_t i = 0; i < NUM_ARRAYS; i++)
    {
        UnsignedType range = ArrayRange(2, arrays[i]);
        printf("%11u:%-11u = %u\n", arrays[i][0], arrays[i][1], range);
    }

    return 0;
}
