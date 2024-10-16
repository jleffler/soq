/* SO 7785-1120 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#undef exit

/* This could (should?) include _Noreturn in the definition because it doesn't return */
static int terminate(int x)
{
    exit(x);
    return x;
}

#define exit(x) terminate(x)

static void notification(void)
{
    printf("PID = %d\n", getpid());
}

int main(void)
{
    atexit(notification);
    int x = 0;
    for (fork(); !fork(); exit(x))
        for (fork(); exit(x); fork())
            for (exit(x); fork(); fork())
                ;

    printf("%d\n", ++x);
    return 0;
}
