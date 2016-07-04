/*
@(#)File:           timer.h
@(#)Purpose:        Timing package for multiple systems
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1993,1997,2003,2006,2008,2015-16
@(#)Derivation:     timer.h 2.9 2015/02/21 17:32:35
*/

/*TABSTOP=4*/

#ifndef TIMER_H
#define TIMER_H

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
};

typedef struct Clock Clock;

extern void     clk_diff(Time * t1, Time * t2, long *sec, long *nsec);
extern void     clk_init(Clock *clk);
extern void     clk_start(Clock *clk);
extern void     clk_stop(Clock *clk);
extern char    *clk_elapsed_ms(Clock *clk, char *buffer, size_t buflen);
extern char    *clk_elapsed_us(Clock *clk, char *buffer, size_t buflen);
extern char    *clk_elapsed_ns(Clock *clk, char *buffer, size_t buflen);

#endif /* TIMER_H */
