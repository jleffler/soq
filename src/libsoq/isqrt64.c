/*
@(#)File:           isqrt64.c
@(#)Purpose:        64-bit Integer square root calculation
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-2023
@(#)Derivation:     isqrt64.c 1.6 2023/02/02 20:51:20
*/

/*TABSTOP=4*/

#include "isqrt.h"

/* Configuration: use public domain implementation unless -DUSE_JLSS_ISQRT */
#undef USE_PUBLIC_DOMAIN
#ifndef USE_JLSS_ISQRT
#define USE_PUBLIC_DOMAIN
#endif /* USE_JLSS_ISQRT */

#if defined(USE_TIMING_TESTS)
extern int64_t isqrt_64_step(uint64_t x);
extern int64_t isqrt_64_loop(uint64_t x);
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-macros"
#define isqrt_64_step(x) isqrt_64(x)
#define isqrt_64_loop(x) isqrt_64(x)
#pragma GCC diagnostic pop
#endif /* USE_TIMING_TESTS */

#if defined(USE_PUBLIC_DOMAIN) || defined(USE_TIMING_TESTS)
/*
** Adapted code by Chris Torek: fast and (hopefully) correct
*/
int64_t isqrt_64_step(uint64_t v)
{
    uint64_t t = 0;
    uint64_t r = 0;
    uint64_t s;

#undef STEP
#define STEP(k) \
    s = t + r; \
    r >>= 1; \
    if (s <= v) { \
        v -= s; \
        r |= t; \
    }

    if (v > UINT32_MAX)
    {
        t = UINT64_C(1) << 62;
        STEP(31);
        t >>= 2;
        STEP(30);
        t >>= 2;
        STEP(29);
        t >>= 2;
        STEP(28);
        t >>= 2;
        STEP(27);
        t >>= 2;
        STEP(26);
        t >>= 2;
        STEP(25);
        t >>= 2;
        STEP(24);
        t >>= 2;
        STEP(23);
        t >>= 2;
        STEP(22);
        t >>= 2;
        STEP(21);
        t >>= 2;
        STEP(20);
        t >>= 2;
        STEP(19);
        t >>= 2;
        STEP(18);
        t >>= 2;
        STEP(17);
        t >>= 2;
        STEP(16);
        t >>= 2;
    }
    else
        t = UINT64_C(1) << 30;

    STEP(15);
    t >>= 2;
    STEP(14);
    t >>= 2;
    STEP(13);
    t >>= 2;
    STEP(12);
    t >>= 2;
    STEP(11);
    t >>= 2;
    STEP(10);
    t >>= 2;
    STEP(9);
    t >>= 2;
    STEP(8);
    t >>= 2;
    STEP(7);
    t >>= 2;
    STEP(6);
    t >>= 2;
    STEP(5);
    t >>= 2;
    STEP(4);
    t >>= 2;
    STEP(3);
    t >>= 2;
    STEP(2);
    t >>= 2;
    STEP(1);
    t >>= 2;
    STEP(0);

#undef STEP

    return (int64_t)r;
}
#endif /* USE_PUBLIC_DOMAIN || USE_TIMING_TESTS */

#if !defined(USE_PUBLIC_DOMAIN) || defined(USE_TIMING_TESTS)
/*
** Adapted code by Chris Torek: pretty fast and (hopefully) correct
*/
int64_t isqrt_64_loop(uint64_t v)
{
    uint64_t t = 1L << 62;
    uint64_t r = 0;
    uint64_t s;

#undef STEP
#define STEP(k) \
    s = t + r; \
    r >>= 1; \
    if (s <= v) { \
        v -= s; \
        r |= t; \
    }

    for (int k = 31; k > 0; k--)
    {
        STEP(k);
        t >>= 2;
    }
    STEP(0);

#undef STEP

    return (int64_t)r;
}
#endif /* !USE_PUBLIC_DOMAIN || USE_TIMING_TESTS */

#if defined(TEST)

#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#if defined(USE_TIMING_TESTS)
/*
** Representative timings - MacOS X 10.7.2 on a 2.3 GHz Intel Core i7
** with 8 GB 1333 MHz DDR3 memory.
**
** CT: 0.482771 (1370731968); JL 2.074758 (1370731968); MT 0.125003 (1507082656)
** CT: 0.404681 (1370731968); JL 1.825984 (1370731968); MT 0.086421 (1507082656)
** CT: 0.509388 (1370731968); JL 1.900582 (1370731968); MT 0.094746 (1507082656)
** CT: 0.534594 (1370731968); JL 1.866929 (1370731968); MT 0.095474 (1507082656)
** CT: 0.447996 (1370731968); JL 2.211031 (1370731968); MT 0.120391 (1507082656)
*/

#include "timer.h"

enum { ITERATIONS = 100000 };

static inline uint64_t next_64_x(uint64_t x)
{
    // Need 128-bit (more than 64-bit) arithmetic -- double!
    return x * 1.2311441 + 1;
    //return (UINT64_C(262) * x) / UINT64_C(213) + 1;
    //return (UINT64_C(20349812971) * x) / UINT64_C(213) + 1;
}

extern int64_t isqrt_64_mt(uint64_t x);

int64_t isqrt_64_mt(uint64_t x)
{
    return x;
}

static void test_isqrt_64(void)
{
    Clock c1;
    Clock c2;
    Clock c3;
    uint64_t acc1 = 0;
    uint64_t acc2 = 0;
    uint64_t acc3 = 0;

    clk_init(&c1);
    clk_init(&c2);
    clk_init(&c3);

    /* Test the public domain (Chris Torek) algorithm */
    clk_start(&c1);
    for (uint64_t i = 0; i < ITERATIONS; i++)
    {
        for (uint64_t x = 0; x < UINT64_MAX / 2; x = next_64_x(x))
        {
            int64_t v = isqrt_64_step(x);
            acc1 += v + i;
        }
    }
    clk_stop(&c1);

    /* Test the loop algorithm */
    clk_start(&c2);
    for (uint64_t i = 0; i < ITERATIONS; i++)
    {
        for (uint64_t x = 0; x < UINT64_MAX / 2; x = next_64_x(x))
        {
            int64_t v = isqrt_64_loop(x);
            acc2 += v + i;
        }
    }
    clk_stop(&c2);

    /* Test the empty algorithm */
    clk_start(&c3);
    for (uint64_t i = 0; i < ITERATIONS; i++)
    {
        for (uint64_t x = 0; x < UINT64_MAX / 2; x = next_64_x(x))
        {
            int64_t v = isqrt_64_mt(x);
            acc3 += v + i;
        }
    }
    clk_stop(&c3);

    printf("CT: %8s (%" PRIu64 "); LP %8s (%" PRIu64 "); MT %8s (%" PRIu64 ")\n",
            clk_fmt_elapsed_us(&c1), acc1,
            clk_fmt_elapsed_us(&c2), acc2,
            clk_fmt_elapsed_us(&c3), acc3);
}

int main(void)
{
    test_isqrt_64();
    return 0;
}

#elif defined(USE_PUBLIC_DOMAIN)
int main(void)
{
    uint64_t l;
    char            buf[100];

    for (;;)
    {
        (void)printf("gimme a number> ");
        if (fgets(buf, sizeof buf, stdin) == NULL)
            break;
        /* should use strtoul here but some do not have it */
        if (sscanf(buf, "0x%" SCNx64, &l) != 1 &&
            sscanf(buf, "0%"  SCNo64, &l) != 1 &&
            sscanf(buf, "%"   SCNu64, &l) != 1 &&
            sscanf(buf, "%"   SCNx64, &l) != 1)
            (void)printf("that was not a number\n");
        else
        {
            uint64_t ri = isqrt_64(l);
            double   rd = sqrt((double)l);
            assert(ri * ri <= l && (ri+1)*(ri+1) > l);
            (void)printf("root(%" PRIu64 ") => %" PRIu64 " sqrt(%" PRIu64 ") => %.17g\n",
                          l, ri, l, rd);
        }
    }
    putchar('\n');
    return(0);
}

#else

static const uint64_t tests64[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 24, 25, 9999, 10000,
    0xFFFFFFFE, 0xFFFFFFFF, 0x10000000, 0x101010101010,
    0x3FFFFFFFFFFF, 0x400000000000, 0xFFFFFFFFFFFFFFFF,
};

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

static void check64(uint64_t x)
{
    int64_t s = isqrt_64(x);
    assert(s * s <= x);
    // assert((s+1) * (s+1) > x);
    // But avoid overflows!
    assert(x / (s + 1) < (s + 1));
    printf("ISQRT64(%" PRIu64 ") = %" PRId64 "\n", x, s);
}

int main(void)
{
    for (size_t i = 0; i < DIM(tests64); i++)
        check64(test64[i]);
    return(0);
}

#endif /* USE_PUBLIC_DOMAIN */
#endif /* TEST */
