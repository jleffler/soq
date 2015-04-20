/*
@(#)File:           $RCSfile$
@(#)Version:        $Revision$
@(#)Last changed:   $Date$
@(#)Purpose:        Prompt for an integer value
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2015
@(#)Product:        :PRODUCT:
*/

/*TABSTOP=4*/

#ifndef JLSS_ID_PROMPT_H
#define JLSS_ID_PROMPT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MAIN_PROGRAM
#ifndef lint
/* Prevent over-aggressive optimizers from eliminating ID string */
extern const char jlss_id_prompt_h[];
const char jlss_id_prompt_h[] = "@(#)$Id$";
#endif /* lint */
#endif /* MAIN_PROGRAM */

#include <stdarg.h>
#include <stdio.h>

extern int vfprompt_for_int(FILE *in, FILE *out, int *retval, int minval, int maxval,
                            int maxtries, const char *prompt, va_list args);
extern int fprompt_for_int(FILE *in, FILE *out, int *retval, int minval, int maxval,
                           const char *prompt, ...);
extern int prompt_for_int(int *retval, int minval, int maxval,
                          const char *prompt, ...);

#ifdef __cplusplus
}
#endif

#endif /* JLSS_ID_PROMPT_H */
