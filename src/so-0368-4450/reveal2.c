#include <stdio.h>
#include "reveal2.h"

static void hidden_function(int x)
{
    printf("%s:%s(): %d\n", __FILE__, __func__, x);
}

extern HiddenFunctionType revealer(void)
{
    return hidden_function;
}
