### Stack Overflow Question 4574-5483

[SO 4574-5483](https://stackoverflow.com/q/45745483) &mdash;
A breadth-first search in a binary tree of processes using fork

                              1
                              |
                +-------------+-------------+
                |                           |
                2                           3
                |                           |
         +------+------+             +------+------+
         |             |             |             |
         4             5             6             7
         |             |             |             |
     +---+---+     +---+---+     +---+---+     +---+---+
     |       |     |       |     |       |     |       |
     8       9     10      11    12      13    14      15

The code in `ptree29.c` is almost what the OP posted.
The changes are solely in setting `n` to `4` by default, and testing
`narg` (aka `argc` in a normal signature for `main()`) before using
`argv[1]`.
Given a large enough argument (4 or more), the output is not in
sequence.
Given a small enough argument (3 or less), the output sometimes is in
sequence.

The code in `ptree17.c` is the version posted in the answer.
It uses `open()` — it isn't absolutely clear that was permitted —
and also `nanosleep()` for 1 millisecond at a time to control the
sequencing.
The delay reduces the retries (probably dramatically, though no testing
was conducted to validate that.

If files can't be used (only `pipe()` is allowed), then someone has some
serious thinking to do.
Offhand, I don't see a simple solution.
Indeed, I'm not sure I see a complex solution either.
