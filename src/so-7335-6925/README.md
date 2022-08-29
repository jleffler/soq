### Stack Overflow Question 7335-6925

[SO 7335-6925](https://stackoverflow.com/q/73356925) &mdash;
Is GCC 11.2.0 or Apple Clang 13.0.0 (clang-1300.0.29.30) correct about const applied to VLA arguments?

Consider this C code:
```
#include <stdio.h>

static void print_matrix(size_t rows, size_t cols, const int data[rows][cols])
{
    for (size_t r = 0; r < rows; r++)
    {
        const char *pad = "";
        for (size_t c = 0; c < cols; c++)
        {
            printf("%s%3d", pad, data[r][c]);
            pad = "  ";
        }
        putchar('\n');
    }
}

int main(void)
{
    /* Created by: gen_matrix -r 3 -c 5 -L 0 -H 999 -n matrix -E -w 3 -S 0x08C777A9 -i */
    /* Random seed: 0x08C777A9 */
    int matrix[3][5] =
    {
        { 984, 843, 464, 599,  17, },
        { 876, 173, 647,  61, 387, },
        { 138, 245, 718, 981, 629, },
    };
    enum { MATRIX_ROWS = 3, MATRIX_COLS = 5 };

    print_matrix(MATRIX_ROWS, MATRIX_COLS, matrix);

    return 0;
}
```
This is the `makefile` I used:
```
# Makefile to demonstrate inconsistency between GCC 11.2.0 and Apple Clang 13.0.0.

CC = gcc

OFLAGS = -O3
GFLAGS = -g
WFLAG1 = -Werror
WFLAG2 = -Wall
WFLAG3 = -Wextra
WFLAG4 = -pedantic
WFLAG5 = -pedantic-errors
UFLAGS = # Set on command line

WFLAGS = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5}
CFLAGS = ${OFLAGS} ${GFLAGS} ${WFLAGS} ${UFLAGS}

PROG1 = gcc23
FILE.c = ${PROG1}.c

PROGRAMS = ${PROG1}

all: ${PROGRAMS}

${PROG1}:
	${CC} ${CFLAGS} ${FILE.c} -o $@
```
I have two compilers:
```none
$ gcc --version
gcc (GCC) 11.2.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ clang --version
Apple clang version 13.0.0 (clang-1300.0.29.30)
Target: x86_64-apple-darwin20.6.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
$
```
Consider the following build records:
```
$ rm -f gcc23
$ make CC=gcc 
gcc -O3 -g -Werror -Wall -Wextra -pedantic -pedantic-errors  gcc23.c -o gcc23
gcc23.c: In function ‘main’:
gcc23.c:29:44: error: pointers to arrays with different qualifiers are incompatible in ISO C [-Wpedantic]
   29 |     print_matrix(MATRIX_ROWS, MATRIX_COLS, matrix);
      |                                            ^~~~~~
make: *** [gcc23] Error 1
$ rm -f gcc23
$ make CC=clang
clang -O3 -g -Werror -Wall -Wextra -pedantic -pedantic-errors  gcc23.c -o gcc23
$ rm -f gcc23
$ make CC=clang UFLAGS=-Weverything
clang -O3 -g -Werror -Wall -Wextra -pedantic -pedantic-errors -Weverything gcc23.c -o gcc23
error: include location '/usr/local/include' is unsafe for cross-compilation [-Werror,-Wpoison-system-directories]
gcc23.c:3:73: error: variable length array used [-Werror,-Wvla]
static void print_matrix(size_t rows, size_t cols, const int data[rows][cols])
                                                                        ^~~~
gcc23.c:3:67: error: variable length array used [-Werror,-Wvla]
static void print_matrix(size_t rows, size_t cols, const int data[rows][cols])
                                                                  ^~~~
3 errors generated.
make: *** [gcc23] Error 1
$
```
Adding `-std=c99`, `-std=c11` or `-std=c18` does not alter the
compilation errors.  The errors from compiling with Clang's
`-Weverything` option are not related to the `const` qualifier on the
function argument.  Adding `-Wno-vla` means the code compiles cleanly
under Clang (and the `-Werror,-Wpoison-system-directories` error goes
away too).

As you can see, GCC complains about the addition of `const` to the argument to the function, but Clang does not.

* Which is correct, and why?

I want it to be Clang that's correct — that is consistent with my expectations.


