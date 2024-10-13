/* SO 7183-1526 */
/* Rotation code from answer by chqrlie; test harness from JL */
/*
** Code for #ifdef USE_JLSS_CODE is amended by JL based on the first
** version of chqrlie's code and fixed the bugs in essentially the same
** way the chqrlie did in the revised code in the #ifndef USE_JLSS_CODE
** block.  And the outputs are the same.
** Program rot43 generates rotations a wholly different way.  Its output
** agrees with that from rot53.
*/

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

static uint32_t somearray[12] =
{
    0xd1310ba6, 0x98dfb5ac, 0x2ffd72db, 0xd01adfb7, 0xb8e1afed, 0x6a267e96,
    0xba7c9045, 0xf12c7f99, 0x24a19947, 0xb3916cf7, 0x0801f2e2, 0x858efc16,
};
enum { NUM_SOMEARRAY = sizeof(somearray) / sizeof(somearray[0]) };


// assuming x is a uint64_t and r in the range 0..63
#define ROR64(x, n) (((x) >> (n)) | ((x) << (63 - (n)) << 1))
#define ROL64(x, n) (((x) << (n)) | ((x) >> (63 - (n)) >> 1))

// assuming r in the range 0..63
static inline uint64_t ror64(uint64_t x, int n)
{
    return (x >> n) | (x << (63 - n) << 1);
}

static inline uint64_t rol64(uint64_t x, int n)
{
    return (x << n) | (x >> (63 - n) >> 1);
}

#ifndef USE_JLSS_CODE
static void ror32_array(uint32_t *dst, const uint32_t *src, size_t size, size_t n) {
    size_t dist = n / 32 % size;
    int shift = n % 32;
    for (size_t i = 0; i < size; i++) {
        dst[(i + dist) % size] = src[i] >> shift;
    }
    if (shift) {
        for (size_t i = 0; i < size; i++) {
            dst[(i + dist + 1) % size] |= src[i] << (32 - shift);
        }
    }
}

static void rol32_array(uint32_t *dst, const uint32_t *src, size_t size, size_t n) {
    size_t dist = n / 32 % size;
    int shift = n % 32;
    for (size_t i = 0; i < size; i++) {
        dst[(i + size - dist) % size] = src[i] << shift;
    }
    if (shift) {
        for (size_t i = 0; i < size; i++) {
            dst[(i + size - dist - 1) % size] |= src[i] >> (32 - shift);
        }
    }
}

#else

static void ror32_array(uint32_t *dst, const uint32_t *src, size_t size, size_t n)
{
    size_t dist = (n / 32) % size;
    size_t shift = n % 32;
    // printf("size = %zu, n = %zu, dist = %zu, shift = %zu\n", size, n, dist, shift);
    for (size_t i = 0; i < size; i++)
    {
        dst[(i + dist) % size] = src[i] >> shift;
    }
    if (shift)
    {
        for (size_t i = 0; i < size; i++)
        {
            dst[(i + dist + 1) % size] |= src[i] << (32 - shift);
        }
    }
}

static void rol32_array(uint32_t *dst, const uint32_t *src, size_t size, size_t n)
{
    size_t dist = (n / 32) % size;
    size_t shift = n % 32;
    //printf("size = %zu, n = %zu, dist = %zu, shift = %zu\n", size, n, dist, shift);
    for (size_t i = 0; i < size; i++)
    {
        dst[(i + size - dist) % size] = src[i] << shift;
    }
    if (shift)
    {
        for (size_t i = 0; i < size; i++)
        {
            // if (i == size - 1 || i == 0)
            //{
            //    size_t idx = (i + size - dist - 1) % size;
            //    printf("i = %zu, idx = %zu, dst[%zu] = 0x%.8" PRIX32 ", src[%zu] = 0x%.8" PRIX32
            //           ", shift = %zu, value = 0x%.8" PRIX32 "\n",
            //           i, idx, idx, dst[idx], i, src[i], 32 - shift, (src[i] >> (32 - shift)));
            //}
            dst[(i + size - dist - 1) % size] |= src[i] >> (32 - shift);
            // if (i == size - 1 || i == 0)
            //{
            //    size_t idx = (i + size - dist - 1) % size;
            //    printf("After: dst[%zu] = 0x%.8" PRIX32 "\n", idx, dst[idx]);
            //}
        }
    }
}

#endif /* USE_JLSS_CODE */

static void print_array32(const char *tag, size_t arrlen, uint32_t array[arrlen])
{
    printf("%s (%zu):", tag, arrlen);
    putchar((arrlen >= 5) ? '\n' : ' ');
    int length = 0;
    const char *pad = "";
    for (size_t i = 0; i < arrlen; i++)
    {
        length += printf("%s0x%.8" PRIX32, pad, array[i]);
        pad = " ";
        if (length > 64)
        {
            putchar('\n');
            length = 0;
            pad = "";
        }
    }
    if (length > 0)
        putchar('\n');
}

int main(void)
{
    uint32_t answer[NUM_SOMEARRAY];

    uint32_t smaller[] = { 0x10101010, 0x0505A0A0 };
    enum { NUM_SMALLER = sizeof(smaller) / sizeof(smaller[0]) };
    for (int i = 0; i <= 32; i++)
    {
        char buffer[64];
        print_array32("Small array before rotate ", NUM_SMALLER, smaller);

        memset(answer, '\xFF', sizeof(answer));
        ror32_array(answer, smaller, NUM_SMALLER, i);
        snprintf(buffer, sizeof(buffer), "After rotate right %2d bits", i);
        print_array32(buffer, NUM_SMALLER, answer);

        memset(answer, '\xFF', sizeof(answer));
        rol32_array(answer, smaller, NUM_SMALLER, i);
        snprintf(buffer, sizeof(buffer), "After rotate  left %2d bits", i);
        print_array32(buffer, NUM_SMALLER, answer);
    }
    putchar('\n');

    int shift[] = { 0, 4, 8, 12, 16, 20, 24, 27, 28, 32, 37, 48, 65 };
    enum { NUM_SHIFT = sizeof(shift) / sizeof(shift[0]) };

    for (int i = 0; i < NUM_SHIFT; i++)
    {
        char buffer[64];
        print_array32("Before rotation", NUM_SOMEARRAY, somearray);

        memset(answer, '\xFF', sizeof(answer));
        ror32_array(answer, somearray, NUM_SOMEARRAY, shift[i]);
        snprintf(buffer, sizeof(buffer), "After rotate right %d bits", shift[i]);
        print_array32(buffer, NUM_SOMEARRAY, answer);

        memset(answer, '\xFF', sizeof(answer));
        rol32_array(answer, somearray, NUM_SOMEARRAY, shift[i]);
        snprintf(buffer, sizeof(buffer), "After rotate left %d bits", shift[i]);
        print_array32(buffer, NUM_SOMEARRAY, answer);
        putchar('\n');
    }

    return 0;
}
