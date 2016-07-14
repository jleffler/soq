/*
@(#)File:           isqrt64.c
@(#)Purpose:        64-bit Integer square root calculation
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-16
@(#)Derivation:     isqrt64.c 1.3 2016/07/13 03:30:02
*/

/*TABSTOP=4*/

#include "isqrt.h"

/*
** Code by Chris Torek: fast and correct
*/
/*
** From: edelsohn@sccs.syr.edu (David Edelsohn)
** Subject: Re: quick sqrt()
** Message-ID: <1991Aug14.161849.18548@rodan.acs.syr.edu>
** Date: 14 Aug 91 20:18:49 GMT
** Organization: Syracuse Center for Computational Science/Dept of Physics
**
** I tried replying to the poster but my email bounced and Chris Torek
** has not jumped in with his previous solution, so I will repost it for him:
** >From: chris@mimsy.umd.edu (Chris Torek)
** >Subject: Re: Integer Square Root (Was Re: # to the nth power)
**
** Integer square root routine, good for up to 32-bit values.
** Note that the largest square root (that of 0xffffffff)is
** 0xffff, so the result fits in a regular unsigned and need
** not be `long'.
**
** Original code from Tomas Rokicki (using a well known algorithm).
** This version by Chris Torek, University of Maryland.
**
** This code is in the public domain.
*/

/*
** Adapted code by Chris Torek: fast and (hopefully) correct
*/
int64_t isqrt_64(uint64_t v)
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


#if defined(TEST)

#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#ifdef USE_INTERACTIVE_TEST

int main(void)
{
    uint64_t l;
    char     buf[100];

    while (printf("gimme a number> ") > 0 &&
           fgets(buf, sizeof buf, stdin) != NULL)
    {
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
            assert(ri * ri <= l);
            // assert((ri+1) * (ri+1) > l);
            // But avoid overflows!
            assert(l / (ri + 1) < (ri + 1));
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
    0xFFFFFFFE, 0xFFFFFFFF, 0x100000000, 0x101010101010,
    0x3FFFFFFFFFFF, 0x400000000000, 0xFFFFFFFFFFFFFFFF,
};

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

static void check64(uint64_t x)
{
    uint64_t s = isqrt_64(x);
    assert(s * s <= x);
    // assert((s+1) * (s+1) > x);
    // But avoid overflows!
    assert(x / (s + 1) < (s + 1));
    printf("ISQRT64(%" PRIu64 ") = %" PRId64 "\n", x, s);
}

int main(void)
{
    for (size_t i = 0; i < DIM(tests64); i++)
        check64(tests64[i]);
    return(0);
}

#endif /* USE_INTERACTIVE_TEST */
#endif /* TEST */
