/*
@(#)File:           randseed.c
@(#)Purpose:        Generate a 4-byte pseudo-random seed
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018-2021
@(#)Derivation:     randseed.c 1.5 2021/04/28 01:10:25
*/

/*TABSTOP=4*/

#define _DARWIN_C_SOURCE

#include "posixver.h"
#include "randseed.h"
#include "stderr.h"
#include "kludge.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Configuration:
** RS4_USE_DEV_RANDOM    -- Value from reading /dev/random
** RS4_USE_DEV_URANDOM   -- Value from reading /dev/urandom
** RS4_USE_ARC4RANDOM    -- Value from arc4random()
** RS4_USE_CLOCK_GETTIME -- Value from mixing clock_gettime() and getpid() and 16-bit CRC
** RS4_USE_GETTIMEOFDAY  -- Value from mixing gettimeofday() and getpid() and 16-bit CRC
** RS4_USE_TIME_GETPID   -- Value from mixing time() and getpid() and 16-bit CRC
**
** RS4_NO_INLINE_FUNCTIONS -- Generate convenience functions
**
** Of these, the first three are preferable, though opening and reading a device
** might be deemed 'slow'.
** Using clock_gettime() or gettimeofday() mixes and matches sub-second values with
** the Unix time.
** Using time() and getpid() is the least satisfactory, but is better than using
** either on its own.
*/

#ifdef RS4_NO_INLINE_FUNCTIONS

uint32_t random_seed_uint32(void)
{
    uint32_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

int32_t random_seed_sint32(void)
{
    int32_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

uint64_t random_seed_uint64(void)
{
    int64_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

int64_t random_seed_sint64(void)
{
    uint64_t rv;
    random_seed_bytes(sizeof(rv), &rv);
    return rv;
}

#endif /* RS4_NO_INLINE_FUNCTIONS */

#undef RS4_SELECTED
#undef RS4_RANDOM_DEV
#undef RS4_RANDOM_FILL

#if !defined(RS4_SELECTED) && defined(RS4_USE_ARC4RANDOM)
#define RS4_SELECTED

#include <string.h>

static inline size_t min_size(size_t a, size_t b) { return (a < b) ? a : b; }

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using arc4random()");
    char *buffer = data;
    while (size > 0)
    {
        uint32_t rv = arc4random();
        size_t   nb = min_size(size, sizeof(rv));
        memcpy(buffer, &rv, nb);
        size -= nb;
    }
}
#endif /* RS4_USE_ARC4RANDOM */

#if !defined(RS4_SELECTED) && defined(RS4_USE_CLOCK_GETTIME)
#define RS4_SELECTED
#define RS4_RANDOM_FILL

static void random_seed_fill(size_t size, void *data, size_t seed_size, void *seed_data);

#include <time.h>

#undef RS4_CLOCK_NAME
#if defined(CLOCK_MONOTONIC)
#define RS4_CLOCK_TYPE CLOCK_MONOTONIC
#define RS4_CLOCK_NAME "CLOCK_MONOTONIC"
#else
#define RS4_CLOCK_TYPE CLOCK_REALTIME
#define RS4_CLOCK_NAME "CLOCK_REALTIME"
#endif

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using clock_gettime(), " RS4_CLOCK_NAME ", getpid() and 16-bit CRC");
    struct seed
    {
        struct timespec tv;
        pid_t pid;
    } buffer;
    if (clock_gettime(RS4_CLOCK_TYPE, &buffer.tv) < 0)
        err_syserr("clock_gettime(%s): ", RS4_CLOCK_NAME);
    buffer.pid = getpid();
    random_seed_fill(size, data, sizeof(buffer), &buffer);
}
#endif /* RS4_USE_CLOCK_GETTIME */

#if !defined(RS4_SELECTED) && defined(RS4_USE_GETTIMEOFDAY)
#define RS4_SELECTED
#define RS4_RANDOM_FILL

static void random_seed_fill(size_t size, void *data, size_t seed_size, void *seed_data);

#include <sys/time.h>

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using gettimeofday() and getpid() and 16-bit CRC");
    struct seed
    {
        struct timeval tv;
        pid_t pid;
    } buffer;
    if (gettimeofday(&buffer.tv, 0) < 0)
        err_syserr("gettimeofday(): ");
    buffer.pid = getpid();
    random_seed_fill(size, data, sizeof(buffer), &buffer);
}
#endif /* RS4_USE_GETTIMEOFDAY */

#if !defined(RS4_SELECTED) && defined(RS4_USE_TIME_GETPID)
#define RS4_SELECTED
#define RS4_RANDOM_FILL

static void random_seed_fill(size_t size, void *data, size_t seed_size, void *seed_data);

#include <time.h>

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using time() and getpid() and 16-bit CRC");
    struct seed
    {
        time_t t0;
        pid_t  p0;
    } buffer = { time(0), getpid() };
    random_seed_fill(size, data, sizeof(buffer), &buffer);
}
#endif /* RS4_USE_TIME_GETPID */

#ifdef RS4_RANDOM_FILL

#include <string.h>
#include "crc.h"

static inline size_t min_size(size_t a, size_t b) { return (a < b) ? a : b; }

static void random_seed_fill(size_t size, void *data, size_t seed_size, void *seed_data)
{
    uint16_t seed[3] =
    {
        crc_forward(seed_data, seed_size, CRC_CCITT),
        crc_forward(seed_data, seed_size, CRC_16),
        crc_reverse(seed_data, seed_size, CRC_CCITT),
    };
    char *buffer = data;
    while (size > 0)
    {
        int32_t rv = jrand48(seed);
        size_t  nb = min_size(size, sizeof(rv));
        memcpy(buffer, &rv, nb);
        size -= nb;
    }
}

#endif /* RS4_RANDOM_FILL */

#if !defined(RS4_SELECTED) && defined(RS4_USE_DEV_URANDOM)
#define RS4_SELECTED
#define RS4_RANDOM_DEV
static void random_seed_dev(const char *device, size_t size, void *data);

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using /dev/urandom");
    random_seed_dev("/dev/urandom", size, data);
}
#endif /* RS4_USE_DEV_URANDOM */

/* Default - assume /dev/random is available */
#if !defined(RS4_SELECTED) /* && defined(RS4_USE_DEV_RANDOM) */
#define RS4_SELECTED
#define RS4_RANDOM_DEV
static void random_seed_dev(const char *device, size_t size, void *data);

void random_seed_bytes(size_t size, void *data)
{
    FEATURE_FILE("random_seed_bytes() using /dev/random");
    random_seed_dev("/dev/random", size, data);
}
#endif /* RS4_USE_DEV_RANDOM */

#if defined(RS4_RANDOM_DEV)

#include <fcntl.h>

static void random_seed_dev(const char *device, size_t size, void *data)
{
    int fd = open(device, O_RDONLY);
    if (fd < 0)
        err_syserr("failed to open %s for reading: ", device);
    ssize_t nread = read(fd, data, size);
    if (nread != (ssize_t)size)
        err_error("unexpected short read %zu bytes (out of %zu) on %s: ",
                  nread, size, device);
    close(fd);
}
#endif /* RS4_SELECTED */

#ifdef TEST

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>       /* nanosleep() */
#include <unistd.h>

static const char optstr[] = "c:hn:V";
static const char usestr[] = "[-hV][-c count][-n naptime]";
static const char hlpstr[] =
    "  -c count    Number of iterations (default 1000)\n"
    "  -h          Print this help message and exit\n"
    "  -n naptime  Interval between attempts in nanoseconds (default 10000000)\n"
    "  -V          Print version information and exit\n"
    ;

int main(int argc, char **argv)
{
    long count = 1000;
    long naptime = 10000000;
    err_setarg0(argv[0]);

    int opt;
    while ((opt = getopt(argc, argv, optstr)) != -1)
    {
        switch (opt)
        {
        case 'c':
            count = strtol(optarg, NULL, 0);
            if (count <= 0)
                err_error("Count must be a positive number (not %s)\n", optarg);
            break;
        case 'h':
            err_help(usestr, hlpstr);
            /*NOTREACHED*/
        case 'n':
            naptime = strtol(optarg, NULL, 0);
            if (naptime <= 0 || naptime >= 1000000000)
                err_error("Naptime must be a positive number less than 1,000,000,000 (not %s)\n", optarg);
            break;
        case 'V':
            err_version("PROG", &"@(#)$Revision: 1.5 $ ($Date: 2021/04/28 01:10:25 $)"[4]);
            /*NOTREACHED*/
        default:
            err_usage(usestr);
            /*NOTREACHED*/
        }
    }

    struct timespec ts = { .tv_sec = 0, .tv_nsec = naptime };
    for (long i = 0; i < count; i++)
    {
        printf("%5ld: 0x%.8" PRIX32 "\n", i, random_seed_uint32());
        nanosleep(&ts, NULL);
    }

    return 0;
}
#endif /* TEST */
