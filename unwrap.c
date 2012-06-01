#include <stdio.h>

/* "unwrapper": */
#define UNWRAP(...) __VA_ARGS__

struct a { int a1; double a2; };
struct b { struct a a; int b; };

/* your macros: */
#define WRAP(NAME, ELEMS) static const char *NAME[] = { UNWRAP ELEMS }
#define ARRAY(type, name, initializer) static const type name[] = { UNWRAP initializer }

int
main (void)
{
    WRAP (some_test, ("a", "b", "c"));
    ARRAY(char, another, ('a', 'b', 'c'));
    ARRAY(struct a, more, (1, 2.0));
    ARRAY(struct b, less, ({ 1, 2.0 }, 3));
    printf ("The second element in some_test is: '%s'\n", some_test[1]);
    printf ("The second element in another is: '%c'\n", another[1]);
    return 0;
}

