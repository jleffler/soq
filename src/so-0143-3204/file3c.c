#define DEFINE_VARIABLES
#include "file2c.h"  /* Variables now defined and initialized */

int increment(void) { return global_variable++; }
int oddball_value(void) { return oddball_struct.a + oddball_struct.b; }

