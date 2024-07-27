/*
@(#)File:           stderr.c
@(#)Purpose:        Error reporting routines
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1988-2024
@(#)Derivation:     stderr.c 10.32 2024/03/24 20:49:47
*/

/*TABSTOP=4*/

/*
** Configuration:
** USE_STDERR_SYSLOG    - Include syslog functionality
** USE_STDERR_FILEDESC  - Include file descriptor functionality
** JLSS_STDERR          - Force support for syslog and file descriptors
**
** NO_UNISTD_H          - Define if <unistd.h> is missing (assumed present).
**                      - Not part of autoconf-generated config.h; that defines
**                        HAVE_UNISTD_H, but using NO_UNISTD_H means the code
**                        normally compiles using <unistd.h> even without
**                        config.h (HAVE_CONFIG_H).
**
** HAVE_CLOCK_GETTIME   - Define if clock_gettime() is available (nanoseconds)
** HAVE_GETTIMEOFDAY    - Define if gettimeofday() is available (microseconds)
** HAVE_SYSLOG_H        - Define if <syslog.h> is available
** HAVE_SYSLOG          - Define if syslog() is available
*/

/* #define __EXTENSIONS__  // Solaris 11.3 - declare flockfile(), funlockfile() */

#include "posixver.h"
#include "stderr.h"     /* Includes config.h if available */
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#ifndef NO_UNISTD_H
#include <unistd.h>
#else
extern int getpid(void);
#endif /* NO_UNISTD_H */

/* Some help messages can be very long */
#ifndef ERR_MAXMSGLEN
#define ERR_MAXMSGLEN 8192
#endif
enum { MAX_MSGLEN = ERR_MAXMSGLEN };

/* Find sub-second timing mechanism */
#if defined(HAVE_CLOCK_GETTIME)
/* Uses <time.h> */
#elif defined(HAVE_GETTIMEOFDAY)
/*
** Mac OS X up to and including version 10.11 El Capitan does not have
** clock_gettime(); macOS Sierra 10.12 and up does have clock_gettime().
*/
#include <sys/time.h>
#else
/* No sub-second timing */
#endif

#if defined(HAVE_SYSLOG_H) && defined(HAVE_SYSLOG) && defined(USE_STDERR_SYSLOG)
#include <syslog.h>
extern const char jlss_id_stderr_c_with_syslog[];
const char jlss_id_stderr_c_with_syslog[] =
        "@(#)" __FILE__ " configured with USE_STDERR_SYSLOG";
#else
#undef USE_STDERR_SYSLOG
#undef HAVE_SYSLOG_H
#undef HAVE_SYSLOG
#endif /* syslog configuration */

#if defined(USE_STDERR_FILEDESC)
extern const char jlss_id_stderr_c_with_filedesc[];
const char jlss_id_stderr_c_with_filedesc[] =
        "@(#)" __FILE__ " configured with USE_STDERR_FILEDESC";
#endif /* USE_STDERR_FILEDESC */

enum { FSLASH = '/', BSLASH = '\\' };

static const char def_format[] = "%Y-%m-%d %H:%M:%S";
static const char *tm_format = def_format;
static char arg0[ERR_MAXLEN_ARGV0+1] = "**undefined**";

/* Permitted default error flags */
enum { ERR_LOGTIME = ERR_STAMP | ERR_MILLI | ERR_MICRO | ERR_NANO };
enum { ERR_LOGOPTS = ERR_NOFLUSH | ERR_EXIT | ERR_ABORT | ERR_LOGTIME |
                     ERR_NOARG0  | ERR_PID  | ERR_ERRNO };
static int   err_flags = 0;     /* Default error flags (ERR_STAMP, ERR_PID, etc) */

/* Where do messages go?
**  if   (defined USE_STDERR_SYSLOG && use_syslog != 0) ==> syslog
**  elif (defined USE_STDERR_FILEDESC && err_fd >= 0)   ==> file descriptor
**  else                                                ==> file pointer
*/
#ifdef USE_STDERR_SYSLOG
static int   use_syslog =  0;
#endif /* USE_STDERR_SYSLOG */
static FILE *errout =  0;
#ifdef USE_STDERR_FILEDESC
static int   err_fd = -1;
#endif /* USE_STDERR_FILEDESC */

/*
** err_???_print() functions are named systematically, and are all static.
**
** err_[ev][crx][fn]_print():
** --   e   takes ellipsis argument
** --   v   takes va_list argument
** --   c   conditionally exits
** --   r   returns (no exit)
** --   x   exits (no return)
** --   f   takes file pointer
** --   n   no file pointer (use errout)
*/

static NORETURN void err_vxf_print(FILE *fp, int flags, int errnum, int estat,
                                   const char *format, va_list args);
static NORETURN void err_vxn_print(int flags, int errnum, int estat,
                                   const char *format, va_list args);
static NORETURN void err_exn_print(int flags, int estat, const char *format, ...)
                PRINTFLIKE(3, 4);
static NORETURN void err_terminate(int flags, int estat);

/*
** Set default log options, returning old value.
** Setting ERR_EXIT and ERR_ABORT is permitted but not recommended.
*/
int err_setlogopts(int new_opts)
{
    int old_opts = err_flags;
    err_flags = new_opts & ERR_LOGOPTS;
    return(old_opts);
}

/* Return default log options */
int err_getlogopts(void)
{
    return(err_flags);
}

/* Set time format - NULL implies default format */
const char *err_settimeformat(const char *new_fmt)
{
    const char *old_fmt = tm_format;
    if (new_fmt == NULL)
        tm_format = def_format;
    else
        tm_format = new_fmt;
    return old_fmt;
}

/* Set time format - NULL implies default format */
const char *err_gettimeformat(void)
{
    return tm_format;
}

/* Change the definition of 'stderr', reporting on the old one too */
/* NB: using err_stderr((FILE *)0) simply reports the current 'stderr' */
FILE *(err_stderr)(FILE *newerr)
{
    FILE *old;

    if (errout == 0)
        errout = stderr;
    old = errout;
    if (newerr != 0)
        errout = newerr;
    return(old);
}

#if defined(USE_STDERR_FILEDESC)
/* Change the definition of 'stderr', reporting on the old one too */
/* NB: using err_use_fd() with a negative value turns off 'errors to file descriptor' */
int (err_use_fd)(int new_fd)
{
    int old_fd = err_fd;

    if (new_fd < 0)
        new_fd = -1;
    err_fd = new_fd;
    return(old_fd);
}
#endif /* USE_STDERR_FILEDESC */

#if defined(USE_STDERR_SYSLOG)
/*
** Configure the use of syslog
** If configured to use syslog(), the facility argument should be one of
** the standard facilities (POSIX defines LOG_USER and LOG_LOCAL0 to
** LOG_LOCAL7) to turn on syslog(), or a negative value to turn it off.
** The logopts should be the bitwise combination of 0 and the options
** LOG_PID, LOG_CONS, LOG_NDELAY, LOG_ODELAY, LOG_NOWAIT.  However, the
** STDERR package sets LOG_PID regardless.
** The ident used in openlog() corresponds to the value in arg0.
** Note that when formatting the message for syslog(), the time, the PID
** and arg0 are not needed (and hence not provided).  The downside is
** you are stuck with the date formatted by syslog().
*/
int (err_use_syslog)(int logopts, int facility)
{
    if (facility < 0)
    {
        /* Turn off syslog() */
        closelog();
        use_syslog = 0;
    }
    else
    {
        openlog(arg0, LOG_PID|logopts, facility);
        use_syslog = 1;
    }
    return(use_syslog);
}
#endif /* USE_STDERR_SYSLOG */

/* Return stored basename of command */
const char *(err_getarg0)(void)
{
    return(arg0);
}

/* Store basename of command, excluding trailing slashes */
void (err_setarg0)(const char *argv0)
{
    /* Ignore three pathological program names -- NULL, "/" and "" */
    if (argv0 != 0 && *argv0 != '\0' && (argv0[0] != FSLASH || argv0[1] != '\0'))
    {
        const char *cp;
        size_t nbytes;

        if ((cp = strrchr(argv0, FSLASH)) == 0 &&
            (cp = strrchr(argv0, BSLASH)) == 0)
        {
            /* Basename of file only */
            cp = argv0;
            nbytes = strlen(cp);
        }
        else if (*(cp + 1) != '\0')
        {
            /* Regular pathname containing slashes but not trailing slashes */
            cp++;
            nbytes = strlen(cp);
        }
        else
        {
            /* Skip backwards over trailing slashes */
            const char *ep = cp;
            while (ep > argv0 && (*ep == FSLASH || *ep == BSLASH))
                ep--;
            /* Skip backwards over non-slashes */
            cp = ep;
            while (cp > argv0 && (*cp != FSLASH && *cp != BSLASH))
                cp--;
            assert(ep >= cp);
            if (cp > argv0)
                cp++;
            nbytes = (size_t)(ep - cp) + 1;
        }
        if (nbytes > sizeof(arg0) - 1)
            nbytes = sizeof(arg0) - 1;
        /*
        ** Use memmove() to allow for usage: daemonize(err_getarg(), 0);
        ** where daemonize() calls err_setarg0() with its first argument.
        */
        memmove(arg0, cp, nbytes);
        arg0[nbytes] = '\0';
    }
}

const char *(err_rcs_string)(const char *s2, char *buffer, size_t buflen)
{
    const char *src = s2;
    char *dst = buffer;
    char *end = buffer + buflen - 1;

    /*
    ** Bother RCS!  We've probably been given something like:
    ** "$Revision: 10.32 $ ($Date: 2024/03/24 20:49:47 $)"
    ** We only want to emit "7.5 (2001/08/11 06:25:48)".
    ** Skip the components between '$' and ': ', copy up to ' $',
    ** repeating as necessary.  And we have to test for overflow!
    ** Also work with the unexpanded forms of keywords ($Keyword$).
    ** Never needed this with SCCS!
    */
    while (*src != '\0' && dst < end)
    {
        while (*src != '\0' && *src != '$')
        {
            *dst++ = *src++;
            if (dst >= end)
                break;
        }
        if (*src == '$')
            src++;
        while (*src != '\0' && *src != ':' && *src != '$')
            src++;
        if (*src == '\0')
            break;
        if (*src == '$')
        {
            /* Unexpanded keyword '$Keyword$' notation */
            src++;
            continue;
        }
        if (*src == ':')
            src++;
        if (*src == ' ')
            src++;
        while (*src != '\0' && *src != '$')
        {
            /* Map / in 2009/02/15 to dash */
            /* Heuristic - maps slashes surrounded by digits to dashes */
            char c = *src++;
            if (c == '/' && isdigit(*src) && isdigit(*(src-2)))
                c = '-';
            *dst++ = c;
            if (dst >= end)
                break;
        }
        if (*src == '$')
        {
            if (*(dst-1) == ' ')
                dst--;
            src++;
        }
    }
    *dst = '\0';
    return(buffer);
}

/* Similar to, but different from, Time in timer.h */
typedef struct Time
{
    time_t tv_sec;
    long   tv_nsec;
} Time;

static Time now(void)
{
    Time clk;
#if defined(HAVE_CLOCK_GETTIME)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    clk.tv_sec = ts.tv_sec;
    clk.tv_nsec = ts.tv_nsec;
#elif defined(HAVE_GETTIMEOFDAY)
    struct timeval tv;
    gettimeofday(&tv, 0);
    clk.tv_sec = tv.tv_sec;
    clk.tv_nsec = 1000 * tv.tv_usec;
#else
    clk.tv_sec = time(0);
    clk.tv_nsec = 0;
#endif
    return clk;
}

/* Format a time string for now (using ISO8601 format by default) */
/* The time format can be set via err_settimeformat() */
static char *err_time(int flags, char *buffer, size_t buflen)
{
    Time clk = now();
    struct tm *tp = localtime(&clk.tv_sec);
    size_t nb = strftime(buffer, buflen, tm_format, tp);
    if (flags & (ERR_NANO | ERR_MICRO | ERR_MILLI))
    {
        char subsec[12];
        int ss_len;
        if (flags & ERR_NANO)
            ss_len = snprintf(subsec, sizeof(subsec), ".%.9ld", clk.tv_nsec);
        else if (flags & ERR_MICRO)
            ss_len = snprintf(subsec, sizeof(subsec), ".%.6ld", clk.tv_nsec / 1000);
        else /* (flags & ERR_MILLI) */
            ss_len = snprintf(subsec, sizeof(subsec), ".%.3ld", clk.tv_nsec / (1000 * 1000));
        if (ss_len > 0 && (size_t)ss_len + nb + 1 < buflen)
            strcpy(buffer + nb, subsec);
    }
    return(buffer);
}

/* Format string - va_list */
static char *vfmt_string(char *curr, const char *end, const char *format, va_list args)
{
    char *new_end = curr;
    if (curr < end - 1)
    {
        size_t size = (size_t)(end - curr);
        int more = vsnprintf(curr, size, format, args);
        if (more >= 0)
            new_end += ((size_t)more >= size) ? size : (size_t)more;
    }
    return(new_end);
}

/* Format string - ellipsis */
static char *efmt_string(char *curr, const char *end, const char *format, ...)
{
    va_list args;
    char *new_end;
    va_start(args, format);
    new_end = vfmt_string(curr, end, format, args);
    va_end(args);
    return new_end;
}

static size_t err_fmtmsg(char *buffer, size_t buflen, int flags, int errnum,
                         const char *format, va_list args)
{
    char *curpos = buffer;
    char *bufend = buffer + buflen;

    buffer[0] = '\0';   /* Not strictly necessary */
    if ((flags & ERR_NOARG0) == 0)
        curpos = efmt_string(curpos, bufend, "%s: ", arg0);
    if (flags & ERR_LOGTIME)
    {
        char timbuf[32];
        curpos = efmt_string(curpos, bufend,
                             "%s - ", err_time(flags, timbuf, sizeof(timbuf)));
    }
    if (flags & ERR_PID)
        curpos = efmt_string(curpos, bufend,
                             "pid=%d: ", (int)getpid());
    curpos = vfmt_string(curpos, bufend, format, args);
    if (flags & ERR_ERRNO)
        curpos = efmt_string(curpos, bufend,
                             "error (%d) %s\n", errnum, strerror(errnum));
    assert(curpos >= buffer);
    return((size_t)(curpos - buffer));
}

/*
** err_stdio - report error via stdio
** Using fflush(fp) ensures that the message is flushed even if the
** stream is fully buffered.
** No longer need explicit flockfile() and funlockfile() because there's
** only a single call to fwrite() and that must lock the stream anyway.
*/
static void (err_stdio)(FILE *fp, int flags, int errnum, const char *format, va_list args)
{
    char buffer[MAX_MSGLEN];
    size_t msglen = err_fmtmsg(buffer, sizeof(buffer), flags, errnum, format, args);
    fwrite(buffer, sizeof(char), msglen, fp);
    fflush(fp);
}

#if defined(USE_STDERR_SYSLOG)
/* err_syslog() - report error via syslog
**
** syslog() automatically adds PID and program name (configured in
** openlog()) and time stamp.  Hence those elements are removed from
** flags sent to err_fmtmsg.
*/
static void (err_syslog)(int flags, int errnum, const char *format, va_list args)
{
    char buffer[MAX_MSGLEN];
    int priority;

    err_fmtmsg(buffer, sizeof(buffer), flags & ~(ERR_NOARG0|ERR_PID|ERR_LOGTIME),
               errnum, format, args);

    if (flags & ERR_ABORT)
        priority = LOG_CRIT;
    else if (flags & ERR_EXIT)
        priority = LOG_ERR;
    else
        priority = LOG_WARNING;
    syslog(priority, "%s", buffer);
}
#endif /* USE_STDERR_SYSLOG */

#if defined(USE_STDERR_FILEDESC)
/* err_filedes() - report error via file descriptor */
static void (err_filedes)(int fd, int flags, int errnum, const char *format, va_list args)
{
    char buffer[MAX_MSGLEN];
    size_t msglen = err_fmtmsg(buffer, sizeof(buffer), flags, errnum, format, args);
    ssize_t nbytes;
    char *msgbuf = buffer;

    while (msglen > 0)
    {
        nbytes = write(fd, msgbuf, msglen);
        if (nbytes <= 0)
            break;
        msgbuf += nbytes;
        assert(nbytes > 0 && msglen >= (size_t)nbytes);
        msglen -= (size_t)nbytes;
    }
}
#endif /* USE_STDERR_FILEDESC */

/* Most fundamental (and flexible) error message printing routine - always returns */
static void (err_vrf_print)(FILE *fp, int flags, int errnum, const char *format, va_list args)
{
    if ((flags & ERR_NOFLUSH) == 0)
        fflush(0);

#if defined(USE_STDERR_SYSLOG)
    if (use_syslog)
    {
        err_syslog(flags, errnum, format, args);
        return;
    }
#endif /* USE_STDERR_SYSLOG */
#if defined(USE_STDERR_FILEDESC)
    if (err_fd >= 0)
    {
        err_filedes(err_fd, flags, errnum, format, args);
        return;
    }
#endif /* USE_STDERR_FILEDESC */
    err_stdio(fp, flags, errnum, format, args);
}

/* Terminate program - abort or exit */
static NORETURN void err_terminate(int flags, int estat)
{
    assert(flags & (ERR_ABORT|ERR_EXIT));
    if (flags & ERR_ABORT)
        abort();
    exit(estat);
}

/* Most fundamental (and flexible) error message printing routine - may return */
void (err_vlogmsg)(FILE *fp, int flags, int estat, const char *format, va_list args)
{
    err_vrf_print(fp, flags, errno, format, args);
    if (flags & (ERR_ABORT|ERR_EXIT))
        err_terminate(flags, estat);
}

/* Analog of err_vlogmsg() which guarantees 'no return' */
static NORETURN void (err_vxf_print)(FILE *fp, int flags, int errnum, int estat,
                            const char *format, va_list args)
{
    err_vrf_print(fp, flags, errnum, format, args);
    err_terminate(flags, estat);
}

/* Alternative external interface to err_vlogmsg() - may return */
void (err_logmsg)(FILE *fp, int flags, int estat, const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vlogmsg(fp, flags, estat, format, args);
    va_end(args);
}

/* Print error message to current error output - no return */
static NORETURN void (err_vxn_print)(int flags, int errnum, int estat,
                                     const char *format, va_list args)
{
    if (errout == 0)
        errout = stderr;
    err_vxf_print(errout, flags, errnum, estat, format, args);
}

/* Print error message to current error output - no return */
static NORETURN void err_exn_print(int flags, int estat, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    err_vxn_print(flags, errno, estat, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Print error message to nominated output - returns unless flags say exit */
static void err_erf_print(FILE *fp, int flags, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    err_vrf_print(fp, flags, errno, format, args);
    va_end(args);
}

/* Print message using current error file - may return */
void (err_print)(int flags, int estat, const char *format, va_list args)
{
    if (errout == 0)
        errout = stderr;
    err_vlogmsg(errout, flags, estat, format, args);
}

static void err_vrn_print(int flags, int errnum, const char *format, va_list args)
{
    if (errout == 0)
        errout = stderr;
    err_vrf_print(errout, flags, errnum, format, args);
}

/* Report warning including message from errno */
void (err_sysrem)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_SYSREM | err_getlogopts(), errno, format, args);
    va_end(args);
}

/* Report warning including message from errno */
void (err_sysremark)(int errnum, const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_SYSREM | err_getlogopts(), errnum, format, args);
    va_end(args);
}

/* err_syswarn() and err_syswarning() are preferred duplicates of err_sysrem() and err_sysremark() */
/* Report warning including message from errno */
void (err_syswarn)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_SYSREM | err_getlogopts(), errno, format, args);
    va_end(args);
}

/* Report warning including message from errno */
void (err_syswarning)(int errnum, const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_SYSREM | err_getlogopts(), errnum, format, args);
    va_end(args);
}

/* Report error including message from errno */
void (err_syserr)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vxn_print(ERR_SYSERR | err_getlogopts(), errno, ERR_STAT, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Report error including message from errno */
void (err_syserror)(int errnum, const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vxn_print(ERR_SYSERR | err_getlogopts(), errnum, ERR_STAT, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Report warning - identical to err_warning() */
void (err_remark)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_REM | err_getlogopts(), errno, format, args);
    va_end(args);
}

/* Report warning - identical to err_remark() */
void (err_warning)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vrn_print(ERR_REM | err_getlogopts(), errno, format, args);
    va_end(args);
}

/* Report warning */
void (err_vwarning)(const char *format, va_list args)
{
    err_vrn_print(ERR_REM | err_getlogopts(), errno, format, args);
}

/* Report error */
NORETURN void err_verror(const char *format, va_list args)
{
    err_vxn_print(ERR_ERR | err_getlogopts(), errno, ERR_STAT, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Report error */
NORETURN void (err_error)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vxn_print(ERR_ERR | err_getlogopts(), errno, ERR_STAT, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Report message - sometimes exiting too */
void (err_report)(int flags, int estat, const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_print(flags, estat, format, args);
    va_end(args);
}

/* Format one continuation line of a usage message */
static int fmt_usage_line(size_t buflen, char *buffer, int length, const char *line)
{
    int arg0_len = (int)strlen(arg0);
    const char *name = "";
    if (line[0] == '@')
    {
        name = arg0;
        int whisp = strspn(&line[1], " \t");
        line += whisp + 1;
        length -= whisp + 1;
    }
    int out_len = snprintf(buffer, buflen, "%-*s%*s %.*s\n",
                           (int)sizeof("Usage:"), "",
                           arg0_len, name,
                           length, line);
    assert(out_len > 0 && (size_t)out_len < buflen);
    return out_len;
}

/* Format possibly multi-line usage message */
/*
** Given usestr containing "abc\ndef", the output from a command "cmd" would be:
** Usage: cmd abc
**            def
** Given usestr containing "abc\n@def \\\nghi\n@jkl", the output would be:
** Usage: cmd abc
**        cmd def \
**            ghi
**        cmd jkl
** White space (blanks, tabs) after the `@` is skipped.
** White space after the (first) newline suppresses the special formatting;
** the remaining information is printed verbatim.
** In 'real life', the "abc" parts would normally be a lot longer, of course.
*/

void err_fmt_usage(size_t buflen, char *buffer, const char *usestr)
{
    const char *newline = strchr(usestr, '\n');
    if (newline != 0 && newline[1] != ' ' && newline[1] != '\0')
    {
        char *bufptr = buffer;
        int out_len = snprintf(bufptr, buflen, "Usage: %s %.*s\n", arg0, (int)(newline - usestr), usestr);
        assert(out_len > 0 && (size_t)out_len < buflen);
        bufptr += out_len;
        buflen -= (size_t)out_len;

        int eol;
        newline++;
        while ((eol = strcspn(newline, "\n")) != 0)
        {
            out_len = fmt_usage_line(buflen, bufptr, eol, newline);
            assert(out_len > 0 && (size_t)out_len < buflen);
            bufptr += out_len;
            buflen -= (size_t)out_len;
            if (newline[eol] == '\0')
                break;
            newline += eol + 1;
        }
    }
    else
        snprintf(buffer, buflen, "Usage: %s %s", arg0, usestr);

    size_t result_len = strlen(buffer);
    if (result_len > 0 && buffer[result_len - 1] == '\n')
        buffer[result_len - 1] = '\0';
}

/* Print usage message and exit with failure status */
NORETURN void (err_usage)(const char *usestr)
{
    char buffer[MAX_MSGLEN];    /* Fairly big chunk of stack! */
    err_fmt_usage(sizeof(buffer), buffer, usestr);
    err_exn_print(ERR_NOARG0|ERR_EXIT, EXIT_FAILURE, "%s\n", buffer);
}

/* Report failure and generate core dump */
NORETURN void (err_abort)(const char *format, ...)
{
    va_list         args;

    va_start(args, format);
    err_vxn_print(ERR_ABORT | err_getlogopts(), errno, EXIT_FAILURE, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

/* Report version information (no exit), removing embedded RCS keyword strings (but not values) */
void (err_printversion)(const char *program, const char *verinfo)
{
    char buffer[64];

    if (strchr(verinfo, '$'))
        verinfo = err_rcs_string(verinfo, buffer, sizeof(buffer));
    err_erf_print(stdout, ERR_DEFAULT, "%s Version %s\n", program, verinfo);
}

/* Report version information and exit, removing embedded RCS keyword strings (but not values) */
void (err_version)(const char *program, const char *verinfo)
{
    err_printversion(program, verinfo);
    exit(EXIT_SUCCESS);
}

/* Report an internal error and exit */
/* Abort if JLSS_INTERNAL_ERROR_ABORT set in environment */
NORETURN void (err_internal)(const char *function, const char *format, ...)
{
    va_list args;
    int flags = ERR_EXIT;
    int errnum = errno;     /* Capture errno before it gets changed */
    const char *ev = getenv("JLSS_INTERNAL_ERROR_ABORT");

    if (ev != 0 && *ev != '\0')
        flags = ERR_ABORT;  /* Generate core dump */

    va_start(args, format);
    err_remark("unrecoverable internal error in function %s():\n", function);
    err_vxn_print(flags | err_getlogopts(), errnum, EXIT_FAILURE, format, args);
    /* va_end(args);   // Superfluous - err_vxn_print() does not return */
}

#ifdef TEST
#include "test.stderr.c"
#endif /* TEST */
