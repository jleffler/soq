### Stack Overflow Question 7874-7328

[SO 7874-7328](https://stackoverflow.com/q/78747328) &mdash;
Reverse singly-linked list in C and return new head

* `rvsll37.c`
  Mostly minor amendments to the main answer
  (https://stackoverflow.com/a/78747358) by
  [user24714692](https://stackoverflow.com/users/24714692/user24714692).
  That answer was edited to capture the new head after reversal, maybe as
  a result of a now deleted comment by me.  This code avoids dereferencing
  a null pointer on failed allocation (by reporting an error and exiting).
  The code protected by // allows you to check that the allocated data is
  all freed.

* `rvdll61.c`
  Analogous code for reversing a doubly-linked list.
