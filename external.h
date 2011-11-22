/*
** This header must not contain header guards (like <assert.h> must not.
** Each time it is invoked, it redefines the three macros EXTERN,
** INIT_SIMPLE, INIT_COMPLEX based on whether macro DEFINE_VARIABLES is
** currently defined.
*/
#undef EXTERN
#undef INIT_SIMPLE
#undef INIT_COMPLEX

#ifdef DEFINE_VARIABLES
#define EXTERN                  extern
#define INIT_SIMPLE(x)          /* nothing */
#define INIT_COMPLEX(x, ...)    /* nothing */
#else
#define EXTERN                  /* nothing */
#define INIT_SIMPLE(x)          = x
#define INIT_COMPLEX(x, ...)    = x, __VA_ARGS__
#endif /* DEFINE_VARIABLES */
