# Conversion specifiers for printing

| Conversion Specifier| Type of Argument  | Description |
|---|---|---|
| `i`, `d` | int | prints decimal
| `u`    | unsigned int | prints decimal
| `o`    | unsigned int | prints octal |
| `x`    | unsigned int | prints hexadecimal, lower-case |
| `X`    | unsigned int | prints hexadecimal, upper-case |
| `f`    | double | prints float with a default precision of 6, if no precision is given (lower-case used for special numbers `nan` and `inf` or `infinity`) |
| `F`    | double | prints float with a default precision of 6, if no precision is given (upper-case used for special numbers `NAN` and `INF` or `INFINITY`) |
| `e`    | double | prints float with a default precision of 6, if no precision is given, using scientific notation using mantissa/exponent; lower-case exponent and special numbers |
| `E`    | double | prints float with a default precision of 6, if no precision is given, using scientific notation using mantissa/exponent; upper-case exponent and special numbers |
| `g`    | double |  uses either `f` or `e` *[see below]*|
| `G`    | double |  uses either `F` or `E` *[see below]*|
| `a`    | double | prints hexadecimal, lower-case |
| `A`    | double | prints hexadecimal, upper-case |
| `c`    | char | prints single character |
| `s`    | char* | prints string of characters up to a `NUL` terminator, or truncated to length given by precision, if specified |
| `p`    | void* | prints `void`-pointer value; a non`void`-pointer should be explicitly converted ("cast") to `void*`; pointer to object only, **not** a function-pointer  |
| `%` | n/a | prints the `%` character |
| `n` | int * | ***write*** the number of bytes printed so far into the `int` pointed at. |

Note that length modifiers can be applied to `%n` (e.g. `%hhn` indicates that _a following `n` conversion specifier applies to a pointer to a `signed char`
argument_, according to the ISO/IEC 9899:2011 §7.21.6.1 ¶7).

Note that the floating point conversions apply to types `float` and `double` because of default promotion rules — §6.5.2.2 Function calls, ¶7 _The ellipsis notation in a function prototype declarator causes
argument type conversion to stop after the last declared parameter. The default argument
promotions are performed on trailing arguments._)  Thus, functions such as `printf()` are only ever passed `double` values, even if the variable referenced is of type `float`.

With the `g` and `G` formats, the choice between `e` and `f` (or `E` and `F`) notation is documented in the C standard and in the POSIX specification for [`printf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html):

> The double argument representing a floating-point number shall be converted in the style `f` or `e` (or in the style `F` or `E` in the case of a `G` conversion specifier), depending on the value converted and the precision. Let `P` equal the precision if non-zero, 6 if the precision is omitted, or 1 if the precision is zero. Then, if a conversion with style `E` would have an exponent of `X`:

>    - If P > X >= -4, the conversion shall be with style `f` (or `F`) and precision `P - (X+1)`.
>    - Otherwise, the conversion shall be with style `e` (or `E`) and precision `P - 1`.

> Finally, unless the '#' flag is used, any trailing zeros shall be removed from the fractional portion of the result and the decimal-point character shall be removed if there is no fractional portion remaining.

