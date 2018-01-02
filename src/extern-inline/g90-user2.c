#include "g90-extern.h"

int fn_regular2(int x)
{
    return fn_inline(-x) * 3 - 5;
}
