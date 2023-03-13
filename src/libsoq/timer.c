/*
@(#)File:           timer.c
@(#)Purpose:        Simple timing package for multiple systems
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1993-2023
@(#)Derivation:     timer.c 3.2 2023/02/02 23:16:33
*/

/*TABSTOP=4*/

/*
** Configuration (listed in order of preference):
** HAVE_CLOCK_GETTIME: Use POSIX.4 (POSIX.1:1996) clock_gettime()
** HAVE_GETTIMEOFDAY:  Use gettimeofday (BSD, SVR4, Unix-98)
** HAVE_TIMES:         Use times (System V - deprecated)
** HAVE_FTIME:         Use ftime (Antique Unix - deprecated)
** HAVE_CLOCK:         Use clock (ISO C 1990)
** If nothing defined: Use time() with 1 second resolution (ISO C 1990)
** Note 1: since ISO C defines clock(), there should never be any need
** to use time().
** Note 2: support for AIX 3.x gettimer function removed 2001-03-09; AIX
** 3.x has not been supported by IBM for a while now, and AIX 4.x has
** gettimeofday() -- and AIX 3.x may have had gettimeofday() too.
** Note 3: support for GetTickCount removed 2001-03-09.  It might be
** needed on Windows 95, but on NT the clock() function is used in
** preference and is probably available to all Win32 platforms.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define HAVE_GETTIMEOFDAY       /* Sensible default */
#endif /* HAVE_CONFIG_H */

/*===============================================================*/

/*
** Configure POSIX and X/Open feature test macros before including any
** system headers.  Note, do not need both <time.h> and <sys/time.h>, so
** don't need to test for config.h and TIME_WITH_SYS_TIME macro.
*/

#undef JLSS_NEED_TIME_H
#undef JLSS_NEED_SYS_TIME_H

#if defined HAVE_CLOCK_GETTIME

    /*
    ** POSIX 1003.4 clock_gettime().
    ** Requires: -lposix4 when linking on Solaris 2.6 or 7.
    ** Requires: LIBS=-lposix4 in environment when autoconfiguring.
    */
    #include "posixver.h"
    #define JLSS_NEED_TIME_H    1

#elif defined HAVE_GETTIMEOFDAY

    /**
    ** gettimeofday() is not a POSIX 1003.1 function.  It is part of
    ** SUS-98, and is therefore enabled by _XOPEN_SOURCE 500
    ** Or in SUSv3 with X/Open source 600.
    */
    #include "posixver.h"
    #define JLSS_NEED_SYS_TIME_H    1

#elif defined HAVE_FTIME

    /* Uses #include <sys/timeb.h> and neither <time.h> nor <sys/time.h> */

#elif defined HAVE_TIMES

    /* Uses #include <sys/times.h> and neither <time.h> nor <sys/time.h> */

#elif defined HAVE_CLOCK

    #define JLSS_NEED_TIME_H    1

#else

    #define JLSS_NEED_TIME_H    1

#endif /* Various clock types */

#include "timer.h"      /* Configuration independent */

#include <stdio.h>
#include <sys/types.h>

#ifdef JLSS_NEED_TIME_H
#include <time.h>
#endif /* JLSS_NEED_TIME_H */

#ifdef JLSS_NEED_SYS_TIME_H
#include <sys/time.h>
#endif /* JLSS_NEED_SYS_TIME_H */

#undef JLSS_NEED_TIME_H
#undef JLSS_NEED_SYS_TIME_H

/*===============================================================*/

#define NS_PER_SECOND   1000000000  /* nanoseconds per second */
#define US_PER_SECOND   1000000     /* microseconds per second */
#define MS_PER_SECOND   1000        /* milliseconds per second */

/* Rely on ISO C string concatenation */
extern const char jlss_id_timer_type[];
#define TIMER_TYPE(str) const char jlss_id_timer_type[] = "@(#)Using " str

/*
** clk_get() - sole machine-dependent routine.
** Gets time in seconds and nanoseconds since reference time.
** Reference time is typically boot time or The Epoch (1970-01-01 00:00:00).
** Its absolute value is not necessarily significant, but differences
** between successive values are.
*/

#if defined HAVE_CLOCK_GETTIME

TIMER_TYPE("POSIX 1003.4 clock_gettime()");

static void
clk_get(Time *t)
{
    struct timespec mt;

    clock_gettime(CLOCK_REALTIME, &mt);
    t->seconds = mt.tv_sec;
    t->nanoseconds = mt.tv_nsec;
}

#elif defined HAVE_GETTIMEOFDAY

TIMER_TYPE("Single Unix Specification (Unix-98) gettimeofday()");

static void
clk_get(Time *t)
{
    struct timeval mt;

    gettimeofday(&mt, (struct timezone *)0);
    t->seconds = mt.tv_sec;
    t->nanoseconds = mt.tv_usec * (NS_PER_SECOND / US_PER_SECOND);
}

#elif defined HAVE_FTIME

#include <sys/timeb.h>

TIMER_TYPE("Version 7 Unix ftime()");

static void
clk_get(Time *t)
{
    struct timeb mt;

    ftime(&mt);
    t->seconds = mt.time;
    t->nanoseconds = mt.millitm * (NS_PER_SECOND / MS_PER_SECOND);
}

#elif defined HAVE_TIMES

#include <sys/times.h>
#include <limits.h>             /* CLK_TCK */

#ifndef CLK_TCK
#ifdef HZ
#define CLK_TCK HZ
#else
#define CLK_TCK 100     /* Take a guess -- not good but works OK mostly */
static const char kludge[] = "@(#)KLUDGE - assume CLK_TCK is 100";
#endif /* HZ */
#endif /* CLK_TCK */

TIMER_TYPE("POSIX.1 times()");

static void
clk_get(Time *t)
{
    struct tms  mt;
    clock_t     sys_t;
    long        us;

    /* CLK_TCK is present in POSIX but marked obsolescent. */
    /* POSIX_SOURCE should use sysconf(_SC_CLK_TCK).       */
    /* Scaling algorithm OK for CLK_TCK of 60 or 100.      */
    sys_t = times(&mt);
    t->seconds = (sys_t / CLK_TCK);
    us = ((sys_t % CLK_TCK) * US_PER_SECOND) / CLK_TCK;
    t->nanoseconds = us * (NS_PER_SECOND / US_PER_SECOND);
}

#elif defined HAVE_CLOCK

#ifndef CLOCKS_PER_SEC
error HAVE_CLOCK defined but CLOCKS_PER_SEC undefined
#endif

/*
** On NT, CLOCKS_PER_SEC is 1000, and if you multiply by NS_PER_SECOND
** before dividing by CLOCKS_PER_SEC, you are likely to get overflows
** and nonsense on 32-bit machines.  Hence the compile time check
** (not reliable for cross-compilation, of course) and alternative
** expressions for calculating the result.  Note how the HAVE_TIMES
** code above uses different assumptions and algorithms for roughly
** the same net effect.
*/

TIMER_TYPE("ISO C 1990 clock()");

static void
clk_get(Time *t)
{
    long        us;
    clock_t cnt;

    cnt = clock();
    t->seconds = cnt / CLOCKS_PER_SEC;
    us = (cnt % CLOCKS_PER_SEC);
#if NS_PER_SECOND % CLOCKS_PER_SEC == 0 && NS_PER_SECOND > CLOCKS_PER_SEC
    t->nanoseconds = us * (NS_PER_SECOND/CLOCKS_PER_SEC);
#else
    t->nanoseconds = (long)(((double)us*NS_PER_SECOND)/CLOCKS_PER_SEC);
#endif
}

#else

TIMER_TYPE("ISO C (POSIX.1) time() -- 1 second resolution");

/* No fine-resolution timing defined -- use time() */
static void
clk_get(Time *t)
{
    t->seconds = time((time_t)0);
    t->nanoseconds = 0;
}

#endif /* HAVE_CLOCK_GETTIME, ... */

/* ============== End of Platform-Dependent Coding ============== */

/* Calculate difference between two times */
void
clk_diff(Time *t1, Time *t2, long *sec, long *nsec)
{
    long        s;
    long        n;

    s = t2->seconds - t1->seconds;
    n = t2->nanoseconds - t1->nanoseconds;
    if (n < 0)
    {
        n += NS_PER_SECOND;
        s--;
    }
    *sec = s;
    *nsec = n;
}

/* Format time as seconds and subseconds */
static char *
clk_format(long sec, long subsec, char *buffer, size_t buflen, const char *fmt)
{
    snprintf(buffer, buflen, fmt, sec, subsec);
    return(buffer);
}

/* Initialize a Clock structure */
void
clk_init(Clock *clk)
{
    clk->t1.seconds = 0;
    clk->t1.nanoseconds = 0;
    clk->t2.seconds = 0;
    clk->t2.nanoseconds = 0;
    clk->buffer[0] = '\0';
}

/* Start a clock (record the stop time in clk->t1) */
void
clk_start(Clock *clk)
{
    clk_get(&clk->t1);
    clk->buffer[0] = '\0';
}

/* Stop a clock (record the stop time in clk->t2) */
void
clk_stop(Clock *clk)
{
    clk_get(&clk->t2);
    clk->buffer[0] = '\0';
}

/* Return elapsed time as string in seconds and milliseconds */
char *
clk_elapsed_ms(Clock *clk, char *buffer, size_t buflen)
{
    long sec;
    long nsec;

    /* The % MS_PER_SECOND operation suppresses a warning from GCC 9.1.0 */
    clk_diff(&clk->t1, &clk->t2, &sec, &nsec);
    nsec = (nsec / (NS_PER_SECOND / MS_PER_SECOND)) % MS_PER_SECOND;
    return(clk_format(sec, nsec, buffer, buflen, "%ld.%03ld"));
}

/* Return elapsed time as string in seconds and microseconds */
char *
clk_elapsed_us(Clock *clk, char *buffer, size_t buflen)
{
    long sec;
    long nsec;

    /* The % US_PER_SECOND operation suppresses a warning from GCC 9.1.0 */
    clk_diff(&clk->t1, &clk->t2, &sec, &nsec);
    nsec = (nsec / (NS_PER_SECOND / US_PER_SECOND)) % US_PER_SECOND;
    return(clk_format(sec, nsec, buffer, buflen, "%ld.%06ld"));
}

/* Return elapsed time as string in seconds and nanoseconds */
char *
clk_elapsed_ns(Clock *clk, char *buffer, size_t buflen)
{
    long sec;
    long nsec;

    /* The % NS_PER_SECOND operation suppresses a warning from GCC 9.1.0 */
    clk_diff(&clk->t1, &clk->t2, &sec, &nsec);
    nsec %= NS_PER_SECOND;
    return(clk_format(sec, nsec, buffer, buflen, "%ld.%09ld"));
}

#ifndef TIMER_VERSION_1
/* Simpler formatting interface because of structure containing buffer */
/* Old interface is retained, so recompilation is sufficient for old code */

char *clk_fmt_elapsed_ms(Clock *clk)
{
    return clk_elapsed_ms(clk, clk->buffer, sizeof(clk->buffer));
}

char *clk_fmt_elapsed_us(Clock *clk)
{
    return clk_elapsed_us(clk, clk->buffer, sizeof(clk->buffer));
}

char *clk_fmt_elapsed_ns(Clock *clk)
{
    return clk_elapsed_ns(clk, clk->buffer, sizeof(clk->buffer));
}

/* Return pointer to formatted string, formatting in nanoseconds if need be */
char *
clk_fmt_elapsed_str(Clock *clk)
{
    if (clk->buffer[0] == '\0')
        clk_fmt_elapsed_ns(clk);
    return clk->buffer;
}

double
clk_fmt_elapsed_dbl(Clock *clk)
{
    long sec;
    long nsec;
    clk_diff(&clk->t1, &clk->t2, &sec, &nsec);
    return((double)nsec / NS_PER_SECOND + (double)sec);
}

#endif /* !TIMER_VERSION_1 */

#ifdef TEST

#include <stdlib.h>

static size_t counter = 0;
static void increment(void)
{
    counter += rand();
}

int
main(void)
{
    Clock       clk;
    size_t      max = 100000000;
    char *(*fmt[3])(Clock *clk) =
    {
        clk_fmt_elapsed_ms, clk_fmt_elapsed_us, clk_fmt_elapsed_ns
    };

    clk_init(&clk);

    for (int i = 0; i < 20; i++)
    {
        clk_start(&clk);
        for (size_t j = 0; j < max; j++)
            increment();
        clk_stop(&clk);
        /* Test the old functions */
        char buf1[32];
        char buf2[32];
        char buf3[32];
        char *p1 = clk_elapsed_ms(&clk, buf1, sizeof(buf1));
        char *p2 = clk_elapsed_us(&clk, buf2, sizeof(buf2));
        char *p3 = clk_elapsed_ns(&clk, buf3, sizeof(buf3));
        /* Test the new functions */
        char *p4 = (*fmt[i % 3])(&clk);
        double p5 = clk_fmt_elapsed_dbl(&clk);
        char *p6 = clk_fmt_elapsed_str(&clk);
        printf("Clock: %s = %s = %s = %-16s %16.9lf %-16s (%zu)\n", p1, p2, p3, p4, p5, p6, counter);
    }
    return(0);
}

#endif /* TEST */
