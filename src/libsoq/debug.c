/*
@(#)File:           debug.c
@(#)Purpose:        Provide varargs support for debugging
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2019
@(#)Derivation:     debug.c 3.16 2019/05/03 18:11:35
*/

/*TABSTOP=4*/

#include "posixver.h"
#undef DEBUG
#define DEBUG
#include "debug.h"
#include "stderr.h"

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXINDENT   ((int)(sizeof(blanks) - 1) / 3)

static int      debug = 0;

static char     blanks[] = "                                                 ";
static char    *indent = &blanks[sizeof(blanks) - 1];
static int      inlevel = 0;
/* GNU C library does not allow you to initialize debugfp to stderr */
static FILE    *debugfp = 0;
static char     fn[256] = "/dev/stderr";
static int      options;

int db_setoptions(int opts)
{
    int rv = options;
    options = opts;
    return rv;
}

FILE *db_getfileptr(void)
{
    DB_TRACKING();
    if (debugfp == 0)
        debugfp = stderr;
    return debugfp;
}

/*
**  Set output file pointer
*/
void db_setfileptr(FILE * dbfp)
{
    if (dbfp != (FILE *)NULL)
    {
        if (debugfp != stdin && debugfp != stdout && debugfp != stderr)
            fclose(debugfp);
        debugfp = dbfp;
        strcpy(fn, "<unknown>");
    }
}

/*
**  Set output file name
*/
void db_setfilename(const char *nfn)
{
    FILE           *nfp;

    if (strcmp(nfn, fn) == 0)   /* Same as last time? */
        return;
    if ((nfp = fopen(nfn, "a+")) != (FILE *)NULL)
    {
        db_setfileptr(nfp);
        strncpy(fn, nfn, sizeof(fn) - 1);
        fn[sizeof(fn) - 1] = '\0';
    }
}

/*
**  Call as: db_print(level, format, ...);
**  Print debug information if debug flag set at or above level.
*/
void db_print(int level, const char *fmt, ...)
{
    if (debug >= level)
    {
        va_list args;
        FILE *fp = db_getfileptr();
        fflush(stdout);
        flockfile(fp);
        fputs(db_indent(), fp);
        if (options & DB_OPT_PID)
            fprintf(fp, "%d: ", (int)getpid());
        va_start(args, fmt);
        vfprintf(fp, fmt, args);
        va_end(args);
        fflush(fp);
        funlockfile(fp);
    }
}

/*
**  Call as: db_printloc(level, format, __FILE__, __LINE__, __func__, ...);
**  Print debug information if debug flag set at or above level.
*/
void db_printloc(int level, const char *file, int line, const char *func, const char *fmt, ...)
{
    if (debug >= level)
    {
        va_list args;
        FILE *fp = db_getfileptr();
        fflush(stdout);
        flockfile(fp);
        fputs(db_indent(), fp);
        if (options & DB_OPT_PID)
            fprintf(fp, "%d:", (int)getpid());
        fprintf(fp, "%s:%d:%s(): ", file, line, func);
        va_start(args, fmt);
        vfprintf(fp, fmt, args);
        va_end(args);
        fflush(fp);
        funlockfile(fp);
    }
}

/*
** Return indent string
*/
const char *db_indent(void)
{
    return(indent);
}

/*
**  Set indent level absolutely.
**  Returns old indent level.
*/
int db_setindent(int i)
{
    int             olevel = inlevel;

    if (i <= 0)
        inlevel = 0;
    else if (i > MAXINDENT)
        inlevel = MAXINDENT;
    else
        inlevel = i;
    indent = blanks + sizeof(blanks) - 3 * i - 1;
    return(olevel);
}

/*
**  Reduce indent level by one
**  Returns old indent level.
*/
int db_oldindent(void)
{
    return(db_setindent(inlevel - 1));
}

/*
**  Increase indent level by one
**  Returns old indent level.
*/
int db_newindent(void)
{
    return(db_setindent(inlevel + 1));
}

/*
**  Returns current debug level.
*/
int db_getdebug(void)
{
    return(debug);
}

/*
**  Set new debug level.
**  Returns old debug level.
*/
int db_setdebug(int level)
{
    int             o;

    assert(level >= 0);
    o = debug;
    debug = level;
    return(o);
}

#if defined(TEST)

static void db_test(void)
{
    fprintf(stderr, "Should appear at indent = %d\n", db_newindent() + 1);
    TRACE((1, "This should have appeared at debug level %d; %d %f\n",
              1, 3, 3.141593));
    DB_TRACE(2, "This should have appeared at debug level %d; %d %f\n",
              2, 3, 3.141593);
    DB_TRACELOC(3, "This should have appeared at debug level %d; %d %f\n",
              3, 3, 3.141593);
    DB_TRACE(4, "This should have appeared at debug level %d; %d %f\n",
              4, 3, 3.141593);
    db_oldindent();
}

static void db_test1(int i)
{
    db_setdebug(i);
    fprintf(stderr, "Debug level is: %d\n", db_getdebug());
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
    DB_TRACKING();
    if (argc <= 1)
        printf("It is more fun if you add arguments to the command line!\n");
    test_debug(argc, argv);
    return(0);
}

#endif /* TEST */
