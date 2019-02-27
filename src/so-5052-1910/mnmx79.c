/* SO 5052-1910 - Find min and max in an efficient way */
/*
** Data structure for array has: count of ranges, N; N * 2 integers, low
** and high; plus any left-overs as individual values
*/
#undef NDEBUG
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

static void find_min_max(size_t num, uint32_t arr[num], uint32_t *pmin, uint32_t *pmax)
{
    assert(arr != 0 && pmin != 0 && pmax != 0 && num > 1);
    assert(arr[0] <= num);
    assert(arr[0] == 0 || num > 2);

    uint32_t max = arr[1];
    uint32_t min = arr[1];
    uint32_t lim = arr[0] * 2;
    size_t i;

    for (i = 1; i < lim; i += 2)
    {
        assert(arr[i] <= arr[i + 1]);
        if (arr[i] < min)
            min = arr[i];
        if (arr[i + 1] > max)
            max = arr[i + 1];
    }

    for ( ; i < num; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        else if (arr[i] > max)
            max = arr[i];
    }
    *pmin = min;
    *pmax = max;
}

static void test_min_max(const char *tag, size_t num, uint32_t arr[num])
{
    uint32_t lim = arr[0] * 2;
    size_t i;

    printf("%s (%zu):\n", tag, num);
    for (i = 1; i < lim; i += 2)
        printf("  Range %zu: %" PRIu32 "..%" PRIu32 "\n", i / 2, arr[i], arr[i + 1]);
    while (i < num)
        printf("  Value: %" PRIu32 "\n", arr[i++]);

    uint32_t min;
    uint32_t max;
    find_min_max(num, arr, &min, &max);

    printf("%s: min = %" PRIu32 ", max = %" PRIu32 "\n", tag, min, max);
}

int main(void)
{
    uint32_t arr1[] = { 2, 34, 78, 5, 10, 100 };
    uint32_t arr2[] = { 1, 18, 39, 2 };
    uint32_t arr3[] = { 0, 14, 5, 256, 99 };
    uint32_t arr4[] = { 2, 9, 14, 5, 256 };
    uint32_t arr5[] = { 2, 9, 14, 5, 256, 2 };
    uint32_t arr6[] = { 2, 9, 14, 5, 256, 379 };
    uint32_t arr7[] = { 0, 9, };
    uint32_t arr8[] = { 1, 9, 9 };

    test_min_max("arr1", sizeof(arr1) / sizeof(arr1[0]), arr1);
    test_min_max("arr2", sizeof(arr2) / sizeof(arr2[0]), arr2);
    test_min_max("arr3", sizeof(arr3) / sizeof(arr3[0]), arr3);
    test_min_max("arr4", sizeof(arr4) / sizeof(arr4[0]), arr4);
    test_min_max("arr5", sizeof(arr5) / sizeof(arr5[0]), arr5);
    test_min_max("arr6", sizeof(arr6) / sizeof(arr6[0]), arr6);
    test_min_max("arr7", sizeof(arr7) / sizeof(arr7[0]), arr7);
    test_min_max("arr8", sizeof(arr8) / sizeof(arr8[0]), arr8);

    return 0;
}
