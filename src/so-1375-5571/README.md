### Sign extending an int in C

The code submitted as an answer on 2012-12-07 no longer compiles
cleanly, generating:

    gfsx.c: In function ‘getFieldSignExtended’:
    gfsx.c:18:27: error: left shift of negative value [-Werror=shift-negative-value]
             return(bits | (~0 << (hi - lo)));
                               ^~
    cc1: all warnings being treated as errors

The answer did note that you run into implementation-defined behaviour
from right-shifting negative values; it didn't note the same for
left-shifting.  The solution is simple: use 0U instead of 0.
