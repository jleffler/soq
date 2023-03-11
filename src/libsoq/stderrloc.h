/*
@(#)File:           stderrloc.h
@(#)Purpose:        Standard Error Logging Functions with Locations
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2016
@(#)Derivation:     stderrloc.h 1.1 2016/01/10 18:19:53
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_STDERRLOC_H
#define JLSS_ID_STDERRLOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "noreturn.h"

extern NORETURN void err_pos_error(const char *file, int line, const char *func, const char *fmt, ...);
extern NORETURN void err_pos_syserr(const char *file, int line, const char *func, const char *fmt, ...);
extern void err_pos_remark(const char *file, int line, const char *func, const char *fmt, ...);
extern void err_pos_sysrem(const char *file, int line, const char *func, const char *fmt, ...);

extern void err_pos_vremark(const char *file, int line, const char *func, const char *fmt, va_list args);
extern void err_pos_vsysrem(const char *file, int line, const char *func, const char *fmt, va_list args);
extern NORETURN void err_pos_vsyserr(const char *file, int line, const char *func, const char *fmt, va_list args);
extern NORETURN void err_pos_verror(const char *file, int line, const char *func, const char *fmt, va_list args);

#define err_loc_remark(fmt, ...) err_pos_remark(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
#define err_loc_sysrem(fmt, ...) err_pos_sysrem(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
#define err_loc_error(fmt, ...)  err_pos_error(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)
#define err_loc_syserr(fmt, ...) err_pos_syserr(__FILE__, __LINE__, __func__, fmt, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_STDERRLOC_H */
