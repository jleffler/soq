# Notation and Miscellany


The C standard says that there is very little difference between the
`#include <header.h>` and `#include "header.h"` notations.

> [`#include <header.h>`] searches a sequence of implementation-defined
> places for a header identified uniquely by the specified sequence
> between the `<` and `>` delimiters, and causes the replacement of that
> directive by the entire contents of the header.
> How the places are specified or the header identified is
> implementation-defined.

> [`#include "header.h"`] causes the replacement of that directive by
> the entire contents of the source file identified by the specified
> sequence between the `"…"` delimiters.
> The named source file is searched for in an implementation-defined
> manner.
> If this search is not supported, or if the search fails, the directive
> is reprocessed as if it read [`#include <header.h>`] …

So, the double quoted form may look in more places than the
angle-bracketed form.
The standard specifies by example that the standard headers should be
included in angle-brackets, even though the compilation works if you use
double quotes instead.
Similarly, standards such as POSIX use the angle-bracketed format
&mdash; and you should too.
Reserve double-quoted headers for headers defined by the project.
For externally-defined headers (including headers from other projects
your project relies on), the angle-bracket notation is most appropriate.

Note that there should be a space between `#include` and the header,
even though the compilers will accept no space there.
Spaces are cheap.

A number of projects use a notation such as:

    #include <openssl/ssl.h>
    #include <sys/stat.h>
    #include <linux/kernel.h>

You should consider whether to use that namespace control in your
project (it is quite probably a good idea).
You should steer clear of the names used by existing projects (in
particular, both `sys` and `linux` would be bad choices).

If you use this, your code should be careful and consistent in the use
of the notation.

Do not use `#include "../include/header.h"` notation.

Header files should seldom if ever define variables.
Although you will keep global variables to a minimum, if you need a
global variable, you will declare it in a header, and define it in one
suitable source file, and that source file will include the header to
cross-check the declaration and definition, and all source files that
use the variable will use the header to declare it.

Corollary: you will not declare global variables in a source file — a
source file will only contain definitions.

Header files should seldom declare `static` functions, with the notable
exception of `static inline` functions which will be defined in headers
if the function is needed in more than one source file.


* Source files define global variables, and global functions.
* Source files do not declare the existence of global variables or functions; they include the header that declares the variable or function.
* Header files declare global variable and functions (and types and other supporting material).
* Header files do not define variables or any functions except (`static`) `inline` functions.


<hr>

# Cross-references

* [Where to document functions in C?](http://stackoverflow.com/questions/3568052)
* [List of standard header files in C and C++](http://stackoverflow.com/questions/2027991)
* [Is `inline` without `static` or `extern` ever useful in C99?](http://stackoverflow.com/questions/6312597)
* [How do I use `extern` to share variables between source files?](http://stackoverflow.com/questions/1433204)
* [What are the benefits of a relative path such as `"../include/header.h"` for a header?](http://stackoverflow.com/questions/597318)
* [Header inclusion optimization](http://stackoverflow.com/questions/1869439)
* [Should I include every header?](http://stackoverflow.com/questions/26611481)

