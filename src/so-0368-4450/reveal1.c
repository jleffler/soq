#include <stdio.h>
#include "reveal1.h"

static void hidden_function(int x)
{
    printf("%s:%s(): %d\n", __FILE__, __func__, x);
}

extern void (*(revealer(void)))(int)
{
    return hidden_function;
}
