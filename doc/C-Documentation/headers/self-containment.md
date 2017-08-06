# Self-containment

Modern headers should be self-contained, which means that a program that needs to use the facilities defined by `header.h` can include that header (`#include "header.h"`) and not worry about whether other headers need to be included first.

## Recommendation: Header files should be self-contained.

<hr>

### Historical rules

Historically, this has been a mildly contentious subject.

Once upon another millennium, the [AT&T Indian Hill C Style and Coding
Standards](http://www.literateprogramming.com/indhill-annot.pdf) stated:

>  Header files should not be nested.
>  The prologue for a header file should, therefore, describe what other
>  headers need to be `#include`d for the header to be functional.
>  In extreme cases, where a large number of header files are to be
>  included in several different source files, it is acceptable to put
>  all common `#include`s in one include file.

This is the antithesis of self-containment.

### Modern rules

However, since then, opinion has tended in the opposite direction.
If a source file needs to use the facilities declared by a header
`header.h`, the programmer should be able to write:

    #include "header.h"

and (subject only to having the correct search paths set on the command
line), any necessary pre-requisite headers will be included by
`header.h` without needing any further headers added to the source file.

This provides better modularity for the source code.
It also protects the source from the "guess why this header was added" conundrum that arises after the code has been modified and hacked for a decade or two.

The [NASA Goddard Space Flight Center (GSFC) coding standards for
C](http://stackoverflow.com/questions/1804486/should-i-use-include-in-headers)
is one of the more modern standards &mdash; but is now a little hard to
track down.
It states that headers should be self-contained.
It also provides a simple way to ensure that headers are self-contained:
the implementation file for the header should include the header as the first
header.
If it is not self-contained, that code will not compile.

The rationale given by GSFC includes:

> §2.1.1 Header include rationale

> This standard requires a unit’s header to contain `#include`
  statements for all other headers required by the unit header.
  Placing `#include` for the unit header first in the unit body allows
  the compiler to verify that the header contains all required
  `#include` statements.

> An alternate design, not permitted by this standard, allows no
  `#include` statements in headers; all `#includes` are done in the body
  files.
  Unit header files then must contain #ifdef statements that check that
  the required headers are included in the proper order.

> One advantage of the alternate design is that the `#include` list in
  the body file is exactly the dependency list needed in a makefile, and
  this list is checked by the compiler.
  With the standard design, a tool must be used to generate the
  dependency list.
  However, all of the branch recommended development environments
  provide such a tool.

> A major disadvantage of the alternate design is that if a unit’s
  required header list changes, each file that uses that unit must be
  edited to update the `#include` statement list.
  Also, the required header list for a compiler library unit may be
  different on different targets.

> Another disadvantage of the alternate design is that compiler library
  header files, and other third party files, must be modified to add the
  required `#ifdef` statements.

Thus, self-containment means that:

* If a header `header.h` needs a new nested header `extra.h`, you do not
  have to check every source file that uses `header.h` to see whether
  you need to add `extra.h`.
* If a header `header.h` no longer needs to include a specific header
  `notneeded.h`, you do not have to check every source file that uses
  `header.h` to see whether you can safely remove `notneeded.h` (but see [Include what you use](https://stackoverflow.com/documentation/c/6257/create-and-include-header-files/21641/include-what-you-use-iwyu).
* You do not have to establish the correct sequence for including the
  pre-requisite headers (which requires a topological sort to do the job
  properly).

### Checking self-containment

See [Linking against a static
  library](http://stackoverflow.com/questions/4507896) for a script
  `chkhdr` that can be used to test idempotence and self-containment of
  a header file.
