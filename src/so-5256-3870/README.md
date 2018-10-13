### Stack Overflow Question 5256-3870

[SO 5256-3870](https://stackoverflow.com/q/52563870) &mdash;
Need help debugging

Appalling question title!

There's an [answer](https://stackoverflow.com/a/52563945/15168) by
[Ian](https://stackoverflow.com/users/4078718/ian) which is mostly OK,
but runs it avoids problems with the limited range of `int` by using `long long`.
This is OK, but the strategy runs into problems if the data is not `int` but is
already `long long` data.

I created three variant solutions, which will probably be posted
soon.

### `array-range-17.c`

This solution sticks with using only `int` and the corresponding
`unsigned` type and works correctly even when the input involves
`INT_MIN` and `INT_MAX`.
It's been verified with two's-complement machines; in principle it will
work on one's-complement or sign-magnitude machines too, but I've no way
of verifying that.

### `array-range-19.c`

This solution is based on `array-range-19.c` but parameterizes the code
so it could be used with base types `long long` and `unsigned long
long`, where there is (probably) no longer the option of using a longer
type, or with `intmax_t` and `uintmax_t` where that is definitely the
case.

The printing formats are trickier as a result!

### `array-range-23.c`

This solution works with unsigned data types, but is based on the
parameterized `array-range-19.c` solution.
This is a much easier problem to solve; there are no overflow problems
to worry about (and the values always have the same sign, of necessity).

