#!/bin/sh
#
# Standard spiel on omitting return 0 from the end of main

cat <<'EOF'
In one of the less felicitous decisions in C99 ([§5.1.2.2.3 Program
termination](http://port70.net/~nsz/c/c11/n1570.html#5.1.2.2.3) in C11),
you are allowed to omit the `return 0;` at the end of `main()` — and
only `main()` — and zero will be returned.

> If the return type of the `main` function is a type compatible with
> `int`, a return from the initial call to the main function is
> equivalent to calling the `exit` function with the value returned by
> the `main` function as its argument; reaching the `}` that terminates
> the `main` function returns a value of 0.

Compare with [§6.9.1 Function definitions
¶12](http://port70.net/~nsz/c/c11/n1570.html#6.9.1p12) which says:

> If the `}` that terminates a function is reached, and the value of the
> function call is used by the caller, the behavior is undefined.

The C standard also says 0 has the same effect as EXIT_SUCCESS, which (I
believe) caused angst for VMS where an exit code of 0 meant failure.
Exiting with a non-zero status might be a portability issue; for that
there is EXIT_FAILURE in `<stdlib.h>`.
But an exit status of 0 is required to be reported to the environment as
success (see C11 [§7.22.4.4 The exit function
¶5](http://port70.net/~nsz/c/c11/n1570.html#7.22.4.4p5)).

The 'implicit return 0 feature' was introduced largely for compatibilty
with C++98, which also allows it.
I regard that rule as an abomination, but it is part of the C standard.
Personally, I aim to always write the `return 0;` or equivalent at the
end of `main()` — it's only an accident when I omit it, to be fixed
ASAP.

EOF
