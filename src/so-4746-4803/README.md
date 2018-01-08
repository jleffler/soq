### Stack Overflow Question 4746-4803

[SO 4746-4803](https://stackoverflow.com/q/47464803) &mdash;
How to optimize Matrix initialization and transposition to run faster using C

Interesting code.

The matrix transposition code has a simpler and a more complex version,
and the more complex version dramatically outperforms the simpler
version due to controlling the access more tightly (fewer page misses).

At reduced scales (say 4k x 4k), the benefit of the complex version is
small to minimal.
At full scale (40k x 40k), the benefit is quite startling.

NB: On Cygwin, neither mtx61 nor mtx83 links successfully.
Most likely, this is because there's a monstrous global array

    enum { DIMENSION = 40000, BLOCKSIZE = 500 };

    static double Matrix[DIMENSION][DIMENSION];

since essentially the same code (mtx61p.c, mtx83p.c) with `DIMENSION`
set to 4000 links fine.

Work around this with `make -t mtx61 mtx83`.
It's not entirely satisfactory, but neither is life, sometimes.
