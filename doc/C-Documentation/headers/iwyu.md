# Include What You Use (IWYU)

Google's [Include What You Use](http://include-what-you-use.org/)
project, or IWYU, ensures source files include all headers used in the
code.

Suppose a source file `source.c` includes a header `arbitrary.h` which
in turn coincidentally includes `freeloader.h`, but the source file also
explicitly and independently uses the facilities from `freeloader.h`.
All is well to start with.
Then one day `arbitrary.h` is changed so its clients no longer need the
facilities of `freeloader.h`.
Suddenly, `source.c` stops compiling — because it didn't meet the IWYU
criteria.
Because the code in `source.c` explicitly used the facilities of
`freeloader.h`, it should have included what it uses — there should
have been an explicit `#include "freeloader.h"` in the source too.

([Idempotency](https://stackoverflow.com/documentation/c/6257/create-and-include-header-files/21638/idempotence)
would have ensured there wasn't a problem.)

The IWYU philosophy maximizes the probability that code continues to
compile even with reasonable changes made to interfaces.
Clearly, if your code calls a function that is subsequently removed from
the published interface, no amount of preparation can prevent changes
becoming necessary.
This is why changes to APIs are avoided when possible, and why there are
deprecation cycles over multiple releases, etc.

This is a particular problem in C++ because standard headers are allowed
to include each other.
Source file `file.cpp` could include one header `header1.h` that on one
platform includes another header `header2.h`.
`file.cpp` might turn out to use the facilities of `header2.h` as well.
This wouldn't be a problem initially - the code would compile because
`header1.h` includes `header2.h`.
On another platform, or an upgrade of the current platform, `header1.h`
could be revised so it no longer includes `header2.h`, and
then`file.cpp` would stop compiling as a result.

IWYU would spot the problem and recommend that `header2.h` be included
directly in `file.cpp`.
This would ensure it continues to compile.
Analogous considerations apply to C code too.
