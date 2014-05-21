/* Standard prologue */
#if defined(DEFINE_VARIABLES) && !defined(FILE8C_H_DEFINITIONS)
#undef FILE8C_H_INCLUDED
#endif

#ifndef FILE8C_H_INCLUDED
#define FILE8C_H_INCLUDED

#include "external.h"   /* Support macros EXTERN, INITIALIZE */
#include "file2c.h"     /* struct oddball */

#if !defined(DEFINE_VARIABLES) || !defined(FILE8C_H_DEFINITIONS)

/* Global variable declarations / definitions */
EXTERN struct oddball another INITIALIZE({ 14, 34 });

#endif /* !DEFINE_VARIABLES || !FILE8C_H_DEFINITIONS */

/* Standard epilogue */
#ifdef DEFINE_VARIABLES
#define FILE8C_H_DEFINITIONS
#endif /* DEFINE_VARIABLES */

#endif /* FILE8C_H_INCLUDED */

