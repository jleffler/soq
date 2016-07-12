/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Data types and declarations for create_timer() et al
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_POSIX_TIMER_H
#define JLSS_ID_POSIX_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_posix_timer_h[];
const char jlss_id_posix_timer_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <pthread.h>
#include <signal.h>
#include <time.h>

/* Defines correct for Mac OS X 10.11.5 */
//#define NO_UNION_SIGVAL
//#define NO_STRUCT_SIGEVENT
#define NO_TYPE_TIMER_T
#define NO_STRUCT_ITIMERSPEC

#ifdef NO_UNION_SIGVAL
union sigval
{
    int     sival_int;
    void   *sival_ptr;
};
#endif /* NO_UNION_SIGVAL */

#ifdef NO_STRUCT_SIGEVENT
struct sigevent
{
    enum { SIGEV_SIGNAL = 1, SIGEV_THREAD, SIGEV_NONE };    // sigev_notify
    int             sigev_notify;
    int             sigev_signo;
    union sigval    sigev_value;
    void          (*sigev_notify_function)(union sigval);
    pthread_attr_t *sigev_notify_attributes;
};
#endif /* NO_STRUCT_SIGEVENT */

#ifdef NO_TYPE_TIMER_T
typedef int timer_t;
#endif /* NO_TYPE_TIMER_T */

#ifdef NO_STRUCT_ITIMERSPEC
struct itimerspec
{
    struct timespec it_value;
    struct timespec it_interval;
};
#endif /* NO_STRUCT_ITIMERSPEC */

enum { CLOCK_REALTIME = 1, CLOCK_MONOTONIC };
enum { TIMER_ABSTIME = 1 };

extern int timer_create(int type, struct sigevent * restrict evp, timer_t * restrict trp);
extern int timer_destroy(timer_t tr);
extern int timer_settime(timer_t tr, int flags, const struct itimerspec * restrict its, struct itimerspec * restrict ots);
extern int timer_gettime(timer_t tr, struct itimerspec *its);
extern int timer_getoverrun(timer_t tr);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_POSIX_TIMER_H */
