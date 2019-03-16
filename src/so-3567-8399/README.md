### Stack Overflow Question 3567-8399

[SO 3567-8399](https://stackoverflow.com/q/35678399) &mdash;
How to output a marquee string that is smaller than the size of the marquee sign?

None of this code was submitted as an answer.
The code available here is considerably more complex than the code in
the question because it does overwriting and timing etc.

All the programs run for a while and then stop.

* `marquee.c`

  Unidirectional rotation, and the full string is always displayed
  (which isn't what the question asks about).

* `marquee3.c`

  Bidirectional rotation (showing the string twice, rotating both
  leftwards and rightwards).  Again, the full string is always
  displayed.

* `marquee4.c` — driven solely from the command line.

  `Usage: marquee4 [-hV][-d delay][-p pad][-w width] 'message'`

  This allows you to specify the pad (default `"..."`), the width
  (default 15) and the delay (in milliseconds — default is 100 ms),
  and the message.  This handles all the cases — length shorter than,
  equal to, or longer than the width of the marquee display.
