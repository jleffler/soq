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
