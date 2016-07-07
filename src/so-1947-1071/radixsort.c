#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum { BINS  = 16  };
enum { GROUP = 4   };
enum { MASK  = 0xF };

static void dump_array(char const *tag, size_t n, int a[n])
{
    printf("%s:\n", tag);
    for (size_t i = 0; i < n; i++)
        printf("int: %11d hex: 0x%.8X\n", a[i], a[i]);
}

static size_t num_iterations(size_t n, int a[n])
{
    size_t num_iter = 0;
    size_t max_iter = sizeof(int) * CHAR_BIT / GROUP;
    unsigned max_val = 0;
    for (size_t i = 0; i < n; i++)
    {
        if ((unsigned)a[i] > max_val)
        {
            for (size_t j = num_iter; j < max_iter; j++)
            {
                if (((unsigned)a[i] >> j * GROUP) & MASK)
                    num_iter = j;
            }
            max_val = (unsigned)a[i];
            if (num_iter == max_iter)
                break;
        }
    }
    return num_iter + 1;
}

int main(void)
{
    int list[] =
    {
        0x00000016, 0x0000004C, 0x0000004C, 0x000000D4, 0x0000000A, 0x000000E6, 0x000000AF, 0x00000013,
        0x000065C6, 0x00000BEB, 0x000096BA, 0x00009A7D, 0x00002917, 0x00008A2C, 0x0000DEAD, 0x0000BEEF,
        0x00C500A9, 0x0033E6B2, 0x00957850, 0x00546F9F, 0x003C4FD3, 0x00601839, 0x00FD4B4C, 0x007B0855,
        0x0000FACE, 0x000FACED, 0x000ABCDE, 0x00012345, 0x000BEEFE, 0x00049912, 0x00037777, 0x0002D999,
        0x0607743F, 0x028A8148, 0x0B0E6709, 0x028543F7, 0x0D57B5BD, 0x0B7E088C, 0x0D53722E, 0x09E07780,
        0x3F642A6A, 0xDD081EF7, 0x6DF13553, 0x9F809E88, 0xD2751C0F, 0xEF2A30BB, 0x54095DF1, 0x3D2D1723,
        0x0000000F, 0x00000000, 0x00000000, 0x00000004, 0x00000000, 0x00000001, 0x00000002, 0x0000000B,
        0x00000D46, 0x00000B51, 0x00000C62, 0x00000C35, 0x00000046, 0x0000054E, 0x00000AD0, 0x0000051D,
        0xB1AC1192, 0xE9E2844B, 0xBB6CC403, 0xCDDE535F, 0xB60D02BD, 0xBE5DDAA5, 0xC6F5A46A, 0x9F5505E5,
        0xFF424509, 0xFF882512, 0xFF33E44C, 0xFF12E905, 0xFF6913C5, 0xFFB4055D, 0xFF0CBD83, 0xFFDDCFAA,
        0xFFF2131E, 0xFFF3C851, 0xFFFF0EF1, 0xFFF8A156, 0xFFF660D8, 0xFFFEB4F0, 0xFFF8B8FB, 0xFFF7CF54,
        0xFFFF001E, 0xFFFFF0E5, 0xFFFFADF9, 0xFFFF0141, 0xFFFF6307, 0xFFFF2298, 0xFFFF0A61, 0xFFFF1C1A,
        0xFFFFFDF0, 0xFFFFFA54, 0xFFFFF6B0, 0xFFFFF786, 0xFFFFF600, 0xFFFFF59E, 0xFFFFF893, 0xFFFFFBB4,
        0xFFFFFFBD, 0xFFFFFF59, 0xFFFFFF28, 0xFFFFFFEF, 0xFFFFFF5C, 0xFFFFFF91, 0xFFFFFF08, 0xFFFFFF5A,
        0xFFFFFFF9, 0xFFFFFFF0, 0xFFFFFFFE, 0xFFFFFFF6, 0xFFFFFFF5, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFFF,
    };
    enum { LIST_SIZE = sizeof(list) / sizeof(list[0]) };
    int buffer[LIST_SIZE];
    int cnt[BINS];
    int map[BINS];

    for (int k = 8; k <= LIST_SIZE; k += 8)
    {
        // init pointers to the list of unsorted numbers and temp buffer
        int *src_ptr = list;
        int *dst_ptr = buffer;

        // print unsorted list
        dump_array("unsorted list", k, src_ptr);
        size_t num_iter = num_iterations(k, src_ptr);
        printf("Number of iterations = %zd\n", num_iter);

        for (size_t j = 0; j < num_iter; j++)
        {
            // initalize the count
            for (int i = 0; i < BINS; i++)
                cnt[i] = 0;

            // count significant digits. shifting j * group # of times
            for (int i = 0; i < k; i++)
                cnt[(src_ptr[i] >> j*GROUP) & MASK]++;

            // initalize the map
            for (int i = 0; i < BINS; i++)
                map[i] = 0;

            // compute the map
            for (int i = 1; i < BINS; i++)
                map[i] = (map[i - 1] + cnt[i - 1]);

            // shift the elements in buffer[] and list[] via their pointers.
            // shifting j * group # of times
            for (int i = 0; i < k; i++)
                dst_ptr[map[(src_ptr[i] >> j*GROUP) & MASK]++] = src_ptr[i];

            // perform a swap of list[] and buffer[] via their pointers
            int *tmp_ptr = src_ptr;
            src_ptr = dst_ptr;
            dst_ptr = tmp_ptr;
        }

        // print list for reference
        dump_array("sorted list", k, src_ptr);
    }

    return 0;
}

