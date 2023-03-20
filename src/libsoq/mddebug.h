/*
@(#)File:           mddebug.h
@(#)Purpose:        Support for Debugging Printing with Multiple Subsystems
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 1990-2023
@(#)Derivation:     mddebug.h 4.1 2023/03/13 17:14:56
*/

#ifndef MDDEBUG_H
#define MDDEBUG_H

#include <stdio.h>
#include "kludge.h"

/* Control whether debugging macros are active at compile time */
#undef DB_MD_ACTIVE
#ifdef DEBUG
#define DB_MD_ACTIVE 1
#else
#define DB_MD_ACTIVE 0
#endif /* DEBUG */

enum DB_MD_Options { DB_MD_OPT_PID = 0x01 };     // Record PID at start of message

/*
** Usage:  DB_MDTRACE(subsys, level, fmt, ...);
** Usage:  DB_MDTRACELOC(subsys, level, fmt, ...);
**
** "subsys" is the debugging system to which this statement belongs.
** The significance of the subsystems is determined by the programmer,
** except that the functions such as db_print refer to subsystem 0.
** "level" is the debugging level which must be operational for the
** output to appear. "fmt" is a printf format string. "..." is
** whatever extra arguments fmt requires (possibly nothing).
*/
#define DB_MDTRACE(subsys, level, ...) \
            do { if (DB_MD_ACTIVE) db_mdprint(subsys, level, __VA_ARGS__); } while (0)
#define DB_MDTRACELOC(subsys, level, ...) \
            do { if (DB_MD_ACTIVE) db_mdprintloc(subsys, level, __FILE__, __LINE__, \
                                              __func__, __VA_ARGS__); } while (0)

/*
** Usage:  DB_MDCALL(subsys, level, ...);
**
** Example: DB_MDCALL(subsys, 1, dump_structure(db_getfileptr(), "tag", arg1, arg2));
**
** If trace is active at given level for given subsystem, execute the
** code in the variable arguments.  Normally used to selectively execute
** printing functions.
*/
#define DB_MDCALL(subsys, level, ...) \
            do { if (DB_ACTIVE && db_mdgetdebug(subsys) >= (level)) { __VA_ARGS__; } } while (0)

/*
** DB_MDTRACKING(); uses the FEATURE_FILE macro from klduge.h to embed a
** string in a function identifying that the file is compiled with debug
** enabled.
*/
#define DB_MDTRACKING() \
            do { if (DB_ACTIVE) FEATURE_FILE("** DEBUGGING SUBSYSTEMS ENABLED **") } while (0)

extern int      db_mdgetdebug(int subsys);
extern int      db_mdparsearg(char *arg);
extern int      db_mdsetdebug(int subsys, int level);
extern int      db_mdsetoptions(int opts);
extern void     db_mdprint(int subsys, int level, const char *fmt, ...);
extern void     db_mdprintloc(int subsys, int level, const char *file,
                              int line, const char *func, const char *fmt, ...);
extern void     db_mdsubsysnames(char * const *names);

/* These functions are defined in debug.c and declared in debug.h */
/* They are use by both mddebug.c and debug.c */
#ifdef DEFINE_AUXILLIARY_DEBUG_FUNCTIONS
extern int         db_newindent(void);
extern int         db_oldindent(void);
extern int         db_setindent(int i);
extern void        db_setfilename(const char *fn);
extern void        db_setfileptr(FILE *fp);
extern FILE       *db_getfileptr(void);
extern const char *db_indent(void);
#endif /* DEFINE_AUXILLIARY_DEBUG_FUNCTIONS */

#endif /* MDDEBUG_H */
