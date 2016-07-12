/* Modern POSIX code analogous to the setitimer() code in isprime.c */
/*
** Using create_timer(), destroy_timer(), timer_settime(), along with
** struct itimerspec (nanosecond resolution), timer_t, and struct sigevent.
*/

#include "posixver.h"
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include "stderr.h"
#include "posix-timer.h"    /* Make-up for Mac OS X */

static int icounter = 0;
static timer_t tmr = 0;
static int tmr_init = 0;

static void alarm_handler(int signum)
{
    assert(signum == SIGALRM);
    if (++icounter % 60 == 0)
        write(STDOUT_FILENO, ".\n", 2);
    else
        write(STDOUT_FILENO, ".", 1);
}

static int mk_interval_timer(void)
{
    int rc = 0;
    if (tmr_init == 0)
    {
        struct sigevent ev =
        {
            .sigev_notify    = SIGEV_SIGNAL,
            .sigev_signo     = SIGALRM,
            .sigev_value     = { .sival_int = 0 },
            .sigev_notify_function = 0,
            .sigev_notify_attributes = 0,
        };
        rc = timer_create(CLOCK_REALTIME, &ev, &tmr);
        if (rc != 0)
            err_sysrem("timer_create() failed for CLOCK_REALTIME");
        else
            tmr_init = 1;
    }
    return rc;
}

static int rm_interval_timer(void)
{
    int rc = 0;
    if (tmr_init != 0)
    {
        rc = timer_destroy(tmr);
        if (tmr != 0)
            err_sysrem("timer_destroy() failed");
        else
            tmr_init = 0;
    }
    return rc;
}

static int set_interval_timer(int interval)
{
    int rc = 0;
    assert(interval >= 0);
    if (tmr_init == 0 && interval > 0)
    {
        if ((rc = mk_interval_timer()) != 0)
            return rc;
    }
    if (tmr_init != 0)
    {
        struct itimerspec its =
        {
            .it_value =    { .tv_sec = interval, .tv_nsec = 0 },
            .it_interval = { .tv_sec = interval, .tv_nsec = 0 },
        };
        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_handler = alarm_handler;
        sa.sa_flags = SA_RESTART;
        if ((rc = sigaction(SIGALRM, &sa, 0)) != 0)
            err_sysrem("sigaction() failed");
        else if ((rc = timer_settime(tmr, 0, &its, 0)) != 0)
            err_sysrem("timer_settime() failed");
        if (interval == 0)
            rc = rm_interval_timer();
    }
    return rc;
}


#ifndef NO_PROGRESS_REPORTING
#define PROGRESS_REPORT(x)  (x)
#else
#define PROGRESS_REPORT(x)  ((void)0)
#endif

#include "timer.h"
#include <stdlib.h>

extern void bake_off(int seed, int count);
extern int check_number(unsigned v);

extern void bake_off(int seed, int count)
{
    srand(seed);
    Clock clk;
    clk_init(&clk);
    printf("Bake-off...warning this could take three minutes or more.\n");
    PROGRESS_REPORT(set_interval_timer(1));

    clk_start(&clk);

    int failures = 0;

    /* Check numbers to 1000 */
    for (unsigned v = 1; v < 1000; v++)
    {
        if (check_number(v))
            failures++;
    }

    /* Check random numbers */
    for (int i = 0; i < count; i++)
    {
        unsigned v = rand();
        if (check_number(v))
            failures++;
    }

    clk_stop(&clk);
    PROGRESS_REPORT(set_interval_timer(0));

    PROGRESS_REPORT(putchar('\n'));
    char buffer[32];
    (void)clk_elapsed_us(&clk, buffer, sizeof(buffer));
    if (failures == 0)
        printf("== PASS == %s s\n", buffer);
    else
        printf("!! FAIL !! %d failures in %s s\n", failures, buffer);
}
