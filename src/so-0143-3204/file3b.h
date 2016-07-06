#ifdef DEFINE_VARIABLES
#define EXTERN                  /* nothing */
#define INITIALIZER(...)        = __VA_ARGS__
#else
#define EXTERN                  extern
#define INITIALIZER(...)        /* nothing */
#endif /* DEFINE_VARIABLES */

EXTERN int global_variable INITIALIZER(37);
EXTERN struct { int a; int b; } oddball_struct INITIALIZER({ 41, 43 });
