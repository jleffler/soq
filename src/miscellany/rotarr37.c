/* Rotate the elements of an array */
#include <stdio.h>
#include <string.h>

static inline void
arr_reverse(const int start, const int end, int arr[])
{
    for (int ai = start, zi = end; ai < zi; ++ai, --zi)
    {
        int tmp = arr[ai];
        arr[ai] = arr[zi];
        arr[zi] = tmp;
    }
}

static void dump_array(const char *tag, size_t size, int array[size])
{
    printf("%s (%zu):", tag, size);
    for (size_t i = 0; i < size; i++)
        printf("  %2d", array[i]);
    putchar('\n');
}

/* Rotate array[N] by K places */
static void rotate_array(size_t N, int array[N], size_t K)
{
    if (N != 0 && K != 0)
    {
        K %= N;
        arr_reverse(0, N - 1, array);
        arr_reverse(0, K - 1, array);
        arr_reverse(K, N - 1, array);
    }
}

int main(void)
{
    int data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    dump_array("Original data", NUM_DATA, data);

    size_t N = NUM_DATA;
    for (size_t i = 1; i < 15; i++)
    {
        char tag[32];
        size_t K = i;

        snprintf(tag, sizeof(tag), "Rotate by %3zu", K);
        int array[N];
        memmove(array, data, sizeof(array));
        rotate_array(N, array, K);
        dump_array(tag, N, array);
    }

    return 0;
}
