
/* Standard prologue */
#if defined(DEFINE_VARIABLES) && !defined(FILE2C_H_DEFINITIONS)
#undef FILE2C_H_INCLUDED
#endif

#ifndef FILE2C_H_INCLUDED
#define FILE2C_H_INCLUDED

#include "external.h"   /* Support macros EXTERN, INITIALIZE */
#include "file1c.h"     /* Type definition for struct oddball */

#if !defined(DEFINE_VARIABLES) || !defined(FILE2C_H_DEFINITIONS)

/* Global variable declarations / definitions */
EXTERN int global_variable INITIALIZE(37);
EXTERN struct oddball oddball_struct INITIALIZE({ 41, 43 });

#endif /* !DEFINE_VARIABLES || !FILE2C_H_DEFINITIONS */

/* Standard epilogue */
#ifdef DEFINE_VARIABLES
#define FILE2C_H_DEFINITIONS
#endif /* DEFINE_VARIABLES */

#endif /* FILE2C_H_INCLUDED */
