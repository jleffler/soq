/*
@(#)File:           prng48.c
@(#)Purpose:        Generate pseudo-random integers over a specified range
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2022
@(#)Derivation:     prng48.c 1.2 2022/06/27 15:56:46
*/

/*TABSTOP=4*/

/*
** Using nrand48() and a private seed avoids interfering with any other
** PRNG at work.  Using types long and unsigned short matches what POSIX
** says for the types.  The range of values generated is limited to the
** unsigned 31-bit values. Thus the equivalent of RAND_MAX is PRNG48_MAX.
** POSIX does not seem to stipulate the initial value for the seed.  On
** macOS, the value is documented as 0x1234ABCD330E.  This is equivalent
** to calling srand48(0x1234ABCD).
*/

#include "posixver.h"
#include "prng48.h"       /* SSC: Self-sufficiency check */
#include <stdlib.h>
#include <string.h>

/* This is the default seed for all the xrand48() functions */
static unsigned short prng48_data[3] = { 0x330EU, 0xABCDU, 0x1234U };

void prng48_seed(unsigned short seed[3])
{
    memcpy(prng48_data, seed, sizeof(prng48_data));
}

long prng48_rand(long lo, long hi)
{
    long range = hi - lo + 1;
    long residue = PRNG48_MAX - PRNG48_MAX % range;
    long result;
    while ((result = nrand48(prng48_data)) > residue)
        ;
    return lo + result % range;
}

#ifdef TEST
#error Compile "test.prng48.c" to test this code
#endif
