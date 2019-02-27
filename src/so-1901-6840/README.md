### Stack Overflow Question 1901-6840

[SO 1901-6840](https://stackoverflow.com/q/19016840) &mdash;
Using mergesort to sort linked lists

* `list.h`

  Define structure types and declare functions.

* `list.c`

  Implement basic list management functions.  The list access functions
  are now all implemented but unused — the structure isn't opaque so
  it isn't clear they're really necessary.  This code has a structure
  with head, tail and size values, separate from the nodes inserted into
  the list.  This speeds access to the end of the list, of course, but
  isn't always necessary.

* `mergelist.c`

  Implements the sorting code, plus a test harness.

