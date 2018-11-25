/*
@(#)File:           microsleep.c
@(#)Purpose:        Implement platform-independent micro_sleep()
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2018
*/

/*TABSTOP=4*/

/*
** While macOS, and Mac OS X before it, support usleep(), it is not
** available on Cygwin (at least under compilation options requesting
** POSIX 2008 support).  Consequently, there is a portability issue for
** code written using usleep(), which has a convenient interface.  The
** micro_sleep() function provides an interface compatible with usleep()
** but implements it using nanosleep() if it is available or usleep() if
** it is available, failing if neither is documented as available.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "microsleep.h"
#include "kludge.h"
#include <time.h>

enum { US_PER_SEC = 1000000 };
enum { NS_PER_US  = 1000 };

#if defined(HAVE_NANOSLEEP)

int micro_sleep(useconds_t usecs)
{
    FEATURE("micro_sleep() implemented using nanosleep()");
    struct timespec ts;
    ts.tv_sec = usecs / US_PER_SEC;
    ts.tv_nsec = (usecs % US_PER_SEC) * NS_PER_US;
    return nanosleep(&ts, 0);
}

#elif defined(HAVE_USLEEP)

int micro_sleep(useconds_t usecs)
{
    FEATURE("micro_sleep() implemented using usleep()");
    return usleep(usecs);
}

#else

#error Neither HAVE_NANOSLEEP nor HAVE_USLEEP defined

#endif
