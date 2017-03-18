/*
@(#)File:           stderr.h
@(#)Purpose:        Header file for standard error functions
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1989-93,1996-99,2003,2005-11,2015-16
@(#)Derivation:     stderr.h 10.10 2015/10/14 23:12:19
*/

#if !defined(STDERR_H)
#define STDERR_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdarg.h>

/* Beware changing the NORETURN and PRINTFLIKE stanzas */
#if !defined(NORETURN)
#if __STDC_VERSION__ >= 201112L
#define NORETURN      _Noreturn
#elif defined(__GNUC__)
#define NORETURN      __attribute__((noreturn))
#else
#define NORETURN      /* If only */
#endif /* __STDC_VERSION__ || __GNUC__ */
#endif /* NORETURN */

#if !defined(PRINTFLIKE)
#if defined(__GNUC__)
#define PRINTFLIKE(n,m) __attribute__((format(printf,n,m)))
#else
#define PRINTFLIKE(n,m) /* If only */
#endif /* __GNUC__ */
#endif /* PRINTFLIKE */

/* -- Definitions for error handling */

enum { ERR_STAT    = 1 };           /* Default exit status     */

enum { ERR_DEFAULT = 0x0000 };      /* Default flag                      */
enum { ERR_NOFLUSH = 0x0001 };      /* Do not flush open files           */
enum { ERR_EXIT    = 0x0004 };      /* Exit  -- do not return            */
enum { ERR_ABORT   = 0x0008 };      /* Abort -- do not return            */
enum { ERR_STAMP   = 0x0020 };      /* Timestamp messages (whole second) */
enum { ERR_NOARG0  = 0x0040 };      /* Do not print arg0 prefix          */
enum { ERR_PID     = 0x0080 };      /* Include pid=nnnnn info            */
enum { ERR_ERRNO   = 0x0100 };      /* Include system error              */
enum { ERR_MILLI   = 0x0200 };      /* Timestamp messages (millisecond)  */
enum { ERR_MICRO   = 0x0400 };      /* Timestamp messages (microsecond)  */
enum { ERR_NANO    = 0x0800 };      /* Timestamp messages (nanosecond)   */

/* -- Standard combinations of flags */

enum { ERR_REM    = ERR_DEFAULT       };
enum { ERR_ERR    = ERR_EXIT          };
enum { ERR_ABT    = ERR_ABORT         };
enum { ERR_LOG    = ERR_STAMP|ERR_PID };
enum { ERR_SYSREM = ERR_REM|ERR_ERRNO };
enum { ERR_SYSERR = ERR_ERR|ERR_ERRNO };

/* -- Maximum recorded length of argv[0]; extra is truncated */

enum { ERR_MAXLEN_ARGV0 = 63 };

/* -- Global definitions */

extern const char *err_getarg0(void);
extern void        err_setarg0(const char *argv0);

extern FILE       *err_stderr(FILE *fp);
extern const char *err_rcs_string(const char *s, char *buffer, size_t buflen);

extern NORETURN void err_abort(const char *format, ...) PRINTFLIKE(1,2);
extern NORETURN void err_error(const char *format, ...) PRINTFLIKE(1,2);
extern NORETURN void err_help(const char *use_str, const char *hlp_str);
extern NORETURN void err_helplist(const char *use_str, const char * const *help_list);
extern NORETURN void err_internal(const char *function, const char *format, ...) PRINTFLIKE(2,3);
extern NORETURN void err_syserr(const char *format, ...) PRINTFLIKE(1,2);
extern NORETURN void err_syserror(int errnum, const char *format, ...) PRINTFLIKE(2,3);
extern NORETURN void err_usage(const char *usestr);
extern NORETURN void err_version(const char *program, const char *verinfo);

extern void err_logmsg(FILE *fp, int flags, int estat, const char *format, ...) PRINTFLIKE(4,5);
extern void err_print(int flags, int estat, const char *format, va_list args);
extern void err_printversion(const char *program, const char *verinfo);
extern void err_remark(const char *format, ...) PRINTFLIKE(1,2);
extern void err_report(int flags, int estat, const char *format, ...) PRINTFLIKE(3,4);
extern void err_sysrem(const char *format, ...) PRINTFLIKE(1,2);
extern void err_sysremark(int errnum, const char *format, ...) PRINTFLIKE(2,3);

extern int  err_getlogopts(void);           /* Get default log options */
extern int  err_setlogopts(int new_opts);   /* Set default log options */

/* Time format of NULL sets default format - returns previous format */
extern const char *err_settimeformat(const char *new_fmt);
extern const char *err_gettimeformat(void);

#endif /* STDERR_H */
