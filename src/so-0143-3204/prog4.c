#include "file3b.h"
#include "prog4.h"
#include <stdio.h>

int main(void)
{
    use_them();
    global_variable += 19;
    use_them();
    printf("Increment: %d\n", increment());
    printf("Oddball:   %d\n", oddball_value());
    return 0;
}
