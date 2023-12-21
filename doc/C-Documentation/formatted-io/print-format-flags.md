# Printing format flags

The C standard (C11, and C99 too) defines the following flags for `printf()`:

| Flag | Conversions | Meaning
|------|-------------|---------|
| `-` | all | The result of the conversion shall be left-justified within the field. The conversion is right-justified if this flag is not specified.
| `+` | signed numeric | The result of a signed conversion shall always begin with a sign ( '+' or '-' ). The conversion shall begin with a sign only when a negative value is converted if this flag is not specified.
| `<space>` | signed numeric | If the first character of a signed conversion is not a sign or if a signed conversion results in no characters, a `<space>` shall be prefixed to the result. This means that if the `<space>` and '`+`' flags both appear, the `<space>` flag shall be ignored.
| `#` | all | Specifies that the value is to be converted to an alternative form. For `o` conversion, it shall increase the precision, if and only if necessary, to force the first digit of the result to be a zero (if the value and precision are both 0, a single 0 is printed). For `x` or `X` conversion specifiers, a non-zero result shall have `0x` (or `0X`) prefixed to it. For `a`, `A`, `e`, `E`, `f`, `F`, `g`, and `G` conversion specifiers, the result shall always contain a radix character, even if no digits follow the radix character. Without this flag, a radix character appears in the result of these conversions only if a digit follows it. For `g` and `G` conversion specifiers, trailing zeros shall not be removed from the result as they normally are. For other conversion specifiers, the behavior is undefined.
| `0` | numeric | For d, i, o, u, x, X, a, A, e, E, f, F, g, and G conversion specifiers, leading zeros (following any indication of sign or base) are used to pad to the field width rather than performing space padding, except when converting an infinity or NaN. If the '0' and '-' flags both appear, the '0' flag is ignored. For d, i, o, u, x, and X conversion specifiers, if a precision is specified, the '0' flag shall be ignored. ⌦ If the '0' and `<apostrophe>` flags both appear, the grouping characters are inserted before zero padding. For other conversions, the behavior is undefined. ⌫

These flags are also supported by [Microsoft](https://msdn.microsoft.com/en-us/library/8aky45ct.aspx) with the same meanings.

The POSIX specification for [`printf()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html) adds:

| Flag | Conversions | Meaning
|------|-------------|---------|
| `'` | i, d, u, f, F, g, G | The integer portion of the result of a decimal conversion shall be formatted with thousands' grouping characters. For other conversions the behavior is undefined. The non-monetary grouping character is used.


