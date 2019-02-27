#include <stdio.h>
#include "reveal1.h"

int main(void)
{
    void (*revelation)(int) = revealer();
    printf("%s:%s: %d\n", __FILE__, __func__, __LINE__);
    (*revelation)(37);
    return 0;
}
