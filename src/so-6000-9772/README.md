## Stack Overflow Question 6000-9772

[SO 6000-9772](https://stackoverflow.com/q/60009772) &mdash;
Signed integer division with rounding in C

## Question

I'd like to calculate x/y where x and y are both signed integers, and
get a result rounded to the nearest integer.  Specifically, I'd like a
function `rquotient(x, y)` using integer-only arithmetic such that:

    ASSERT(rquotient(59, 4) == 15);
    ASSERT(rquotient(59, -4) == -15);
    ASSERT(rquotient(-59, 4) == -15);
    ASSERT(rquotient(-59, -4) == 15);

    ASSERT(rquotient(57, 4) == 14);
    ASSERT(rquotient(57, -4) == -14);
    ASSERT(rquotient(-57, 4) == -14);
    ASSERT(rquotient(-57, -4) == 14);

I've looked to S.O. for a solution and found the following (each with their own shortcoming):

* https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating (round up only)
* https://stackoverflow.com/questions/36917405/integer-division-with-rounding (positive x and y only)
* https://stackoverflow.com/questions/3950372/round-with-integer-division (positive x and y only)
* https://stackoverflow.com/questions/4085239/integer-division-rounding (positive y only, but a good suggestion in the comments)
* https://stackoverflow.com/questions/319880/integer-division-rounding-with-negatives-in-c (question about the standard, not a solution)

## Answer

### Timing suggested solutions

The code presented here tests the performance of the 3 suggested
functions in the [answer](https://stackoverflow.com/a/60009773/15168) by
[fearless_fool](https://stackoverflow.com/users/558639/fearless-fool)
and the solution in the
[answer](https://stackoverflow.com/a/60009901/15168) by
[Ayxan](https://stackoverflow.com/users/10147399/ayxan).  The functions
are modified to always take `int` arguments (the `const` in `int const
x` is not needed), but the test code only uses test values in the range
where both `x` and `y` are non-negative.

The code uses a set of timing functions available in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository on GitHub as files `timer.c` and `timer.h` in the
[src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.

    #define NDEBUG 1

    #include "timer.h"
    #include <assert.h>
    #include <limits.h>
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>

    /* JL: added static to rquotient_xx functions */

    /* JL: removed two const qualifiers */
    static
    int rquotient_dd(int x, int y)
    {
        return (int)round((double)x / y);
    }

    /* JL: removed unsigned - added assert */
    static
    int rquotient_uu(int x, int y)
    {
        assert(x >= 0 && y > 0);
        return (x + y / 2) / y;
    }

    /* JL: removed unsigned - added assert */
    static
    int rquotient_su(int x, int y)
    {
        assert(y > 0);
        if (x > 0)
            return (x + y / 2) / y;
        else
            return (x - y / 2) / y;
    }

    static
    int rquotient_ss(int x, int y)
    {
        if ((x ^ y) > 0)
            return (x + y / 2) / y;
        else
            return (x - y / 2) / y;
    }

    typedef int (*Divider)(int x, int y);

    static void test_harness(const char *tag, Divider function)
    {
        Clock clk;
        unsigned long long accumulator = 0;

        clk_init(&clk);

        clk_start(&clk);
        for (int i = 1; i < INT_MAX / 1024; i += 13)
        {
            int max_div = i / 4;
            if (max_div == 0)
                max_div = 1;
            for (int j = 1; j < max_div; j += 15)
                accumulator += (*function)(i, j);
        }
        clk_stop(&clk);

        char buffer[32];
        printf("%s: %10s  (%llu)\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)), accumulator);
    }

    int main(void)
    {
        for (int i = 0; i < 10; i++)
        {
            test_harness("rquotient_uu", rquotient_uu);
            test_harness("rquotient_su", rquotient_su);
            test_harness("rquotient_ss", rquotient_ss);
            test_harness("rquotient_dd", rquotient_dd);
        }
        return 0;
    }

The use of `accumulator` serves two important purposes.  First, it
checks that the different computations produce the same results.
Secondly, it ensures that the compiler cannot optimize the loops away
— the accumulated value must be printed.  It is reassuring to see that
the accumulated value is the same on all tests.  The oddball constants
(`INT_MAX / 1024`, `13`, `15`) are guessed values that yield reasonable
times on the test machine — they mean the tests cover quite a lot of
values, without taking inappropriately long times.

### Performance test results

I ran the tests on a MacBook Pro (15 inch, 2017 — with a 2.9 GHz Intel
Core i7 chip and 16 GiB of 2133 Mhz LPDDR3 RAM) running macOS 10.14.6
Mojave, compiled with (home-built) GCC 9.2.0 and the Xcode 11.3.1
toolchain.

    $ gcc -O3 -g -I./inc -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     iround53.c -o iround53 -L./lib -lsoq 
    $

One set of timing results was:

    rquotient_uu:   6.272698  (286795780245)
    rquotient_su:   6.257373  (286795780245)
    rquotient_ss:   6.221263  (286795780245)
    rquotient_dd:  10.956196  (286795780245)
    rquotient_uu:   6.247602  (286795780245)
    rquotient_su:   6.289057  (286795780245)
    rquotient_ss:   6.258776  (286795780245)
    rquotient_dd:  10.878083  (286795780245)
    rquotient_uu:   6.256511  (286795780245)
    rquotient_su:   6.286257  (286795780245)
    rquotient_ss:   6.323997  (286795780245)
    rquotient_dd:  11.055200  (286795780245)
    rquotient_uu:   6.256689  (286795780245)
    rquotient_su:   6.302265  (286795780245)
    rquotient_ss:   6.296409  (286795780245)
    rquotient_dd:  10.943110  (286795780245)
    rquotient_uu:   6.239497  (286795780245)
    rquotient_su:   6.238150  (286795780245)
    rquotient_ss:   6.195744  (286795780245)
    rquotient_dd:  10.975971  (286795780245)
    rquotient_uu:   6.252275  (286795780245)
    rquotient_su:   6.218718  (286795780245)
    rquotient_ss:   6.241050  (286795780245)
    rquotient_dd:  10.986962  (286795780245)
    rquotient_uu:   6.254244  (286795780245)
    rquotient_su:   6.213412  (286795780245)
    rquotient_ss:   6.280628  (286795780245)
    rquotient_dd:  10.963290  (286795780245)
    rquotient_uu:   6.237975  (286795780245)
    rquotient_su:   6.278504  (286795780245)
    rquotient_ss:   6.286199  (286795780245)
    rquotient_dd:  10.984483  (286795780245)
    rquotient_uu:   6.219504  (286795780245)
    rquotient_su:   6.208329  (286795780245)
    rquotient_ss:   6.251772  (286795780245)
    rquotient_dd:  10.983716  (286795780245)
    rquotient_uu:   6.369181  (286795780245)
    rquotient_su:   6.362766  (286795780245)
    rquotient_ss:   6.299449  (286795780245)
    rquotient_dd:  11.028050  (286795780245)

When analyzed, the mean and sample standard deviation for the different functions are:

    Function       Count   Mean        Standard deviation
    rquotient_uu      10    6.260618   0.040679 (sample)
    rquotient_su      10    6.265483   0.048249 (sample)
    rquotient_ss      10    6.265529   0.039216 (sample)
    rquotient_dd      10   10.975506   0.047673 (sample)

It doesn't take much statistical knowledge to see that there is
essentially no performance difference between the three 'all integer'
functions, because the difference between the three means is much less
than one standard deviation (and to be significant, it would need to be
more than one standard deviation).  Nor does it take much skill to
observe that converting to `double`, dividing, rounding, and converting
back to integer takes almost twice as long as the all-integer versions.
In times (long) past, the integer vs floating-point discrepancy could
have been a lot larger.  There is a modest amount of overhead in the
loop calculations and accumulation; that would widen the disparity
between the integer and floating-point computations.

The machine running the test had various programs open in the
background, but there were no videos playing, the browser was showing
Stack Overflow rather than advert-laden pages, and I was tinkering on a
cell phone while the test ran on the laptop.  One attempted test run,
during which I flicked between pages on the browser, showed much more
erratic timing (longer times while I was using the browser, even though
it is a multi-core machine).

Other tests with the condition `if ((x ^ y) > 0)` corrected to `if ((x ^
y) >= 0)` yielded slightly different timing results (but the same value
for `accumulator`):

    rquotient_su     10    6.272791    0.037206
    rquotient_dd     10    9.396147    0.047195
    rquotient_uu     10    6.293301    0.056585
    rquotient_ss     10    6.271035    0.052786

    rquotient_su     10    6.187112    0.131749
    rquotient_dd     10    9.100924    0.064599
    rquotient_uu     10    6.127121    0.092406
    rquotient_ss     10    6.203070    0.219747

    rquotient_su     10    6.171390    0.133949
    rquotient_dd     10    9.195283    0.124936
    rquotient_uu     10    6.214054    0.177490
    rquotient_ss     10    6.166569    0.138124

The performance difference for the floating-point arithmetic is not
quite so pronounced, but still definitively in favour of integer
arithmetic.  The last of those tests, in particular, suggest there was
some other activity on the machine while the tests were running —
though that wasn't me looking at web pages or anything.

<hr>

### Using `-ffast-math`

[Ayxan](https://stackoverflow.com/users/10147399/ayxan) asked:

> I wonder if `-ffast-math` would have made a difference.

I recompiled with the extra option, and it does indeed make a
difference.  Note that the original code was compiled with `-O3` — it
was optimized.  However, the raw data from a run with `-ffast-math` was:

    rquotient_uu:   6.162182  (286795780245)
    rquotient_su:   6.068469  (286795780245)
    rquotient_ss:   6.041566  (286795780245)
    rquotient_dd:   4.568538  (286795780245)
    rquotient_uu:   6.143200  (286795780245)
    rquotient_su:   6.071906  (286795780245)
    rquotient_ss:   6.063543  (286795780245)
    rquotient_dd:   4.543419  (286795780245)
    rquotient_uu:   6.115283  (286795780245)
    rquotient_su:   6.083157  (286795780245)
    rquotient_ss:   6.063975  (286795780245)
    rquotient_dd:   4.536071  (286795780245)
    rquotient_uu:   6.078680  (286795780245)
    rquotient_su:   6.072075  (286795780245)
    rquotient_ss:   6.104850  (286795780245)
    rquotient_dd:   4.585272  (286795780245)
    rquotient_uu:   6.084941  (286795780245)
    rquotient_su:   6.080311  (286795780245)
    rquotient_ss:   6.069046  (286795780245)
    rquotient_dd:   4.563945  (286795780245)
    rquotient_uu:   6.075380  (286795780245)
    rquotient_su:   6.236980  (286795780245)
    rquotient_ss:   6.210127  (286795780245)
    rquotient_dd:   4.787269  (286795780245)
    rquotient_uu:   6.406603  (286795780245)
    rquotient_su:   6.378812  (286795780245)
    rquotient_ss:   6.194098  (286795780245)
    rquotient_dd:   4.589568  (286795780245)
    rquotient_uu:   6.243652  (286795780245)
    rquotient_su:   6.132142  (286795780245)
    rquotient_ss:   6.079181  (286795780245)
    rquotient_dd:   4.595330  (286795780245)
    rquotient_uu:   6.070584  (286795780245)
    rquotient_su:   6.081373  (286795780245)
    rquotient_ss:   6.075867  (286795780245)
    rquotient_dd:   4.558105  (286795780245)
    rquotient_uu:   6.106258  (286795780245)
    rquotient_su:   6.091108  (286795780245)
    rquotient_ss:   6.128787  (286795780245)
    rquotient_dd:   4.553061  (286795780245)

And the statistics from that are:

    rquotient_su     10    6.129633    0.101331
    rquotient_dd     10    4.588058    0.072669
    rquotient_uu     10    6.148676    0.104937
    rquotient_ss     10    6.103104    0.057498

It doesn't take a statistical genius to spot that this shows the
`-ffast-math` floating-point alternative is now better than the integer
version — by a similar factor to how integer was better than
floating-point without the extra compiler option.

One more set of statistics with `-ffast-math`.  These show smaller
variances (standard deviations), but the same overall result.

    rquotient_su     10    6.060705    0.024372
    rquotient_dd     10    4.543576    0.014742
    rquotient_uu     10    6.057718    0.026419
    rquotient_ss     10    6.061652    0.034652

For 32-bit integers, it would appear that with `-ffast-math`, the code
using `double` can be faster than the code using only integers.

If the range was changed from 32-bit integers to 64-bit integers, then
64-bit doubles would not be able to represent all integer values
exactly.  At that point, if the numbers being divided are large enough,
you could start finding accuracy errors (the accumulator results might
well be different).  A 64-bit double effectively has 53 bits to
represent the mantissa, so if the number of bits in the integers were
larger than that, accuracy drops.

<hr>

# Performance testing is hard.  [YMMV!](https://acronymfinder.com/YMMV.html)

Indeed, it might be safer to say "Your Milage ___WILL___ Vary".
