# The `printf()` function

Accessed through including `<stdio.h>`, the function `printf()` is the primary tool used for printing text to the console in C.

    printf("Hello world!");
    // Hello world!

Normal, unformatted character arrays can be printed by themselves by placing them directly in between the parentheses.

    printf("%d is the answer to life, the universe, and everything.", 42);
    // 42 is the answer to life, the universe, and everything.

    int x = 3;
    char y = 'Z';
    char* z = "Example";
    printf("Int: %d, Char: %c, String: %s", x, y, z);
    // Int: 3, Char: Z, String: Example

Alternatively, integers, floating-point numbers, characters, and more can be printed using the escape character `%`, followed by a character or sequence of characters denoting the format, known as the *format specifier*.

All additional arguments to the function `printf()` are separated by commas, and these arguments should be in the same order as the format specifiers. Additional arguments are ignored, while incorrectly typed arguments or a lack of arguments will cause errors or undefined behavior. Each argument can be either a literal value or a variable.

After successful execution, the number of characters printed is returned with type `int`. Otherwise, a failure returns a negative value.

