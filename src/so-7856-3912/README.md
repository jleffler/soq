### Stack Overflow Question 7856-3912

[SO 7856-3912](https://stackoverflow.com/q/78563912) &mdash;
Refactoring test sources

### Question

I have five test source files with these contents:

```c
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "acutest.h"

#include "../src/FileBuf.h"
#include "../src/readlines_fread.c"

void test_readlines_fread_success(void)
{
    /* The lines and line lengths are at most 1024 in sample1.txt. */
    char buf[1024];
    char *lines[1024];
    size_t line_count = 0;
    FILE *const fp = fopen("test/sample.txt", "r");

    TEST_ASSERT(fp);

    while (fgets(buf, sizeof buf, fp)) {
        buf[strcspn(buf, "\n")] = '\0';
        TEST_ASSERT((lines[line_count] = strdup(buf)));
        ++line_count;
    }

    rewind(fp);

    FileBuf fbuf = {};

    TEST_CHECK(readlines_fread(fp, &fbuf));
    TEST_CHECK(fbuf.count == 555);
    TEST_CHECK(fbuf.size == 120635);

    for (size_t i = 0; i < fbuf.count; ++i) {
        TEST_CHECK((strcmp(lines[i], fbuf.lines[i].line) == 0));
    }

    fclose(fp);
}

TEST_LIST = {
    { "test_readlines_fread_success", test_readlines_fread_success },
    { nullptr, nullptr },
};
```

The only difference between them is the last `include` directive is
different, the function name is different, the function being called in
the first `TEST_CHECK()` is different, and the first entry in the
`TEST_LIST` array is different.

Well, it is just one name in 5 different places, `fread` here.

The other 4 test files are the same, except that `fread` is replaced
with `getline`, `mmap_getline`, `mmap_memchr`, and `read` respectively.

I am looking to reduce these 5 test sources to a single one.  I am aware
that I can directly pass the header with the `-include` flag to GCC and
Clang, but how I similarly replace the function names (`fread`,
`getline`, `mmap_getline`, `mmap_memchr`, and `read`) with some
macro-trickery?

Say, when building for the first time, all instances of `fread` should
remain the same.  Then when building for the second time, all instance
of `fread` should be replaced with `getline`, and then `mmap_getline()`,
and so on.


### Answer

If you have a macro that expands to look like a header name, you can use:
```
#include INCLUDE_FILE_NAME
```
So, you could compile with `-DINCLUDE_FILE_NAME='"../src/readlines_fread.c"'`.

The line:
```
{ "test_readlines_fread_success", test_readlines_fread_success },
```
could be converted to use a macro:
```
{ FUNCTION_NAME_AND_POINTER(test_readlines_fread_success) },
```
with:
```
#define FUNCTION_NAME_AND_POINTER(name) #name, name
```
It isn't clear how the `TEST_LIST` array declaration is used — it
seems to combine a type with some sort of array name.  Frankly, it is
more obfuscatory than beneficial.  It would be better split into:
```
TEST_ARRAY_TYPE Test_Array_Name[] =
{
    …
};
```
However, in many ways, that particular observation is tangential, but my
test code will use that revised notation.


It isn't very clear in the question which names are "the function name".
There seem to be a lot of places with various things that could be "the
function name" embedded in them.  If the FUT (function under test) is
`readlines_fread`, then the build environment can do a fair amount of
the work for you.

Here is a version of your file with some macros which would presumably
be placed into a header, probably `acutest.h` for production use.  My
source is in `test97.c`.
```
/* SO 7856-3912 */

//#include <assert.h>
//#include <stdio.h>
//#include <string.h>
//#include "acutest.h"
//#include "FileBuf.h"

/* Check configuration */
#ifndef INCLUDE_FILE_NAME
#error You must define INCLUDE_FILE_NAME as the name of the source file to test
#endif /* INCLUDE_FILE_NAME */
#ifndef FUNCTION_UNDER_TEST
#error You must define FUNCTION_UNDER_TEST as the name of the function under test
#endif /* FUNCTION_UNDER_TEST */

#include INCLUDE_FILE_NAME

#define TEST_FUNCTION_NAME(name)    test_ ## name ## _success
#define TEST_FUNCTION(name)         TEST_FUNCTION_NAME(name)

#define TEST_ARRAY_ENTRY(name)      #name, name
#define TEST_ARRAY_EXPANSION(name)  TEST_ARRAY_ENTRY(name)
#define TEST_ARRAY_MAPPING(name)    TEST_ARRAY_EXPANSION(TEST_FUNCTION(name))


void TEST_FUNCTION(FUNCTION_UNDER_TEST)(void)
{
    /* The lines and line lengths are at most 1024 in sample1.txt. */
    char buf[1024];
    char *lines[1024];
    size_t line_count = 0;
    FILE *const fp = fopen("test/sample.txt", "r");

    TEST_ASSERT(fp);

    while (fgets(buf, sizeof buf, fp)) {
        buf[strcspn(buf, "\n")] = '\0';
        TEST_ASSERT((lines[line_count] = strdup(buf)));
        ++line_count;
    }

    rewind(fp);

    FileBuf fbuf = {};

    TEST_CHECK(FUNCTION_UNDER_TEST(fp, &fbuf));
    TEST_CHECK(fbuf.count == 555);
    TEST_CHECK(fbuf.size == 120635);

    for (size_t i = 0; i < fbuf.count; ++i) {
        TEST_CHECK((strcmp(lines[i], fbuf.lines[i].line) == 0));
    }

    fclose(fp);
}

TEST_ARRAY_TYPE Test_Array_Name[] = {
    { TEST_ARRAY_MAPPING(FUNCTION_UNDER_TEST) },
    { nullptr, nullptr },
};
```
I've commented out the headers, and tested with a file
`readlines_fread.c` in the current directory that contains just:
```
Contents of readlines_fread.c
```
The `makefile` looks like this:
```make
FUNCTION_UNDER_TEST = readlines_fread
INCLUDE_FILE_NAME = "$(FUNCTION_UNDER_TEST).c"

CFLAGS = -E -DINCLUDE_FILE_NAME='$(INCLUDE_FILE_NAME)' -DFUNCTION_UNDER_TEST=$(FUNCTION_UNDER_TEST)

PROG = test97

all: $(PROG).o
```
The preprocessed output looks like this:
```
# 1 "test97.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 418 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "test97.c" 2
# 17 "test97.c"
# 1 "./readlines_fread.c" 1
Content of file readlines_fread.c
# 18 "test97.c" 2
# 27 "test97.c"
void test_readlines_fread_success(void)
{

    char buf[1024];
    char *lines[1024];
    size_t line_count = 0;
    FILE *const fp = fopen("test/sample.txt", "r");

    TEST_ASSERT(fp);

    while (fgets(buf, sizeof buf, fp)) {
        buf[strcspn(buf, "\n")] = '\0';
        TEST_ASSERT((lines[line_count] = strdup(buf)));
        ++line_count;
    }

    rewind(fp);

    FileBuf fbuf = {};

    TEST_CHECK(readlines_fread(fp, &fbuf));
    TEST_CHECK(fbuf.count == 555);
    TEST_CHECK(fbuf.size == 120635);

    for (size_t i = 0; i < fbuf.count; ++i) {
        TEST_CHECK((strcmp(lines[i], fbuf.lines[i].line) == 0));
    }

    fclose(fp);
}

TEST_ARRAY_TYPE Test_Array_Name[] = {
    { "test_readlines_fread_success", test_readlines_fread_success },
    { nullptr, nullptr },
};
```
I believe that is very close to what you wanted to achieve.  By running
`make FUNCTION_UNDER_TEST=readlines_getline`, you can switch to a
different source file and function name.

Obviously, you can identify where files are to be included from with an
option like `-I../src` provided as one of the CFLAGS.

GNU Make copies the output into `test97.o` because it adds `-c` and `-o
test97.o` to the compiler command line:
```none
cc -E -DINCLUDE_FILE_NAME='"readlines_fread.c"' -DFUNCTION_UNDER_TEST=readlines_fread   -c -o test97.o test97.c
```
Other variants of `make` may have different rules.
```none
gcc -E -DINCLUDE_FILE_NAME='"readlines_fread.c"' -DFUNCTION_UNDER_TEST=readlines_fread -c test97.c
```

See also [What are the benefits of a relative path such as
`"../include/header.h"` for a
header?](https://stackoverflow.com/q/597318/15168)

<hr>

It is hard to generate header names enclosed in double quotes because
they look like strings, and that presents problems because strings have
their own set of semantics.

The `#include` notation shown in
[wizzwizz4](https://stackoverflow.com/users/5223757/wizzwizz4)'s
[answer](https://stackoverflow.com/a/78563943/15168) (revision 1) is not
going to work.  String concatenation occurs in Phase 6 (see C11
[§5.1.1.2 Translation
phases](https://port70.net/~nsz/c/c11/n1570.html#5.1.1.2)) while
preprocessing occurs in Phase 4.  You can use a macro name in `#include
MACRO_NAME`, but `MACRO_NAME` must expand to `"file.name"` or
`<file.name>` pretty much directly.  See also [§6.10.2 Source file
inclusion ¶4](https://port70.net/~nsz/c/c11/n1570.html#6.10.2p4) and
especially [footnote
170](https://port70.net/~nsz/c/c11/n1570.html#note170).

However, you could use the angle-bracket notation to good effect.

For example:
```
#define HEADER_NAME(base) <base.h>

#include HEADER_NAME(somename)
```
With the correct `-I` options (`-I.` for the case where `somename.h` is
in the current directory), this will include `somename.h` for you.
Clearly, you could adapt this to include a source file in another
directory, but you may still have to include appropriate `-I` options on
the command line:
```
#define SOURCE_FILE(base) <../src/base.c>

#include SOURCE_FILE(testfile)
```
Or (with `RELATIVE_PATH` more plausibly set on the command line):
```
#define RELATIVE_PATH ../src
#define HEADER_NAME(base) <RELATIVE_PATH/base.h>

#include HEADER_NAME(somename)
```
This works with GCC (aka Clang) on macOS, at any rate.

<hr>

What you need to use also depends on where you do the compilation.  Note
that the POSIX specification for the
[`c99`](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/c99.html)
compiler includes a specification of how `#include <name.h>` and
`#include "name.h"` interact with `-Isome/path/name`:

> _`-I  directory`_
>
> Change the algorithm for searching for headers whose names are not
> absolute pathnames to look in the directory named by the directory
> pathname before looking in the usual places.  Thus, headers whose
> names are enclosed in double-quotes (`""`) shall be searched for first
> in the directory of the file with the `#include` line, then in
> directories named in `-I` options, and last in the usual places.  For
> headers whose names are enclosed in angle brackets (`"<>"`), the
> header shall be searched for only in directories named in `-I` options
> and then in the usual places.  Directories named in `-I` options shall
> be searched in the order specified.  If the `-I` option is used to
> specify a directory that is one of the usual places searched by
> default, the results are unspecified.  Implementations shall support
> at least ten instances of this option in a single `c99` command
> invocation.

Note, in particular, the rule fragment:

> … shall be searched for first in the directory of the file with the `#include` line …

In a comment, you ask:

> And if the files are included with `"cread/src/FileBuf.h"`, what'd I need?

Then, in the `cread/test` directory, you'd need `-I../..`.  Or if the
project is in `/home/username/project/cread` (with sub-directories
`test` and `src`), you could use `-I$HOME/project` (in shell notation;
`-I$(HOME)/project` or `-I${HOME}/project` in `make` notation – and
the notation `-I${HOME}/project` would work in the makefile too).

Basically, the preprocessor is going to take the name in the `#include`
directive (e.g. `cread/src/fileBuf.h` and prepend items from the list of
`-I` options to create a file name.

So, with `-I../..`, you'd end up with `../../cread/src/fileBuf.h`, which
should be the pathname of the file relative to the `test` sub-directory.
Or with `-I${HOME}/project`, you'd have
`/home/username/project/cread/src/fileBuf.h`.

