### Stack Overflow Question 4801-3629

[SO 4801-3629](https://stackoverflow.com/q/48013629) &mdash;
Separate punctuation marks in C from a word

Efforts by 3 authors.

* `punc37.c`

Using `AoS_Copy` code (`aoscopy.h`, `aoscopy.c`), but only after
extending it to add `aosc_addbytes(AOS_Copy *aos, const char *src, const
char *eos)` to copy a substring starting at `str` with `eos` pointing
one byte beyond end of string.
The copy is null terminated, of course.
It does show that it is easy to manage with the set of functions.

* `punc41.c`

An adaptation of `punc37.c` that includes apostrophes in words.

* `punc47.c`

Code by J Guo.  Compiles cleanly; works well.

* `punc73.c`

Code by Nick S.  Compiles cleanly; works well.

### Gruesome test cases

The original sentence was:

    Hello, my name is Sarah!

A more complex sentence is:

    It isn't true that Bill O'Reilly came in 3rd!

A still more complex sentence is:

    Isn't it true that Bill O'Reilly didn't win (he came in 3rd!)? 'Tain't necessarily so!;

This has a word (`'Tain't`) starting with an apostrophe.
It's possible to have words ending with an apostrophe too (`Jesus'` is a
classic example).
Identifying embedded apostrophes is easy enough.
Identifying leading or trailing apostrophes is harder.

