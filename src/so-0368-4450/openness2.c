#include <stdio.h>
#include "reveal2.h"

int main(void)
{
    HiddenFunctionType revelation = revealer();
    printf("%s:%s: %d\n", __FILE__, __func__, __LINE__);
    (*revelation)(37);
    return 0;
}
