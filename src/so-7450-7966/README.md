### Stack Overflow Question 7450-7966

[SO 7450-7966](https://stackoverflow.com/q/74507966) &mdash;
Reading everything currently entered in stdin

Here's an offering that meets my interpretation of your requirements:

* The program reads whatever data is typed (or otherwise entered) on standard input in a period of 10 seconds (stopping if you manage to enter 2047 characters — which would probably mean that the input is coming from a file or a pipe).
* After 10 seconds, it prints whatever it has collected.
* It stops without printing on receiving signals.
* If the signal is interrupt, quit, hangup, pipe or terminate (SIGINT, SIGQUIT, SIGHUP, SIGPIPE, SIGTERM), it stops without printing anything.
* It fiddles with the terminal settings so that the input is unbuffered.  This avoids it hanging around.  It also ensures that system calls do not restart after a signal is received.  That may not matter on Linux; using `signal()` on macOS Big Sur 11.7.1, the input continued after the alarm signal, which was not helpful — using `sigaction()` gives you better control.
* It does its best to ensure that the terminal mode is restored on exit, but if you send an inappropriate signal (not one of those in the list above, or SIGALRM), you will have a terminal in non-canonical (raw) mode.  That leads to confusion, in general.
* It is easy to modify the program so that:
  - input is not echoed by the terminal driver;
  - characters are echoed by the program as they arrive (but beware of editing characters);
  - signals are not generated by the keyboard;
  - so it doesn't futz with standard input terminal attributes if it is not a terminal.

### Code

- Source code in tensec53.c

Compilation:
```none
gcc -O3 -g -std=c11 -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes -fno-common tensec53.c -o tensec53 
```
No errors (or warnings, but warnings are converted to errors).

### Analysis
* The `#undef` line removes any macro definition of `sigemptyset()`
  leaving the compiler calling an actual function.  The C standard
  requires this to work ([§7.1.4
  ¶1](http://port70.net/~nsz/c/c11/n1570.html#7.1.4)).  On macOS, the
  macro is `#define sigemptyset(set) (*(set) = 0, 0)` and GCC complains,
  not unreasonably, about the "right-hand operand of comma expression
  has no effect".  The alternative way of fixing that warning is to test
  the return value from `sigemptyset()`, but that's arguably sillier
  than the macro.  (Yes, I'm disgruntled about this!)
* The `sane` variable records the value of the terminal attributes when
  the program starts — it is set by calling `tcgetattr()` in
  `stty_raw()`.  The code ensures that `sane` is set before activating
  any code that will call `sttr_sane()`.
* The `stty_sane()` function resets the terminal attributes to the sane
  state that was in effect when the program started.  It is used by
  `atexit()` and also by the signal handlers.
* The `stty_raw()` function gets the original terminal attributes, makes
  a copy of them, modifies the copy to turn off canonical processing
  (see [Canonical vs non-canonical terminal
  input](https://stackoverflow.com/q/358342/15168) for more details),
  and sets the revised terminal attributes.
* Standard C says you can't do much in a signal handler function than
  set a `volatile sig_atomic_t` variable, call `signal()` with the
  signal number, or call one of the exit functions.  POSIX is a lot more
  gracious — see [How to avoid using `printf()` in a signal
  handler?](https://stackoverflow.com/q/16891019/15168) for more
  details.
* There are two signal handlers, one for SIGALRM and one for the other
  signals that are trapped.
* The `alarm_handler()` ignores further alarm signals and records that
  it was invoked.
* The `other_handler()` ignores further signals of the same type, resets
  the terminal attributes to the sane state, and exits with a status
  used to report that a program was terminated by a signal (see POSIX
  shell [Exit status for
  commands](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_08_02)).
* The `getch()` function reads a single character from standard input,
  mapping failures to `EOF`.  The cast ensures that the return value is
  positive like `getchar()` does.
* The `set_handler()` function uses `sigaction()` to set the signal
  handling.  Using `signal()` in the signal handlers is a little lazy,
  but adequate.  It ensures that the `SA_RESTART` bit is not set, so
  that when a signal interrupts a system call, it returns with an error
  rather than continuing.
* The `dump_string()` function writes out a string with any
  non-printable characters other than space characters reported as a hex
  escape.
* The `main()` function sets up the terminal, ensures that the terminal
  state is reset on exit (`atexit()` and the calls to `set_handler()`
  with the `other_handler` argument), and sets an alarm for 10 seconds
  hence.
* The reading loop avoids buffer overflows and stops when the alarm is
  received or EOF (error) is detected.
* Because canonical processing is turned off, there is no line editing.
  The body of the loop provides primitive line editing — it recognizes
  the erase (usually backspace `'\b'`, sometimes delete `'\177'`)
  character and the EOF character and handles them appropriately,
  otherwise adding the input to the buffer.
* When the loop exits, usually because the alarm went off, it null
  terminates the string and then calls `dump_string()` to print what was
  entered.

### POSIX headers and functions:
| Headers | Functions | Functions |
|:--------|:----------|:----------|
| [`<ctype.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/ctype.h.html) | [`alarm()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/alarm.html) | [`putchar()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/putchar.html) |
| [`<signal.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html) | [`atexit()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/atexit.html) | [`read()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html) |
| [`<stdio.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html) | [`exit()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/exit.html) | [`sigaction()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigaction.html) |
| [`<stdlib.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdlib.h.html) | [`isprint()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/isprint.html) | [`sigemptyset()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigemptyset.html) |
| [`<termios.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/termios.h.html) | [`isspace()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/isspace.html) | [`signal()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/signal.html) |
| [`<unistd.h>`](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html) | [`perror()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/perror.html) | [`tcgetattr()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/tcgetattr.html) |
| | [`printf()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/printf.html) | [`tcsetattr()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/tcsetattr.html) |
