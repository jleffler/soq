# Introduction

There are a number of guidelines to follow when creating and using
header files in a C project:

* Idemopotence

  If a header file is included multiple times in a translation unit
  (TU), it should not break builds.

* Self-containment

  If you need the facilities declared in a header file, you should not 
  have to include any other headers explicitly.

* Minimality

  You should not be able to remove any information from a header without
  causing builds to fail.

* Include What You Use (IWYU)

  Of more concern to C++ than C, but nevertheless important in C too.
  If the code in a TU (call it `code.c`) directly uses the features
  declared by a header (call it `"headerA.h"`), then `code.c` should
  `#include "headerA.h"` directly, even if the TU includes another
  header (call it `"headerB.h"`) that happens, at the moment, to include
  `"headerA.h"`.

Occasionally, there might be good enough reasons to break one or more of
these guidelines, but you should both be aware that you are breaking the 
rule and be aware of the consequences of doing so before you break it. 

