## Standard C — Hosted Environment

For a hosted environment (that's the normal one), the C11 standard (ISO/IEC 9899:2011) says:

> ### 5.1.2.2.1 Program startup
>
> The function called at program startup is named `main`.  The
> implementation declares no prototype for this function.  It shall be
> defined with a return type of `int` and with no parameters:
>
>     int main(void) { /* ... */ }
>
> or with two parameters (referred to here as `argc` and `argv`, though
> any names may be used, as they are local to the function in which they
> are declared):
>
>     int main(int argc, char *argv[]) { /* ... */ }
>
> or equivalent;<sup>10)</sup> or in some other implementation-defined manner.
>
> If they are declared, the parameters to the main function shall obey
> the following constraints:
>
> - The value of `argc` shall be nonnegative.
> - `argv[argc]` shall be a null pointer.
> - If the value of `argc` is greater than zero, the array members
>   `argv[0]` through `argv[argc-1]` inclusive shall contain pointers to
>   strings, which are given implementation-defined values by the host
>   environment prior to program startup.  The intent is to supply to
>   the program information determined prior to program startup from
>   elsewhere in the hosted environment.  If the host environment is not
>   capable of supplying strings with letters in both uppercase and
>   lowercase, the implementation shall ensure that the strings are
>   received in lowercase.
> - If the value of `argc` is greater than zero, the string pointed to
>   by `argv[0]` represents the program name; `argv[0][0]` shall be the
>   null character if the program name is not available from the host
>   environment.  If the value of `argc` is greater than one, the
>   strings pointed to by `argv[1]` through `argv[argc-1]` represent the
>   program parameters.
> - The parameters `argc` and `argv` and the strings pointed to by the
>   `argv` array shall be modifiable by the program, and retain their
>   last-stored values between program startup and program termination.
>
> <sup>10)</sup> Thus, `int` can be replaced by a typedef name defined
> as `int`, or the type of `argv` can be written as `char **argv`, and so on.

### Program termination in C99 or C11

The value returned from `main()` is transmitted to the 'environment' in
an implementation-defined way.

> ### 5.1.2.2.3 Program termination
>1 If the return type of the `main` function is a type compatible with
>`int`, a return from the initial call to the `main` function is
>equivalent to calling the `exit` function with the value returned by
>the `main` function as its argument;<sup>11)</sup> reaching the `}`
>that terminates the `main` function returns a value of 0.  If the
>return type is not compatible with `int`, the termination status
>returned to the host environment is unspecified.
>
> <sup>11)</sup> In accordance with 6.2.4, the lifetimes of objects with
> automatic storage duration declared in `main` will have ended in the
> former case, even where they would not have in the latter.

Note that `0` is mandated as 'success'.  You can use `EXIT_FAILURE` and
`EXIT_SUCCESS` from `<stdlib.h>` if you prefer, but 0 is well
established, and so is 1.  See also [Exit codes greater than 255 —
possible?](https://stackoverflow.com/questions/179565/exitcodes-bigger-than-255-possible/).

In C89 (and hence in Microsoft C), there is no statement about what
happens if the `main()` function returns but does not specify a return
value; it therefore leads to undefined behaviour.

> ### 7.22.4.4 The `exit` function
>
> ¶5 Finally, control is returned to the host environment.  If the
> value of `status` is zero or `EXIT_SUCCESS`, an
> implementation-defined form of the status _successful termination_
> is returned.  If the value of `status` is `EXIT_FAILURE`, an
> implementation-defined form of the status _unsuccessful termination_
> is returned.  Otherwise the status returned is
> implementation-defined.

## Standard C++ — Hosted Environment

The C++11 standard (ISO/IEC 14882:2011) says:

> ### 3.6.1 Main function [basic.start.main]
> ¶1 A program shall contain a global function called main, which is
> the designated start of the program. [...]
>
> ¶2 An implementation shall not predefine the main function.  This
> function shall not be overloaded.  It shall have a return type of
> type int, but otherwise its type is implementation defined.  All
> implementations shall allow both of the following definitions of
> main:
>
>     int main() { /* ... */ }
>
> and
>
>     int main(int argc, char* argv[]) { /* ... */ }
>
> In the latter form `argc` shall be the number of arguments passed to
> the program from the environment in which the program is run.  If
> `argc` is nonzero these arguments shall be supplied in `argv[0]`
> through `argv[argc-1]` as pointers to the initial characters of
> null-terminated multibyte strings (NTMBSs) (17.5.2.1.4.2) and
> `argv[0]` shall be the pointer to the initial character of a NTMBS
> that represents the name used to invoke the program or `""`.  The
> value of `argc` shall be non-negative.  The value of `argv[argc]`
> shall be 0.  [Note: It is recommended that any further (optional)
> parameters be added after `argv`. —end note]
>
> ¶3 The function `main` shall not be used within a program.  The
> linkage (3.5) of `main` is implementation-defined. [...]
>
> ¶5 A return statement in main has the effect of leaving the main
> function (destroying any objects with automatic storage duration) and
> calling `std::exit` with the return value as the argument.  If control
> reaches the end of main without encountering a return statement, the
> effect is that of executing
>
>     return 0;

The C++ standard explicitly says "It [the main function] shall have a
return type of type `int`, but otherwise its type is implementation
defined", and requires the same two signatures as the C standard to be
supported as options.  So a 'void main()' is directly not allowed by the
C++ standard, though there's nothing it can do to stop a non-standard
implementation allowing alternatives.  Note that C++ forbids the user
from calling `main` (but the C standard does not).

There's a paragraph of §18.5 **Start and termination** in the C++11
standard that is identical to the paragraph from §7.22.4.4 **The `exit`
function** in the C11 standard (quoted above), apart from a footnote
(which simply documents that `EXIT_SUCCESS` and `EXIT_FAILURE` are
defined in `<cstdlib>`).

## Standard C — Common Extension

Classically, Unix systems support a third variant:

    int main(int argc, char **argv, char **envp) { ... }

The third argument is a null-terminated list of pointers to strings,
each of which is an environment variable which has a name, an equals
sign, and a value (possibly empty).  If you do not use this, you can
still get at the environment via '`extern char **environ;`'.  This
global variable is unique among those in POSIX in that it does not have
a header that declares it.

This is recognized by the C standard as a common extension, documented
in Annex J:

> ###J.5.1 Environment arguments
>
> ¶1 In a hosted environment, the main function receives a third
> argument, `char *envp[]`, that points to a null-terminated array of
> pointers to `char`, each of which points to a string that provides
> information about the environment for this execution of the program
> (5.1.2.2.1).

## Microsoft C

The [Microsoft VS 2010][2] compiler is interesting. The web site says:

> The declaration syntax for main is
>
>      int main();
>
> or, optionally,
>
>     int main(int argc, char *argv[], char *envp[]);
>
> Alternatively, the `main` and `wmain` functions can be declared as
> returning `void` (no return value).  If you declare `main` or `wmain`
> as returning void, you cannot return an exit code to the parent
> process or operating system by using a return statement.  To return an
> exit code when `main` or `wmain` is declared as `void`, you must use
> the `exit` function.

It is not clear to me what happens (what exit code is returned to the
parent or OS) when a program with `void main()` does exit — and the MS
web site is silent too.

Interestingly, MS does not prescribe the two-argument version of
`main()` that the C and C++ standards require.  It only prescribes a
three argument form where the third argument is `char **envp`, a pointer
to a list of environment variables.

The Microsoft page also lists some other alternatives — `wmain()`
which takes wide character strings, and some more.

The Microsoft [Visual&nbsp;Studio&nbsp;2005][3] version of [this
page][4] does not list `void main()` as an alternative.  The
[versions][5] from Microsoft [Visual&nbsp;Studio&nbsp;2008][6] onwards
do.

## Standard C — Freestanding Environment

As noted early on, the requirements above apply to hosted environments.
If you are working with a freestanding environment (which is the
alternative to a hosted environment), then the standard has much less to
say.  For a freestanding environment, the function called at program
startup need not be called `main` and there are no constraints on its
return type.  The standard says:

> ### 5.1.2 Execution environments
>
>Two execution environments are defined: freestanding and hosted.  In
>both cases, program startup occurs when a designated C function is
>called by the execution environment.  All objects with static storage
>duration shall be initialized (set to their initial values) before
>program startup.  The manner and timing of such initialization are
>otherwise unspecified.  Program termination returns control to the
>execution environment.
>
> ### 5.1.2.1 Freestanding environment
> In a freestanding environment (in which C program execution may take
> place without any benefit of an operating system), the name and type
> of the function called at program startup are implementation-defined.
> Any library facilities available to a freestanding program, other than
> the minimal set required by clause 4, are implementation-defined.
>
> The effect of program termination in a freestanding environment is
> implementation-defined.

The cross-reference to clause 4 Conformance refers to this:

> ¶5 A _strictly conforming program_ shall use only those features of
> the language and library specified in this International
> Standard.<sup>3)</sup> It shall not produce output dependent on any
> unspecified, undefined, or implementation-defined behavior, and
> shall not exceed any minimum implementation limit.
>
> ¶6 The two forms of conforming implementation are _hosted_ and
> _freestanding_.  A _conforming hosted implementation_ shall accept
> any strictly conforming program.  A _conforming freestanding
> implementation_ shall accept any strictly conforming program in
> which the use of the features specified in the library clause
> (clause 7) is confined to the contents of the standard headers
> `<float.h>`, `<iso646.h>`, `<limits.h>`, `<stdalign.h>`,
> `<stdarg.h>`, `<stdbool.h>`, `<stddef.h>`, `<stdint.h>`, and
> `<stdnoreturn.h>`.  A conforming implementation may have extensions
> (including additional library functions), provided they do not alter
> the behavior of any strictly conforming program.<sup>4)</sup>
>
> ¶7 A _conforming program_ is one that is acceptable to a conforming
> implementation.<sup>5)</sup>
>
> <sup>3)</sup> A strictly conforming program can use conditional
> features (see 6.10.8.3) provided the use is guarded by an appropriate
> conditional inclusion preprocessing directive using the related macro.
> For example:
>
>     #ifdef __STDC_IEC_559__ /* FE_UPWARD defined */
>         /* ... */
>         fesetround(FE_UPWARD);
>         /* ... */
>     #endif
>
> <sup>4)</sup> This implies that a conforming implementation reserves
> no identifiers other than those explicitly reserved in this
> International Standard.
>
> <sup>5)</sup> Strictly conforming programs are intended to be
> maximally portable among conforming implementations.  Conforming
> programs may depend upon non-portable features of a conforming
> implementation.

It is noticeable that the only header required of a freestanding
environment that actually defines any functions is `<stdarg.h>` (and
even those may be — and often are — just macros).

## Standard C++ — Freestanding Environment

Just as the C standard recognizes both hosted and freestanding
environment, so too does the C++ standard.  (Quotes from ISO/IEC
14882:2011.)

> ### 1.4 Implementation compliance [intro.compliance]
>
> ¶7 Two kinds of implementations are defined: a _hosted
> implementation_ and a _freestanding implementation_.  For a hosted
> implementation, this International Standard defines the set of
> available libraries.  A freestanding implementation is one in which
> execution may take place without the benefit of an operating system,
> and has an implementation-defined set of libraries that includes
> certain language-support libraries (17.6.1.3).
>
> ¶8 A conforming implementation may have extensions (including
> additional library functions), provided they do not alter the
> behavior of any well-formed program.  Implementations are required
> to diagnose programs that use such extensions that are ill-formed
> according to this International Standard.  Having done so, however,
> they can compile and execute such programs.
>
> ¶9 Each implementation shall include documentation that identifies
> all conditionally-supported constructs that it does not support and
> defines all locale-specific characteristics.<sup>3</sup>
>
><sup>3)</sup> This documentation also defines implementation-defined
>behavior; see 1.9.
>
> ### 17.6.1.3 Freestanding implementations [compliance]
>
> Two kinds of implementations are defined: hosted and freestanding
> (1.4).  For a hosted implementation, this International Standard
> describes the set of available headers.
>
> A freestanding implementation has an implementation-defined set of
> headers.  This set shall include at least the headers shown in Table
> 16.
>
> The supplied version of the header `<cstdlib>` shall declare at least
> the functions `abort`, `atexit`, `at_quick_exit`, `exit`, and
> `quick_exit` (18.5).  The other headers listed in this table shall
> meet the same requirements as for a hosted implementation.

**Table 16 — C++ headers for freestanding implementations**

| Subclause                       | Header(s)
|:--------------------------------|:---------------------------------------|
|                                 | `<ciso646>`                            |
| 18.2  Types                     | `<cstddef>`                            |
| 18.3  Implementation properties | `<cfloat>` `<limits>` `<climits>`      |
| 18.4  Integer types             | `<cstdint>`                            |
| 18.5  Start and termination     | `<cstdlib>`                            |
| 18.6  Dynamic memory management | `<new>`                                |
| 18.7  Type identification       | `<typeinfo>`                           |
| 18.8  Exception handling        | `<exception>`                          |
| 18.9  Initializer lists         | `<initializer_list>`                   |
| 18.10 Other runtime support     | `<cstdalign>` `<cstdarg>` `<cstdbool>` |
| 20.9  Type traits               | `<type_traits>`                        |
| 29    Atomics                   | `<atomic>`                             |



  [1]: http://en.wikipedia.org/wiki/POSIX
  [2]: http://msdn.microsoft.com/en-us/library/6wd819wh%28v=vs.100%29.aspx
  [3]: http://en.wikipedia.org/wiki/Microsoft_Visual_Studio#Visual_Studio_2005
  [4]: http://msdn.microsoft.com/en-us/library/6wd819wh%28v=vs.80%29.aspx
  [5]: http://msdn.microsoft.com/en-us/library/6wd819wh%28v=vs.90%29.aspx
  [6]: http://en.wikipedia.org/wiki/Microsoft_Visual_Studio#Visual_Studio_2008

## What about using `int main()` in C?

The standard §5.1.2.2.1 of the C11 standard shows the preferred
notation — `int main(void)` — but there are also two examples in
the standard which show `int main()`: [§6.5.3.4
¶8](https://port70.net/~nsz/c/c11/n1570.html#6.5.3.4p8) and [§6.7.6.3
¶20](https://port70.net/~nsz/c/c11/n1570.html#6.7.6.3p20).  Now, it is
important to note that examples are not 'normative'; they are only
illustrative.  If there are bugs in the examples, they do not directly
affect the main text of the standard.  That said, they are strongly
indicative of expected behaviour, so if the standard includes `int
main()` in an example, it suggests that `int main()` is not forbidden,
even if it is not the preferred notation.

> ### 6.5.3.4 The `sizeof` and `_Alignof` operators
>
> …
>
> ¶8 EXAMPLE 3 In this example, the size of a variable length array is
> computed and returned from a function:
>
>     #include <stddef.h>
>    
>     size_t fsize3(int n)
>     {
>         char b[n+3]; // variable length array
>         return sizeof b; // execution time sizeof
>     }
>     int main()
>     {
>         size_t size;
>         size = fsize3(10); // fsize3 returns 13
>         return 0;
>     }

A function definition like `int main(){ … }` does specify that the
function takes no arguments, but does not provide a function prototype,
AFAICT.  For `main()` that is seldom a problem; but it does mean that if
you have recursive calls to `main()`, the arguments won't be checked.
For other functions, it is more of a problem — you really need a
prototype in scope when the function is called to ensure that the
arguments are correct.

You don't normally call `main()` recursively, outside of places like
IOCCC — and you are explicitly forbidden from doing so in C++.  I do
have a test program that does it — mainly for novelty.  If you have:

```
int i = 0;
int main()
{
    if (i++ < 10)
        main(i, i * i);
    return 0;
}
```
and compile with GCC and don't include `-Wstrict-prototypes`, it
compiles cleanly under stringent warnings.  If it's `main(void)`, it
fails to compile because the function definition says "no arguments".

