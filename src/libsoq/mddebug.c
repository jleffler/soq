/*
@(#)File:           mddebug.c
@(#)Purpose:        Provide varargs support for debugging multiple subsystems
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2018
@(#)Derivation:     mddebug.c 3.19 2018/06/12 06:20:45
*/

/*TABSTOP=4*/
#include "posixver.h"
#undef DEBUG
#define DEBUG
#include "debug.h"
#include "stderr.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define USE_JLSS_GETSUBOPT
#define USE_JLSS_GETOPT
#include "getopt.h"
#include "strtoint.h"       /* strtoi() */

#define DB_ON           3
#define DB_OFF          0

static int           subsys_max   = 0;
static int          *subsys_debug = 0;
static char * const *subsys_names = 0;
static int           options = 0;

int db_mdsetoptions(int opts)
{
    int rv = options;
    options = opts;
    return rv;
}

/**************************************\
** MULTIPLE DEBUGGING SUBSYSTEMS CODE **
\**************************************/

/*
**  Returns current debug level.
*/
int db_mdgetdebug(int subsys)
{
    DB_MDTRACKING();
    return((subsys >= 0 && subsys < subsys_max) ? subsys_debug[subsys] : -1);
}

/*
**  Set new debug level.
**  Returns old debug level.
*/
int db_mdsetdebug(int subsys, int level)
{
    int             o = -1;

    if (subsys >= 0 && subsys < subsys_max)
    {
        o = subsys_debug[subsys];
        subsys_debug[subsys] = level;
        if (subsys == 0)
            db_setdebug(level);
    }
    return(o);
}

/*
** Set list of subsystem names
*/
void db_mdsubsysnames(char * const *names)
{
    char * const *np;
    int n_subsys = 0;

    subsys_names = names;
    for (np = names; *np != 0; np++)
        n_subsys++;
    if ((subsys_debug = (int *)calloc((size_t)n_subsys, sizeof(int))) == 0)
        err_error("out of memory for debugging system\n");
    subsys_max = n_subsys;
}

/*
** Parse the value of an argument (eg -D subsys1=3,subsys2=9),
** setting the relevant subsystems to the relevant debug levels.
** NB: argument is destroyed by getsubopt().
** Returns: 0 OK, -1 some fault occurred.
*/
int db_mdparsearg(char *arg)
{
    char         *vp;
    char         *ep;
    char * const *tp;
    int          subsys;
    int          level;
    static int   reported = 0;

    if (subsys_names == 0)
    {
        err_remark("no debug subsystem names have been defined\n");
        return(-1);
    }

    while (*arg != '\0')
    {
        if ((subsys = GETSUBOPT(&arg, subsys_names, &vp)) < 0)
        {
            err_remark("unrecognized debug subsystem (%s)\n", vp);
            if (reported++ == 0)
            {
                FILE *fp = db_getfileptr();
                fprintf(fp, "valid subsystems are:");
                for (tp = subsys_names; *tp != 0; tp++)
                    fprintf(fp, " %s", *tp);
                putc('\n', fp);
                return(-1);
            }
        }
        else if (vp == 0)
        {
            err_remark("debug specifications look like \"subsystem=4\", not %s\n",
                    subsys_names[subsys]);
            return(-1);
        }
        else if (strcmp(vp, "on") == 0)
            db_mdsetdebug(subsys, DB_ON);
        else if (strcmp(vp, "off") == 0)
            db_mdsetdebug(subsys, DB_OFF);
        else if ((level = strtoi(vp, &ep, 0)), ep == vp)
        {
            err_remark("invalid debug level (%s)\n", vp);
            return(-1);
        }
        else
            db_mdsetdebug(subsys, level);
    }
    return(0);
}

/*
**  Print debug information if subsys_debug[subsys] set at or above level.
*/
void db_mdprint(int subsys, int level, const char *fmt,...)
{
    if (subsys >= 0 && subsys < subsys_max && subsys_debug[subsys] >= level)
    {
        va_list         args;
        FILE *fp = db_getfileptr();
        fflush(stdout);
        flockfile(fp);
        fputs(db_indent(), fp);
        if (options & DB_OPT_PID)
            fprintf(fp, "%d:", (int)getpid());
        fprintf(fp, "%s: ", subsys_names[subsys]);
        va_start(args, fmt);
        vfprintf(fp, fmt, args);
        va_end(args);
        fflush(fp);
        funlockfile(fp);
    }
}

/*
**  Print debug information if subsys_debug[subsys] set at or above level.
*/
void db_mdprintloc(int subsys, int level, const char *file, int line,
                   const char *func, const char *fmt,...)
{
    if (subsys >= 0 && subsys < subsys_max && subsys_debug[subsys] >= level)
    {
        va_list         args;
        FILE *fp = db_getfileptr();
        fflush(stdout);
        flockfile(fp);
        fputs(db_indent(), fp);
        if (options & DB_OPT_PID)
            fprintf(fp, "%d:", (int)getpid());
        fprintf(fp, "%s:%d:%s():%s: ", file, line, func, subsys_names[subsys]);
        va_start(args, fmt);
        vfprintf(fp, fmt, args);
        va_end(args);
        fflush(fp);
        funlockfile(fp);
    }
}

#ifdef TEST

/* Thin ice: TRACE() is a function-like macro */
enum { TRACE, SUBSYS_1, SUBSYS_2, SUBSYS_3 };
static char ss_TRACE[]    = "TRACE";
static char ss_SUBSYS_1[] = "SUBSYS_1";
static char ss_SUBSYS_2[] = "SUBSYS_2";
static char ss_SUBSYS_3[] = "SUBSYS_3";

static char * const ss_names[] =
{
    ss_TRACE, ss_SUBSYS_1, ss_SUBSYS_2, ss_SUBSYS_3, 0
};

static void db_test(void)
{
    fprintf(stderr, "Should appear at indent = %d\n", db_newindent() + 1);
    MDTRACE((TRACE, 1, "This should have appeared at debug level %d; %d %f\n",
               1, 3, 3.141593));
    DB_MDTRACE(SUBSYS_1, 2, "This should have appeared at debug level %d; %d %f\n",
               2, 3, 3.141593);
    DB_MDTRACE(SUBSYS_2, 3, "This should have appeared at debug level %d; %d %f\n",
               3, 3, 3.141593);
    DB_MDTRACELOC(SUBSYS_3, 4, "This should have appeared at debug level %d; %d %f\n",
               4, 3, 3.141593);
    db_oldindent();
}

/* i does double duty as level and subsystem */
static void db_test1(int i)
{
    int subsys = ((i - i) > SUBSYS_3) ? SUBSYS_3 : i - 1;
    if (subsys < TRACE)
        subsys = TRACE;
    db_mdsetdebug(subsys, i);
    fprintf(stderr, "Debug level for subsystem %s is: %d\n", ss_names[subsys], db_mdgetdebug(subsys));
    db_test();
    db_setindent(i);
    db_test();
    db_setindent(0);
    db_test();
}

static void test_debug(int argc, char **argv)
{
    int             i;

    for (i = 0; i <= argc; i++)
        db_test1(i);

    if (argc > 0)
    {
        fprintf(stderr, "Recurse with argc = %d\n", argc - 1);
        test_debug(argc - 1, argv);
    }
}

int main(int argc, char **argv)
{
    db_mdsubsysnames(ss_names);
    if (argc <= 1)
        puts("It is more fun if you add arguments to the command line!");
    test_debug(argc, argv);
    return(0);
}

#endif /* TEST */
