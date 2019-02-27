# What does an undefined reference or unresolved symbol error mean in C and how do I fix it?

<!--

If you add a new answer distinct from any of the existing answers,
please use one of the existing answers as a template.

Answers should contain links to original questions covering the same
topic when possible.
Those links should be in the modern [displayed
text](https://example.com/whatever) URL notation because it keeps the
URL together with the title, which is much more maintainable.
The links to questions can be terse: [SO
1234-5678](https://stackoverflow.com/q/12345678) is sufficient to give a
link.
The answer here should supersede the linked questions, but linking to
the original may help someone.

-->

One of the commonly occurring problems for newcomers to C is that they
try to link a program and encounter some 'undefined reference' or
'unresolved external symbol' errors, and they are not sure how to
resolve them.

There are two primary forms in which the problem appears:

1. Missing library on the linker command line.
2. Missing object files on the linker command line.

There are multiple subsidiary problems, including:

* Raw misspellings.
* Expecting a header to specify the library somehow.
* Basic makefiles.

Sometimes, the problem is in part that the OP does not sufficiently
understand the separation between compiling and linking, which is a
particularly easy mistake to make while compiling single source files
into a program, as beginners are wont to do.

Note that there is a similar question for C++:

* [What is an undefined reference/unresolved external symbol error and
   how do I fix it?](https://stackoverflow.com/questions/12573816)

Much, but not all, of the information in that question also applies when
linking C code.

### Missing library on the linker command line

The archetypal form of this question is:

* I included `#include <header.h>` from some library but when I link the
  program, I get messages about 'undefined' functions declared in the header, such as:

        $ gcc -o sets sets.o
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

        $ gcc -o sets sets.o
        sets.o: In function `main':
        .../so-3109-6894/sets.c:184: undefined reference to `err_setarg0'
        sets.o: In function `test_set':
        .../so-3109-6894/sets.c:176: undefined reference to `err_syserr'
        collect2: error: ld returned 1 exit status
        $

  How do I fix the linker command line so that my program links the
  library?

### Missing object files on the linker command line

The archetypal form of this question is:

* I have created a source file `util.c` containing function
  `utility_func()` and a header file `util.h` which declares it, and my
  main program in `main.c` contains `#include "util.h"`.
  But, when I link the program, the function shows up as missing.

  How do I fix the linker command line so that my program links the
  utility function too?

### Raw misspellings

The archetypal form of this question is:

* I have a program that calls `loadDynamicBNSFeature()` from `-lbsn`,
  but I'm getting an error when I link the program that
  `loadDynamicBNSFeature` is undefined.

  In this case, the library name is `libbsn.so` (or `libbsn.a` or
  `libbsn.dll` or whatever), and the function name should be
  `loadDynamicBSNFeature()` — the `SN` has been transposed to `NS`.
  All the other functions use BSN rather than BNS.

In this case, there is nothing to except point out the typo and vote to
close the question as 'Off Topic' with the subreason 'trivial typo'.


<!--

And also:

* Create your own library — static library.
* Create your own library - shared library.
* Use your own library to build your executable.
* Use libtool to create your own library.
* Using weak references.
* Using dynamically loaded libraries.
* Making dynamically loaded libraries call functions in your executable.
* Configuration and pre-requisite libraries or modules.
* Mixing C and C++ linking.

and the list can grow semi-indefinitely.
Note that the actions for building libraries may vary between Windows
and other systems, but using `libtool` alters the cognitive load
required.
It implies a use of the most of the 'Auto Tools' tool chain, which isn't
acceptable to everyone for valid reasons.
It means the answers are likely to be long-winded.

At some point, we'll need to take a view on what is and is not
appropriate.
At the moment, we'll keep things as simple as possible (but, to
paraphrase a quote attributed to Einstein, no simpler).

-->


>! Stack Overflow spoiler — does it work the same in GitHub Markdown?  
>!  
>! There is hidden information in the question text that you can see if
>! you 'edit' the question (or the `.md` file) — please read it before
>! adding an answer, but don't change it.
