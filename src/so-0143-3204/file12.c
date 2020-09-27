#include "prog2.h"
#include <stdio.h>

long l = 9;   /* Do not do this in portable code */

void put(void) { printf("l = %ld\n", l); }
