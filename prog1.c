#include "file3.h"
#include "prog1.h"
#include <stdio.h>

int main(void)
{
    use_it();
    global_variable += 19;
    use_it();
    printf("Increment: %d\n", increment());
    return 0;
}
