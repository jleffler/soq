# Missing library on the linker command line

The archetypal form of this question is:

* I used `#include <header.h>` from the SOQ library but when I link the
  program, I get messages about 'undefined' functions declared in the
  header, such as:

        $ gcc -g -o sets sets.o
        Undefined symbols for architecture x86_64:
        "_err_setarg0", referenced from:
            _main in sets.o
        "_err_syserr", referenced from:
            _main in sets.o
        ld: symbol(s) not found for architecture x86_64
        collect2: error: ld returned 1 exit status
        $

  These particular error messages are from GCC 7.2.0 on a Mac running
  macOS Sierra 10.12.6 while linking an object file `sets.o` created
  from the source file `sets.c`, but similar messages can appear on any
  platform.  For example, on Ubuntu 16.04 LTS, the messages from the
  same source code were:

        $ gcc -g -o sets sets.o
        sets.o: In function `main':
        .../so-3109-6894/sets.c:184: undefined reference to `err_setarg0'
        sets.o: In function `test_set':
        .../so-3109-6894/sets.c:176: undefined reference to `err_syserr'
        collect2: error: ld returned 1 exit status
        $

  How do I fix the linker command line so that my program links the
  library?

## Solution — link the correct library

### TL;DR — include the library on the command line

If the library defining the missing symbols is `libsoq.a` or similar,
and the library is found in `/opt/soq/lib`, then link using a variation
on the theme of:

    $ gcc -g -o sets sets.o -L /opt/soq/lib -lsoq

Note that the library name (`-lsoq`) option must come after the object
files for reliable linking.
The library location option (`-L /opt/soq/lib`) may appear anywhere on
the command line after the compiler name and before the library is
mentioned.

### Detailed information

There are multiple facets to this problem.

* The header tells the compiler about what is in the library, but not
  where the library is found.
* You need to specify where the library is found and what its name is.
* You often need to get the order of object files and libraries correct.

### The header says 'what', not 'where'

Often, when you are compiling with an external library, you need to tell
the compiler where to find the header files it provides, and you need to
tell the linker where to find the library (or libraries) for the
external project.
Sometimes, the headers and the library are installed in a location that
the compiler searches anyway, in which case you don't need to specify
the location again.
You need to know where the software is installed — on Linux and
Unix-like machines, that might be under `/usr/local` (with the headers
in `/usr/local/include` and the libraries in `/usr/local/lib`), which
will quite possibly be searched automatically, or it might be somewhere
like `/opt/project` (with the headers in `/opt/project/include` and the
libraries in `/opt/project/lib`) which will probably not be searched
automatically.

If the header directory is not searched automatically, you need to add
a compilation command line option which is normally:

    -I /opt/project/include

If there are compilation problems with that, look to see where the
missing header files are under `/opt/project`, and look at the
documentation to see how you're supposed to include the headers.
If the documentation says:

    #include <project/project.h>

then you would probably find `/opt/project/include/project/project.h`,
and as long as you write the `#include` as documented and use `-I
/opt/project/include`, everything will work.
If you decide you know better and use `#include <project.h>` instead,
the compilation is likely to fail — even if you specify `-I
/opt/project/include/project` on the command line to identify where the
`project.h` header is.

The header declares the facilities available to programs using the
header.
It does not necessarily provide the code that implements those
facilities.
This is an area of difference between C and modern C++.
Modern C++ has many 'header only' libraries where the code is mostly
template definitions, and you don't actually have to provide the object
code at link time; the C++ compiler does that for you.
Header-only libraries are more of a rarity in C.

When you link the program, you need to specify the location of the
library before the name of the library, but you do need to specify the
library name.
The compiler will search a few standard libraries, but they're the ones
provided by 'the implementation' (the standard C library, the POSIX
libraries, maybe the maths (yes, 'math' to Americans; this is English
text) library, etc).
Project libraries have to be specified on the command line explicitly.

You normally specify a library using the notation `-lname` or `-l name` (both work).
This indicates that the linker should look in the library search
directories for a file named like:

* `libname.a` — Unix/POSIX static library
* `libname.so` — Unix shared library
* `libname.dll` — Windows shared library
* `libname.dylib` — macOS (or Mac OS X) shared library
* `libname.lib` — Windows static library (sometimes; sometimes relatred to a DLL)
* `libname.sa` — Old AIX extension for shared objects
* `libname.shlib` — Old HP-UX extension for shared objects

Note the key points: the name starts `lib`, contains the portion of the
name from the `-l` option, and then has an appropriate platform-specific
suffix.
Depending on the system, you may find that the runtime system picks up a
name such as `libname.so.2.3.1`, but this is rapidly getting off-topic.

