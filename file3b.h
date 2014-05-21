/* Standard prologue */
#if defined(DEFINE_VARIABLES) && !defined(FILE2C_H_DEFINITIONS)
#undef FILE2C_H_INCLUDED
#endif

#ifndef FILE2C_H_INCLUDED
#define FILE2C_H_INCLUDED

#include "external.h"   /* Support macros EXTERN, INITIALIZE */
#include "file1c.h"     /* Type definition for struct oddball */

/* Global variable declarations / definitions */
EXTERN int global_variable INITIALIZE(37);
EXTERN struct oddball oddball_struct INITIALIZE({ 41, 43 });

/* Standard epilogue */
#ifdef DEFINE_VARIABLES
#define FILE2C_H_DEFINITIONS
#undef DEFINE_VARIABLES     /* Safety first */
#endif /* DEFINE_VARIABLES */

#endif /* FILE2C_H_INCLUDED */
