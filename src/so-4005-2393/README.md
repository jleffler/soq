### Stack Overflow Question 4005-2393

[SO 4005-2393](https://stackoverflow.com/q/40052393) &mdash;
How to access the data inside a node whose memory location has been freed?

Not a great question, but this rewritten and simplified code is
unexpectedly not working, and the reasons why are far from clear.

The value stored in `*node` changes unexpectedly.
Both Clang (from XCode 8) and various versions of GCC including GCC
6.2.0 produce the same result, so it probably isn't a compiler bug.

In program `ll31`, the OP's code — function `remove_node1()` —
causes a segmentation fault.  If that's commented out, there's no
trouble.  Using `malloc_debug` to trap problems does not seem to help
identify the error.
