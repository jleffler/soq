## Program `inline1`

### `main1.c`

    #include <stdio.h>
    #include <stdlib.h>
    #include "header1.h"

    int main(void) {
      int start = 3;
      int intermediate = complicated1(start);
      printf("First result is %d\n", intermediate);
      intermediate = complicated2(start);
      printf("Second result is %d\n", intermediate);
      return 0;
    }

### `source1a.c`

    #include <stdio.h>
    #include <stdlib.h>
    #include "header1.h"

    int complicated1(int input) {
      int tmp = timestwo(input);
      return plusfive(tmp);
    }

### `source1b.c`

    #include <stdio.h>
    #include <stdlib.h>
    #include "header1.h"

    int complicated2(int input) {
      int tmp = plusfive(input);
      return timestwo(tmp);
    }

### `header1.h`

    #ifndef HEADERFILE_H
    #define HEADERFILE_H
    int complicated1(int input);
    int complicated2(int input);
    static inline int timestwo(int input) {
      return input * 2;
    }
    static inline int plusfive(int input) {
      return input + 5;
    }
    #endif

Functions `timestwo()` and `plusfive()` get called by both
`complicated1()` and `complicated2()`, which are in different
"translation units", or source files.
In order to use them in this way, we have to define them in the header.

Compile like this (we assume we're using gcc):

    cc -O2 -std=c99 -c -o main1.o main1.c
    cc -O2 -std=c99 -c -o source1a.o source1a.c
    cc -O2 -std=c99 -c -o source1b.o source1b.c
    cc main1.o source1a.o source1a.o -o inline1

We use the -O2 optimization option because some compilers don't inline
without optimization turned on.

### Program `inline2`

The files `main2.c`, `source2a.c`, `source2b.c`, `header2.h` are very
similar, but instead of the `inline` functions being `static`, they are
not marked static.

Note that C99 seems to require an extra extern declaration of the
inlined functions in exactly one of the source files.
So, add:

    extern int timestwo(int input);
    extern int plusfive(int input);

### Program `inline3`

