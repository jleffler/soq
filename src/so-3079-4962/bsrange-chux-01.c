/* SO 4584-8084 - answer by chux */
/* Reformatted per JL standards, and testing framework extended */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    int start_addr;
    size_t length;
} Section;

// Is point `a` in the section?
// return left:-1, right:1, else 0
static int LeftInRight(intmax_t a, const Section *sec)
{
    if (a < sec->start_addr)
        return -1;
    if (a >= sec->start_addr + (intmax_t)sec->length)
        return 1;
    return 0;
}

static
bool isEncapsulated_helper(intmax_t addr, size_t len, const Section *sec, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (len == 0)
            return true;
        int LSide =  LeftInRight(addr, &sec[i]);
        if (LSide > 0)
            continue;         // all of addr/len is to the right of this section
        int RSide =  LeftInRight(addr + (intmax_t)(len - 1), &sec[i]);
        if (RSide < 0)
            continue;         // all of addr/len is to the left of this section

        if (LSide < 0)
        {
            // portion of addr/len is to the left of this section
            intmax_t Laddr = addr;
            size_t Llen = (size_t)(sec[i].start_addr - addr);
            if (!isEncapsulated_helper(Laddr, Llen, sec + 1, n - i - 1))
            {
                return false;
            }
        }
        if (RSide <= 0)
            return true;
        // portion of addr/len is to the right of this section, continue with that
        intmax_t Raddr = sec[i].start_addr + (intmax_t)sec[i].length;
        size_t Rlen = (size_t)(addr + (intmax_t)len - Raddr);
        addr = Raddr;
        len = Rlen;
    }
    return len == 0;
}

/*
** Example by chux:
** Range:       xxxxxxxxxxxx
** Def range 11 ___aaaaaa___
** Def range 12 bbb_________
** Def range 13 _________ccc
** More extreme variant by JL:
** Range:       xxxxxxxxxxxx
** Def range 21 ___aaa______
** Def range 22 b___________
** Def range 23 _________c__
** Def range 24 ______dd____
** Def range 25 _ee_________
** Def range 26 ________f___
** Def range 27 _________ggg
** Note that dropping either one of the two d values
** would mean that the range is not encapsulated.
*/

static const Section arr[] =
{
    { .start_addr =  20, .length = 100, },
    { .start_addr = 150, .length =  25, },
    { .start_addr = 175, .length =  25, },

    { .start_addr = 315, .length =  30, },  // Chux - covers 300..360
    { .start_addr = 300, .length =  15, },
    { .start_addr = 345, .length =  15, },

    { .start_addr = 415, .length =  15, },  // JL - Covers 400..460
    { .start_addr = 400, .length =   5, },
    { .start_addr = 445, .length =   5, },
    { .start_addr = 430, .length =  10, },
    { .start_addr = 405, .length =  10, },
    { .start_addr = 440, .length =   5, },
    { .start_addr = 445, .length =  15, },

    { .start_addr = 515, .length =  15, },  // JL - Does not cover 500..560
    { .start_addr = 500, .length =   5, },
    { .start_addr = 545, .length =   5, },
    { .start_addr = 530, .length =   5, },  // Gap between 535 and 540
    { .start_addr = 505, .length =  10, },
    { .start_addr = 540, .length =   5, },
    { .start_addr = 545, .length =  15, },
};

#define SECTION_N (sizeof arr / sizeof arr[0])

static bool isEncapsulated(int addr, size_t len)
{
    return isEncapsulated_helper(addr, len, arr, SECTION_N);
}

#include <stdio.h>

static void dump_sections(const Section *arr, int num)
{
    for (int i = 0; i < num; i++)
    {
        int lo = arr[i].start_addr;
        int len = arr[i].length;
        int hi = lo + len;
        printf("%2d: [%3d..%3d] = %3d\n", i, lo, hi, len);
    }
}

int main(void)
{
    static const Section tests[] =
    {
        { .start_addr = 170, .length =  10, },  // Yes
        { .start_addr =  70, .length =  10, },  // Yes
        { .start_addr = 150, .length =  50, },  // Yes
        { .start_addr =  90, .length =  40, },  // No
        { .start_addr = 145, .length =  60, },  // No
        { .start_addr = 130, .length =  40, },  // No
        { .start_addr = 180, .length =  40, },  // No
        { .start_addr =  10, .length =  40, },  // No
        { .start_addr = 300, .length =  60, },  // Yes
        { .start_addr = 400, .length =  60, },  // Yes
        { .start_addr = 500, .length =  60, },  // No
    };
    enum { NUM_TESTS = sizeof(tests) / sizeof(tests[0]) };
    dump_sections(arr, SECTION_N);
    for (int i = 0; i < NUM_TESTS; i++)
    {
        int lo = tests[i].start_addr;
        int len = tests[i].length;
        int hi = lo + len;
        printf("Sample [%3d..%3d] %s\n", lo, hi, isEncapsulated(lo, len) ? "Yes" : "No");
    }
}
