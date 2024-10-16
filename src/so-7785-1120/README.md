### Stack Overflow Question 7785-1120

[SO 7785-1120](https://stackoverflow.com/q/77851120/) &mdash;
Are you allowed to have `fork()` as a `for` condition?

Question asked: 2024-01-20T13:01:22Z


This question was on last year's exam and I have never seen anything
like this in my life.  I know what fork does, what it returns, but
this...  I can't even compile this.

What is displayed when running the C code below?  How many processes
appeared in total (including the initial process)?  Sketch the tree of
these processes, indicating next to each process that displayed
something the displayed value (in parentheses).  Justify the answers.

```c
int x=0;
for(fork();!fork();exit(x))
    for(!fork();exit(x);fork())
        for(exit(x);fork();!fork());

printf("%d\n",++x);
```c

[Answer](https://stackoverflow.com/a/77851642)
Answer given: 2024-01-20T14:47:45Z

The answer to the headline question — are you allowed to have
`fork()` as a `for` condition? — is "yes" because it is a function
that returns an `int`.

The answer to the unasked question — are you allowed to have `exit(x)`
as a `for` condition? — is unclear, but using the standard C header
`<stdlib.h>` to declare `exit()` means that the answer is "no" because
`exit()` does not return at all, and is declared not to return a value
(nominally, it returns `void`).

The code shown doesn't list the headers included.  If it includes
`<stdlib.h>` to declare the standard C function `exit()`, the code won't
compile.  If it doesn't include the header `<stdlib.h>`, the code can
only be compiled without warnings under C89/C90 rules where undeclared
functions are assumed to return an `int` value.

_Nomenclature_: For the purposes of this answer, the three components of
the `for` loop condition are `expression-1`, `expression-2` and
`expression-3`.  The initial process is designated P0 — child
processes are designated P1, P2, …

So, working under the assumption that `exit()` and `fork()` are both
inferred to return `int` (and `printf()` likewise, though using a
varargs function like `printf()` without a function prototype in scope
leads to undefined behaviour), and that `exit()` behaves like the
standard C `exit()` and terminates the process, and that `fork()`
creates a new process, returning zero in the child process and non-zero
in the parent process, we can make multiple observations.

* The only value that can be printed is `1`, but that is only printed if
  any of the myriad processes executes the `printf()`.
* In the second loop — `for(!fork();exit(x);fork())` — the `!`
  operator is irrelevant; the value returned by that `fork()` is never
  examined.
* Similarly, in the third loop — `for(exit(x);fork();!fork())` —
  the `!` operator is irrelevant.
* The first loop evaluates its `expression-1` which results in two
  processes running, P0 and P1.  Both processes run the first loop's
  `expression-2`, forking again, so there are now 4 processes, P0, P1,
  P2 (child of P0) and P3 (child of P1).
* For P2, the result of `!fork()` is 1 so it executes the loop body and
  similarly for P3; for processes P0 and P1, the result of `!fork()` is
  0 so the loop terminates; each of P0 and P1 executes the `printf()`
  statement and exits.
* For processes P2 and P3, IF the loop body (loops 2 and 3) terminate
  ordinarily, the corresponding `expression-3` will be evaluated and the
  process will exit without printing anything.  Note that it is a
  big"if"!
* There is nothing except their PID and PPID values to distinguish P2
  and P3; the argument for one applies equally to the other.
* When P2 executes loop 2, the `expression-1` creates a new process P4.
* Both P2 and P4 evaluate the condition, which causes the process to
  exit with status 0 (success).  The body of loop 2 (which is loop 3)
  and the `expression-3` are not executed, so further analysis of loop 3
  is unnecessary.

So, there were a total of 6 processes — P0..P5 (P5 being the child of P3).

The output is two lines containing `1` — probably.  The interleaving
of the results is not determinate.  There will be two `1`'s and two
newlines in the output; the first character will be a `1`; the last
character will be a newline.  In theory, the middle two characters could
appear in either order, but two neat lines is the most likely output.

Consider the code below code, which is a minor variant of the original.
However, it compiles cleanly under C11, C18, etc without complaints from
Clang (`Apple clang version 15.0.0 (clang-1500.1.0.2.5)`) set fussy:
```none
clang -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes \
      -Wstrict-prototypes fork17.c -o fork17
```
The code should compile without warnings using these options.
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#undef exit

/* This could (should?) include _Noreturn in the definition because it doesn't return */
static int terminate(int x)
{
    exit(x);
    return x;
}

#define exit(x) terminate(x)

static void notification(void)
{
    printf("PID = %d\n", getpid());
}

int main(void)
{
    atexit(notification);
    int x = 0;
    for (fork(); !fork(); exit(x))
        for (fork(); exit(x); fork())
            for (exit(x); fork(); fork())
                ;

    printf("%d\n", ++x);
    return 0;
}
```
The dance with `#undef exit` undoes any macro definition of `exit()` but
leaves the function declaration in place.  The function `terminate()` is
defined to return an integer value, but calls the real function `exit()`
which terminates the process before the return occurs.  The `#define
exit(x) terminate(x)` means that the calls to `exit()` in the `main()`
function actually call `terminate()` instead, but the result is the same
as if `exit()` were called except that it ensures no undefined
behaviour.

The `notification()` function is a simple function called when a process
exits normally — it identifies which process is exiting, giving a way
to check on the number of processes created by the program.

I've added an appropriate top and tail for function `main()` and called
`atexit(notification);` to get notified when processes exit.  I removed
the irrelevant `!` operators from the second and third loop controls —
`clang` complained that the expression result was unused.

One example run produced:
```none
1
PID = 31569
1
PID = 31570
PID = 31571
PID = 31572
PID = 31573
PID = 31574
```
This confirms that 6 processes were created and two lines containing `1`
were printed, as stated in the deconstruction of the code.

This is a bad exam question because you have to make a number of
questionable assumptions to come up with the answer that the exam-setter
expects.
