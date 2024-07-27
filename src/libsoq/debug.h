/*
@(#)File:           debug.h
@(#)Purpose:        Support for Debugging Printing
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2024
@(#)Derivation:     debug.h 4.2 2024/05/21 04:48:42
*/

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include "kludge.h"

/* Control whether debugging macros are active at compile time */
#undef DB_ACTIVE
#ifdef DEBUG
#define DB_ACTIVE 1
#else
#define DB_ACTIVE 0
#endif /* DEBUG */

/*
** Usage:  DB_TRACE(level, fmt, ...);
** Usage:  DB_TRACELOC(level, fmt, ...);
**
** "level" is the debugging level which must be operational for the output
** to appear. "fmt" is a printf format string. "..." is whatever extra
** arguments fmt requires (possibly nothing).
**
** The structure of the macros means that the code is always validated
** but is not called when DEBUG is undefined.
** -- See chapter 8 of 'The Practice of Programming', by Kernighan and Pike.
*/
#define DB_TRACE(level, ...)\
            do { if (DB_ACTIVE) db_print(level, __VA_ARGS__); } while (0)
#define DB_TRACELOC(level, ...)\
            do { if (DB_ACTIVE) db_printloc(level, __FILE__, __LINE__, __func__, __VA_ARGS__); } while (0)

/*
** Usage:  DB_CALL(level, ...);
**
** Example: DB_CALL(1, dump_structure(db_getfileptr(), "tag", arg1));
**
** If trace is active at given level, execute the code in the variable
** arguments.  Normally used to selectively execute printing functions.
*/
#define DB_CALL(level, ...)\
            do { if (DB_ACTIVE && db_getdebug() >= (level)) { __VA_ARGS__; } } while (0)

/*
** Usage: DB_BEGIN(level);
**        ...conditional code...
**        DB_END();
** The semicolon after DB_BEGIN is optional, but harmless.
** If DB_BEGIN/DB_END are not properly matched, all hell will break loose.
*/

#define DB_BEGIN(level) do { if (DB_ACTIVE && db_getdebug() >= (level)) {
#define DB_END()        } } while (0)

/*
** DB_TRACKING(); uses the FEATURE_FILE macro from klduge.h to embed a
** string in a function identifying that the file is compiled with debug
** enabled.
*/
#define DB_TRACKING() \
            do { if (DB_ACTIVE) FEATURE_FILE("** DEBUGGING ENABLED **") } while (0)

enum DB_Options { DB_OPT_PID = 0x01 };     // Record PID at start of message

extern int      db_getdebug(void);
extern int      db_setdebug(int level);
extern int      db_setoptions(int opts);
extern void     db_print(int level, const char *fmt, ...);
extern void     db_printloc(int level, const char *file, int line,
                            const char *func, const char *fmt, ...);

/* These functions are declared in debug.h and defined in debug.c */
/* They are also used by mddebug.c */
extern void        db_setfilename(const char *fn);
extern void        db_setfileptr(FILE *fp);
extern FILE       *db_getfileptr(void);
extern int         db_newindent(void);
extern int         db_oldindent(void);
extern int         db_setindent(int i);
/* Semi-private function */
extern const char *db_indent(void);

#endif /* DEBUG_H */
