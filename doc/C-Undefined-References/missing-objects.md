# Missing object files on the linker command line

The archetypal form of this question is:


* I have created a source file `util.c` containing function
  `utility_func()` and a header file `util.h` which declares it, and my
  main program in `main.c` contains `#include "util.h"`.
  But, when I link the program, the function shows up as missing.

  How do I fix the linker command line so that my program links the
  utility function too?

## Solution — link the correct object files

### TL;DR — include the object files on the command line

If the program uses the code from `util.c` and `main.c`, then you can
compile and link using a variation on the theme of:

    $ gcc -o main -std=c11 -g -O3 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     main.c util.c
    $

Note that although the question didn't mention it, it is crucial that
`util.c` and `main.c` _both_ include `util.h`.
That way, the header is used to cross-check the code defining and using
the function, making sure that all the code agrees on the interface.

### Detailed information

There are multiple ways to treat this problem.

Instead of compiling all the source each time you build the program, you
can separately compile the object files that are out of date with
respect to the source or header files they use, and then link them.
This is more or less what's normal when you use `make` to build your
code.
The linking line might well include the `-W` options.

    $ gcc -c -std=c11 -g -O3 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     main.c
    $ gcc -c -std=c11 -g -O3 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     util.c
    $ gcc -g -o main main.o util.o
    $

You can actually mix object files `.o` and source files `.c` on the command line:

    $ gcc -c -std=c11 -g -O3 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     main.c
    $ gcc -o main -std=c11 -g -O3 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes \
    >     main.o util.c
    $

You might need to add a `-I.` option to the command line to find the
`util.h` header, especially if you used the `#include <util.h>` notation
rather than the `#include "util.h"` notation.
Or you might have to specify the directory holding the header if it is
not the current directory (the `.` is a shorthand for the current
directory).
Generally, use the double quotes for headers you or your project
defines; use the angle brackets for headers defined outside your
immediate project.

If you need to use libraries too, then you add the appropriate `-I
/opt/project/include` options to identify where the headers are kept,
and the appropriate `-L /opt/project/lib` options to identify where the
libraries are kept, and the appropriate library names `-lname` to
identify which libraries should be linked.
Note that the library locations should be specified before the library
names, and the object files (or source files if you're doing a mixed
mode compilation and linking operation) should precede any of the
library names.

### Summary

* Compile each of the source files to a separate object file.
* Link all the object files explicitly on the command line.
* Use the -L /opt/project/lib` style of option to identify where any libraries are stored.
* Use the `-lname` style of option to identify which libraries should be linked.
* Specify the libraries after the object files.
* Specify the libraries in an appropriate order.
* Avoid circular dependencies between libraries.

### Example questions where this was a problem

* [SO 4589-9270](https://stackoverflow.com/q/45899270)
* …list to be filled out…

