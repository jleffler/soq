/*
@(#)File:           timeval_math.c
@(#)Purpose:        Add, subtract, compare two struct timeval values
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2019-2024
@(#)Derivation:     timeval_math.c 2.2 2024/04/04 03:22:36
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "timeval_math.h"

enum { US_PER_SECOND = 1000000 };

void sub_timeval(struct timeval t_old, struct timeval t_new, struct timeval *td)
{
    td->tv_usec = t_new.tv_usec - t_old.tv_usec;
    td->tv_sec  = t_new.tv_sec - t_old.tv_sec;
    if (td->tv_sec > 0 && td->tv_usec < 0)
    {
        td->tv_usec += US_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_usec > 0)
    {
        td->tv_usec -= US_PER_SECOND;
        td->tv_sec++;
    }
}

void add_timeval(struct timeval t_old, struct timeval t_new, struct timeval *td)
{
    td->tv_usec = t_new.tv_usec + t_old.tv_usec;
    td->tv_sec  = t_new.tv_sec + t_old.tv_sec;
    if (td->tv_usec >= US_PER_SECOND)
    {
        td->tv_usec -= US_PER_SECOND;
        td->tv_sec++;
    }
    else if (td->tv_usec <= -US_PER_SECOND)
    {
        td->tv_usec += US_PER_SECOND;
        td->tv_sec--;
    }
}

int cmp_timeval(struct timeval t1, struct timeval t2)
{
    if (t1.tv_sec < t2.tv_sec)
        return -1;
    else if (t1.tv_sec > t2.tv_sec)
        return +1;
    else if (t1.tv_usec < t2.tv_usec)
        return -1;
    else if (t1.tv_usec > t2.tv_usec)
        return +1;
    else
        return 0;
}

#ifdef TEST

#error No test yet created

#endif /* TEST */
