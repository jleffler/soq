### Stack Overflow Question 4672-0692

[SO 4672-0692](https://stackoverflow.com/q/46720692) &mdash;
Trying to implement a shell with two or more pipes but the program hangs

<hr>

### Digression

Worked on in run-up to getting gold badge for the `pipe` tag on SO, as
part of WinterBash 2017 — and attaining the 'Foot of the Rainbow' hat
(for getting a gold badge).
Curiously, I'm the only person with a silver tag badge too.
And by the time I was trying to get the badge, it was only necessary to
answer more questions; I already more than enough points from previous
pipe questions.

The other questions answered were:

* [Fork child process not reading from pipe](https://stackoverflow.com/questions/44180272)
* [Trying to use pipe to from / write to another program](https://stackoverflow.com/questions/44087031)
* [Parent reads operations from file and the child sums it with bc](https://stackoverflow.com/questions/44505451)
* [How to pipe own output to another process](https://stackoverflow.com/questions/25384377)
* [How to make a bidirectional link in client-server program](https://stackoverflow.com/questions/47496517)
* [How to run another program, pass data through stdin, and get its stdout output](https://stackoverflow.com/questions/47579087);

SO 4672-0692 was not answered until after the gold badge had been earned.

<hr>

In part, this directory was created because I took a step too far and
broke the shell I'd been modifying to get more debug information —
without using a VCS to protect myself.
Stupid!

<hr>

### `shell59.c`

This is very close to the original code posted.
It was not bad code; it compiled with warnings about missing prototypes
for the functions, and about the unused `argc` and `argv` in `main()`.
Those are very normal warnings to have to fix — especially the missing
prototypes.

### `shell23.c`

This was the development version of the code, mostly instrumented rather
than fixed.
The instrumentation demonstrates that there are too many file descriptors
open (now there's a surprise).

### `shell79.c`

This is a development of `shell23.c` which remedies the problems.
It mainly closes many more pipe file descriptors.
It uses a function `logmsg()` to record PID and function name as well
as a formatted message.
It cuts down on the number of calls to `getpid()` in the code, and makes
the formatting more uniform.
A few of the functions acquire an extra argument.

The code can now use `waitpid()` to wait for specific PIDs.
This at least makes the messaging consistent.
The children tend to die in the reverse order, as can be seen
by replacing `waitpid(pid, &status, 0)` with `wait(&status)`.

The code also avoids creating an unused pipe for the last child.

