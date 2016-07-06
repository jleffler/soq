#include "file3b.h"
#include "prog4.h"
#include <stdio.h>

void use_them(void)
{
    printf("Global variable: %d\n", global_variable++);
    oddball_struct.a += global_variable;
    oddball_struct.b -= global_variable / 2;
}
