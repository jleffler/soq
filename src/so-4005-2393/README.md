# SO 4005-2393

Not a great question, but this rewritten and simplified code is
unexpectedly not working, and the reasons why are far from clear.

The value stored in `*node` changes unexpectedly.
Both Clang (from XCode 8) and various versions of GCC including GCC
6.2.0 produce the same result, so it probably isn't a compiler bug.

