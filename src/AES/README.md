### AES

This code is simply a copy of a reference implementation of AES,
produced by Christophe Devine and released under GNU GPL v2 or later.
(Source from http://www.cs.rochester.edu/u/brown/Crypto/src/AES.c)

It probably does not have a long-term future here.

NB: Critiques include:

* Too many global variables (they should be file static).
* The code can only handle a complete single-block message.
* No support for any encryption mode other than ECB and that by default
  rather than design.

