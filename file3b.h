
/* Standard prologue */
#if defined(DEFINE_VARIABLES) && !defined(FILE2C_H_DEFINITIONS)
#undef FILE2C_H_INCLUDED
#endif

#ifndef FILE2C_H_INCLUDED
#define FILE2C_H_INCLUDED

#include "external.h"   /* Support macros EXTERN, INIT_SIMPLE, INIT_COMPLEX */
#include "file1c.h"     /* Type definition for struct oddball */

/* Global variable declarations / definitions */
EXTERN int global_variable INIT_SIMPLE(37);
EXTERN struct oddball oddball_struct INIT_COMPLEX({ 41, 43 });

/* Standard epilogue */
#ifdef DEFINE_VARIABLES
#define FILE2C_H_DEFINITIONS
#undef DEFINE_VARIABLES     /* Safety first */
#endif /* DEFINE_VARIABLES */

#endif /* FILE2C_H_INCLUDED */
