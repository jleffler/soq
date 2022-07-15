/*
@(#)File:           timespec_math.c
@(#)Purpose:        Add, subtract, compare two struct timespec values
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015-2019
@(#)Derivation:     timespec_math.c 2.2 2019/08/16 05:25:57
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "timespec_math.h"

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

void add_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec + t1.tv_nsec;
    td->tv_sec  = t2.tv_sec + t1.tv_sec;
    if (td->tv_nsec >= NS_PER_SECOND)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
    else if (td->tv_nsec <= -NS_PER_SECOND)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
}

int cmp_timespec(struct timespec t1, struct timespec t2)
{
    if (t1.tv_sec < t2.tv_sec)
        return -1;
    else if (t1.tv_sec > t2.tv_sec)
        return +1;
    else if (t1.tv_nsec < t2.tv_nsec)
        return -1;
    else if (t1.tv_nsec > t2.tv_nsec)
        return +1;
    else
        return 0;
}

#ifdef TEST

#error No test yet created

#endif /* TEST */
