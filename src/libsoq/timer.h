/*
@(#)File:           timer.h
@(#)Purpose:        Timing package for multiple systems
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1993-2019
@(#)Derivation:     timer.h 3.1 2019/08/26 05:23:27
*/

/*TABSTOP=4*/

#ifndef TIMER_H
#define TIMER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stddef.h> /* size_t */

/* Machine-independent time format */
struct Time
{
    long    seconds;        /* Time in whole seconds */
    long    nanoseconds;    /* Sub-seconds in nanoseconds */
};

typedef struct Time Time;

struct Clock
{
    Time    t1;             /* Start time */
    Time    t2;             /* Stop time */
#ifndef TIMER_VERSION_1
    char    buffer[24];     /* Buffer for formatting elapsed time */
#endif /* !TIMER_VERSION_1 */
};

typedef struct Clock Clock;

extern void     clk_diff(Time * t1, Time * t2, long *sec, long *nsec);
extern void     clk_init(Clock *clk);
extern void     clk_start(Clock *clk);
extern void     clk_stop(Clock *clk);

extern char    *clk_elapsed_ms(Clock *clk, char *buffer, size_t buflen);
extern char    *clk_elapsed_us(Clock *clk, char *buffer, size_t buflen);
extern char    *clk_elapsed_ns(Clock *clk, char *buffer, size_t buflen);

#ifndef TIMER_VERSION_1
extern char    *clk_fmt_elapsed_ms(Clock *clk);
extern char    *clk_fmt_elapsed_us(Clock *clk);
extern char    *clk_fmt_elapsed_ns(Clock *clk);
#endif /* !TIMER_VERSION_1 */

#endif /* TIMER_H */
