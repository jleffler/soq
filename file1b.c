#define DEFINE_VARIABLES
#include "file3b.h"  /* Variables now defined and initialized */
#include "prog4.h"

int increment(void) { return global_variable++; }
int oddball_value(void) { return oddball_struct.a + oddball_struct.b; }

