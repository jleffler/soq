# Minimality

Headers are a crucial consistency checking mechanism, but they should be
as small as possible.
In particular, that means that a header should not include other headers
just because the implementation file will need the other headers.
A header should contain only those headers necessary for a consumer of
the services described.

For example, a project header should not include `<stdio.h>` unless one
of the function interfaces uses the type `FILE *` (or one of the other
types defined solely in `<stdio.h>`).
If an interface uses `size_t`, the smallest header that suffices is
`<stddef.h>`.
Obviously, if another header that defines `size_t` is included, there is
no need to include `<stddef.h>` too.

If the headers are minimal, then it keeps the compilation time to a
minimum too.

It is possible to devise headers whose sole purpose is to include a lot
of other headers.
These seldom turn out to be a good idea in the long run because few
source files will actually need all the facilities described by all the
headers.
For example, a `<standard-c.h>` could be devised that includes all the
standard C headers &mdash; with care since some headers are not always
present.
However, very few programs actually use the facilities of `<locale.h>`
or `<tgmath.h>`.

* See also [How to link multiple implementation files in
  C?](http://stackoverflow.com/questions/15622409)

