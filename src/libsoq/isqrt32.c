/*
@(#)File:           isqrt.c
@(#)Purpose:        Integer square root calculation
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1991-92,1997,2005,2008,2011,2015
@(#)Derivation:     isqrt.c 1.10 2015/06/01 02:33:11
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
int32_t isqrt_32(uint32_t v)
{
    uint32_t t = 1L << 30;
    uint32_t r = 0;
    uint32_t s;

#undef STEP
#define STEP(k) \
    s = t + r; \
    r >>= 1; \
    if (s <= v) { \
        v -= s; \
        r |= t; \
    }

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
    return (int32_t)r;
}

#if defined(TEST)
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#ifdef USE_INTERACTIVE_TEST

int main(void)
{
    uint32_t l;
    char     buf[100];

    while (printf("gimme a number> ") > 0 &&
           fgets(buf, sizeof buf, stdin) != NULL)
    {
        /* should use strtoul here but some do not have it */
        if (sscanf(buf, "0x%" SCNx32, &l) != 1 &&
            sscanf(buf, "0%"  SCNo32, &l) != 1 &&
            sscanf(buf, "%"   SCNu32, &l) != 1 &&
            sscanf(buf, "%"   SCNx32, &l) != 1)
            (void)printf("that was not a number\n");
        else
        {
            uint32_t r = isqrt_32(l);
            assert(r * r <= l);
            // assert((r+1) * (r+1) > l);
            // But avoid overflows!
            assert(l / (r + 1) < (r + 1));
            (void)printf("root(%" PRIu32 ") => %" PRIu32 " sqrt(%" PRIu32 ") => %.17g\n",
                          l, r, l, sqrt((double)l));
        }
    }
    putchar('\n');
    return(0);
}

#else

static const uint32_t tests[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 24, 25, 9999, 10000,
    4294705155, 4294705156, 4294705157, 0xFFFFFFFE, 0xFFFFFFFF,
};

#define DIM(x)  (sizeof(x)/sizeof(*(x)))

int main(void)
{
    for (size_t i = 0; i < DIM(tests); i++)
    {
        uint32_t r = isqrt_32(tests[i]);
        assert(r * r <= tests[i]);
        // assert((r+1) * (r+1) > tests[i]);
        // But avoid overflows!
        assert(tests[i] / (r + 1) < (r + 1));
        printf("ISQRT(%" PRIu32 ") = %" PRId32 "\n", tests[i], r);
    }
    return(0);
}

#endif /* USE_INTERACTIVE_TEST */
#endif /* TEST */
