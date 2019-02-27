### Stack Overflow Question 1382-7096

[SO 1382-7096](https://stackoverflow.com/q/13827096) &mdash;
How can I compile and run this 1989 written C program?

### What is this incunabulum code?

Nominally, an incunabulum is an early printed book, especially one
printed before 1501 (Mac dictionary).
Here it refers to 'ancient code'.

* See: http://code.jsoftware.com/wiki/Essays/Incunabulum
* And: [Why won't my Little LISP quote](https://stackoverflow.com/questions/18096456)

The code in `incunabulum.c` looks like a direct copy of the code from
JSoftware.

The second SO question has many links, including to the Incunabulum
essay, but seems less directly relatedto the code of incunabulum.c.

### What gives?

The code doesn't compile without scads of warnings.
The code mixes up int, long and pointer; it might compile and maybe run,
sort of, under `-m32` but it won't under `-m64`.

### Cygwin

Under a 64-bit Cygwin, the `-m32` (32-bit) libraries are not necessarily
available.
Suppress this build with `make -t`.
