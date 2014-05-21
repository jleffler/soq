/*
** This header must not contain header guards (like <assert.h> must not).
** Each time it is included, the macro HEADER_DEFINING_VARIABLES should
** be defined with the name (in quotes - or possibly angle brackets) of
** the header to be included that defines variables when the macro
** DEFINE_VARIABLES is defined.  See also: external.h (which uses
** DEFINE_VARIABLES and defines macros EXTERN and INITIALIZE
** appropriately).
**
** #define HEADER_DEFINING_VARIABLES "file2c.h"
** #include "externdef.h"
*/

#if defined(HEADER_DEFINING_VARIABLES)
#define DEFINE_VARIABLES
#include HEADER_DEFINING_VARIABLES
#undef DEFINE_VARIABLES
#undef HEADER_DEFINING_VARIABLES
#endif /* HEADER_DEFINING_VARIABLES */

