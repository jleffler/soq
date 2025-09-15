### If you use a C99 or later compiler

    #define debug_print(fmt, ...) \
                do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

It assumes you are using C99 (the variable argument list notation is not
supported in earlier versions).  The `do { ... } while (0)` idiom
ensures that the code acts like a statement (function call).  The
unconditional use of the code ensures that the compiler always checks
that your debug code is valid &mdash; but the optimizer will remove the
code when DEBUG is 0.

If you want to work with #ifdef DEBUG, then change the test condition:

    #ifdef DEBUG
    #define DEBUG_TEST 1
    #else
    #define DEBUG_TEST 0
    #endif

And then use DEBUG_TEST where I used DEBUG.

If you insist on a string literal for the format string (probably a good
idea anyway), you can also introduce things like `__FILE__`, `__LINE__`
and `__func__` into the output, which can improve the diagnostics:

    #define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                    __LINE__, __func__, __VA_ARGS__); } while (0)

This relies on string concatenation to create a bigger format string
than the programmer writes.

### If you use a C89 compiler

If you are stuck with C89 and no useful compiler extension, then there
isn't a particularly clean way to handle it.  The technique I used to
use was:

    #define TRACE(x) do { if (DEBUG) dbg_printf x; } while (0)

And then, in the code, write:

    TRACE(("message %d\n", var));

The double-parentheses are crucial &mdash; and are why you have the
funny notation in the macro expansion.  As before, the compiler always
checks the code for syntactic validity (which is good) but the optimizer
only invokes the printing function if the DEBUG macro evaluates to
non-zero.

This does require a support function &mdash; dbg_printf() in the example
&mdash; to handle things like 'stderr'.  It requires you to know how to
write varargs functions, but that isn't hard:

    #include <stdarg.h>
    #include <stdio.h>

    void dbg_printf(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }

You can also use this technique in C99, of course, but the `__VA_ARGS__`
technique is neater because it uses regular function notation, not the
double-parentheses hack.

### Why is it crucial that the compiler always see the debug code?

[_Rehashing comments made to another answer._]

One central idea behind both the C99 and C89 implementations above is
that the compiler proper always sees the debugging printf-like
statements.  This is important for long-term code &mdash; code that will
last a decade or two.

Suppose a piece of code has been mostly dormant (stable) for a number of
years, but now needs to be changed.  You re-enable debugging trace - but
it is frustrating to have to debug the debugging (tracing) code because
it refers to variables that have been renamed or retyped, during the
years of stable maintenance.  If the compiler (post pre-processor)
always sees the print statement, it ensures that any surrounding changes
have not invalidated the diagnostics.  If the compiler does not see the
print statement, it cannot protect you against your own carelessness (or
the carelessness of your colleagues or collaborators).
See '[The Practice of Programming][1]' by Kernighan and Pike, especially Chapter 8
(see also Wikipedia on
[TPOP](https://en.wikipedia.org/wiki/The_Practice_of_Programming#External_links)).

This is 'been there, done that' experience &mdash; I used essentially
the technique described in other answers where the non-debug build does
not see the printf-like statements for a number of years (more than a
decade).  But I came across the advice in TPOP (see my previous
comment), and then did enable some debugging code after a number of
years, and ran into problems of changed context breaking the debugging.
Several times, having the printing always validated has saved me from
later problems.

I use NDEBUG to control assertions only, and a separate macro (usually
DEBUG) to control whether debug tracing is built into the program.  Even
when the debug tracing is built in, I frequently do not want debug
output to appear unconditionally, so I have mechanism to control whether
the output appears (debug levels, and instead of calling `fprintf()`
directly, I call a debug print function that only conditionally prints
so the same build of the code can print or not print based on program
options).  I also have a 'multiple-subsystem' version of the code for
bigger programs, so that I can have different sections of the program
producing different amounts of trace - under runtime control.

I am advocating that for all builds, the compiler should see the
diagnostic statements; however, the compiler won't generate any code for
the debugging trace statements unless debug is enabled.  Basically, it
means that all of your code is checked by the compiler every time you
compile - whether for release or debugging.  This is a good thing!

### debug.h - version 1.2 (1990-05-01)

    /*
    @(#)File:            $RCSfile: debug.h,v $
    @(#)Version:         $Revision: 1.2 $
    @(#)Last changed:    $Date: 1990/05/01 12:55:39 $
    @(#)Purpose:         Definitions for the debugging system
    @(#)Author:          J Leffler
    */
    
    #ifndef DEBUG_H
    #define DEBUG_H
    
    /* -- Macro Definitions	*/
    
    #ifdef DEBUG
    #define TRACE(x)	db_print x
    #else
    #define TRACE(x)
    #endif /* DEBUG */
    
    /* -- Declarations */
    
    #ifdef DEBUG
    extern	int		debug;
    #endif
    
    #endif	/* DEBUG_H */

### debug.h - version 3.6 (2008-02-11)

    /*
    @(#)File:           $RCSfile: debug.h,v $
    @(#)Version:        $Revision: 3.6 $
    @(#)Last changed:   $Date: 2008/02/11 06:46:37 $
    @(#)Purpose:        Definitions for the debugging system
    @(#)Author:         J Leffler
    @(#)Copyright:      (C) JLSS 1990-93,1997-99,2003,2005,2008
    @(#)Product:        :PRODUCT:
    */
    
    #ifndef DEBUG_H
    #define DEBUG_H
    
    #ifdef HAVE_CONFIG_H
    #include "config.h"
    #endif /* HAVE_CONFIG_H */
    
    /*
    ** Usage:  TRACE((level, fmt, ...))
    ** "level" is the debugging level which must be operational for the output
    ** to appear. "fmt" is a printf format string. "..." is whatever extra
    ** arguments fmt requires (possibly nothing).
    ** The non-debug macro means that the code is validated but never called.
    ** -- See chapter 8 of 'The Practice of Programming', by Kernighan and Pike.
    */
    #ifdef DEBUG
    #define TRACE(x)    db_print x
    #else
    #define TRACE(x)    do { if (0) db_print x; } while (0)
    #endif /* DEBUG */
    
    #ifndef lint
    #ifdef DEBUG
    /* This string can't be made extern - multiple definition in general */
    static const char jlss_id_debug_enabled[] = "@(#)*** DEBUG ***";
    #endif /* DEBUG */
    #ifdef MAIN_PROGRAM
    const char jlss_id_debug_h[] = "@(#)$Id: debug.h,v 3.6 2008/02/11 06:46:37 jleffler Exp $";
    #endif /* MAIN_PROGRAM */
    #endif /* lint */
    
    #include <stdio.h>
    
    extern int      db_getdebug(void);
    extern int      db_newindent(void);
    extern int      db_oldindent(void);
    extern int      db_setdebug(int level);
    extern int      db_setindent(int i);
    extern void     db_print(int level, const char *fmt,...);
    extern void     db_setfilename(const char *fn);
    extern void     db_setfileptr(FILE *fp);
    extern FILE    *db_getfileptr(void);
    
    /* Semi-private function */
    extern const char *db_indent(void);
    
    /**************************************\
    ** MULTIPLE DEBUGGING SUBSYSTEMS CODE **
    \**************************************/
    
    /*
    ** Usage:  MDTRACE((subsys, level, fmt, ...))
    ** "subsys" is the debugging system to which this statement belongs.
    ** The significance of the subsystems is determined by the programmer,
    ** except that the functions such as db_print refer to subsystem 0.
    ** "level" is the debugging level which must be operational for the
    ** output to appear. "fmt" is a printf format string. "..." is
    ** whatever extra arguments fmt requires (possibly nothing).
    ** The non-debug macro means that the code is validated but never called.
    */
    #ifdef DEBUG
    #define MDTRACE(x)  db_mdprint x
    #else
    #define MDTRACE(x)  do { if (0) db_mdprint x; } while (0)
    #endif /* DEBUG */
    
    extern int      db_mdgetdebug(int subsys);
    extern int      db_mdparsearg(char *arg);
    extern int      db_mdsetdebug(int subsys, int level);
    extern void     db_mdprint(int subsys, int level, const char *fmt,...);
    extern void     db_mdsubsysnames(char const * const *names);
    
    #endif /* DEBUG_H */

### Single argument variant for C99 or later

Kyle Brandt asked:

> Anyway to do this so `debug_print` still works even if there are no
> arguments?  For example:
>
>         debug_print("Foo");

There's one simple, old-fashioned hack:

    debug_print("%s\n", "Foo");

The GCC-only solution shown below also provides support for that.

However, you can do it with the straight C99 system by using:

    #define debug_print(...) \
                do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

Compared to the first version, you lose the limited checking that
requires the 'fmt' argument, which means that someone could try to call
'debug_print()' with no arguments (but the trailing comma in the
argument list to `fprintf()` would fail to compile).  Whether the loss
of checking is a problem at all is debatable.

### GCC-specific technique for a single argument

Some compilers may offer extensions for other ways of handling
variable-length argument lists in macros.  Specifically, as first noted
in the comments by [Hugo Ideler][2], GCC allows you to omit the comma
that would normally appear after the last 'fixed' argument to the macro.
It also allows you to use [`##__VA_ARGS__`][3] in the macro replacement
text, which deletes the comma preceding the notation if, but only if,
the previous token is a comma:

    #define debug_print(fmt, ...) \
                do { if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

This solution retains the benefit of requiring the format argument while
accepting optional arguments after the format.

This technique is also supported by [Clang](https://clang.llvm.org/) for
GCC compatibility.

<hr>

### C23 and `__VA_OPT__`

Both C++20 (and later) and C23 (and later) add the `__VA_OPT__`
mechanism to handle the problem with `__VA_ARGS__` that is handled by
GCC using the `, ## __VA_ARGS__` notation.

You simply use:
```c
#define debug_print(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, fmt, __VA_OPT__(,) __VA_ARGS__); } while (0)
```
The argument to `__VA_OPT__` is added to the output if `__VA_ARGS__` is
not empty (and nothing is added if `__VA_ARGS__` is empty).  This should
be available if `__STDC_VERSION__ >= 202311L` — but be aware that GCC
14.1.0 (still) sets `__STDC_VERSION__ == 202000` when compiling with
`-std=c23` or `-std=iso9899:2024`.

<hr>

### Why the do-while loop?

> What's the purpose of the `do while` here?

You want to be able to use the macro so it looks like a function call,
which means it will be followed by a semi-colon.  Therefore, you have to
package the macro body to suit.  If you use an `if` statement without
the surrounding `do { ... } while (0)`, you will have:

    /* BAD - BAD - BAD */
    #define debug_print(...) \
                if (DEBUG) fprintf(stderr, __VA_ARGS__)

Now, suppose you write:

    if (x > y)
        debug_print("x (%d) > y (%d)\n", x, y);
    else
        do_something_useful(x, y);

Unfortunately, that indentation doesn't reflect the actual control of
flow, because the preprocessor produces code equivalent to this
(indented and braces added to emphasize the actual meaning):

    if (x > y)
    {
        if (DEBUG)
            fprintf(stderr, "x (%d) > y (%d)\n", x, y);
        else
            do_something_useful(x, y);
    }

The next attempt at the macro might be:

    /* BAD - BAD - BAD */
    #define debug_print(...) \
                if (DEBUG) { fprintf(stderr, __VA_ARGS__); }

And the same code fragment now produces:

    if (x > y)
        if (DEBUG)
        {
            fprintf(stderr, "x (%d) > y (%d)\n", x, y);
        }
    ; // Null statement from semi-colon after macro
    else
        do_something_useful(x, y);

And the `else` is now a syntax error.  The `do { ... } while(0)` loop
avoids both these problems.

There's one other way of writing the macro which might work:

    /* BAD - BAD - BAD */
    #define debug_print(...) \
                ((void)((DEBUG) ? fprintf(stderr, __VA_ARGS__) : 0))

This leaves the program fragment shown as valid.  The `(void)` cast
prevents it being used in contexts where a value is required &mdash; but
it could be used as the left operand of a comma operator where the `do {
... } while (0)` version cannot.  If you think you should be able to
embed debug code into such expressions, you might prefer this.  If you
prefer to require the debug print to act as a full statement, then the
`do { ... } while (0)` version is better.  Note that if the body of the
macro involved any semi-colons (roughly speaking), then you can only use
the `do { ... } while(0)` notation.  It always works; the expression
statement mechanism can be more difficult to apply.  You might also get
warnings from the compiler with the expression form that you'd prefer to
avoid; it will depend on the compiler and the flags you use.

  [1]: http://www.cs.princeton.edu/~bwk/tpop.webpage/
  [2]: https://stackoverflow.com/users/558647/hugo-ideler
  [3]: http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html

<hr>

<sup>
_TPOP was previously at http://plan9.bell-labs.com/cm/cs/tpop and
http://cm.bell-labs.com/cm/cs/tpop but both are now (2015-08-10)
broken._
</sup>

<hr>

### Code in GitHub

If you're curious, you can look at this code in GitHub in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository as files `debug.c`, `debug.h`, `mddebug.c` and `mddebug.h` in
the [src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.

