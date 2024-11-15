### Stack Overflow Question 7918-2426

[SO 7918-2426](https://stackoverflow.com/q/79182426) &mdash;
How to traverse a matrix in a spiral

More or less a 'Gimme the Codez' question, but mildly interesting.

* `spiral29.c` - initial code.  It works, but there is a lot of room for
   improvement.  It also has hand-worked example spirals and discussion.
* `spiral41.c` - revised code, removing some of the repetition and using
   a structure.
* `spiral79.c` - split spiral code off from main program so multiple
   invocations are easy
* `spiral83.c` - counting cells recorded (much simpler)
* `spiral89.c` - using a 2D VLA instead of a structure.  The question as
   written specifies the use of a 2D array.  This code still uses the
   Control structure.  It isn't clear whether the OP is allowed to use
   structures.

Not posted to Stack Overflow.
