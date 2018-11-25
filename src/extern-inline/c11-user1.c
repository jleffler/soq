#include "c11-extern.h"

int fn_regular1(int x)
{
    return fn_inline(x) * 5 - 3;
}
