#if defined(TEST_G90)
#define INLINE_HDR "g90-inline.h"
#define EXTERN_HDR "g90-extern.h"
#elif defined(TEST_C11)
#define INLINE_HDR "c11-inline.h"
#define EXTERN_HDR "c11-extern.h"
#else
#error Neither TEST_G90 nor TEST_C11 is defined
#endif

#include INLINE_HDR
#include EXTERN_HDR

#include <stdio.h>

int main(void)
{
    int i;      /* Has to be compiled with C90 as well as C11 */
    for (i = 0; i < 10; i++)
        printf("%4d -> %4d : %4d : %4d\n", i, fn_inline(i), fn_regular1(i), fn_regular2(i));
    return 0;
}
