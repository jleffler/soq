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
The code groups adjacent punctuation together into a single
multi-character symbol.

* `punc41.c`

An adaptation of `punc37.c` that includes apostrophes in words.

* `punc47.c`

An adaptation of `punc41.c` that handles apostrophes at the start, in
the middle, and at the end of words.  It also uses inline functions to
deal with the the inconvenient interface to `isalnum()` and related
functions from `<ctype.h>`.  These inline functions include the
necessary cast to `unsigned char`.  The inline functions cannot be used
if the argument could be `EOF`.  The names `is_alnum()` etc are not
reserved identifiers: names starting `is` or `to` followed by a
lower-case letter are
[reserved](http://port70.net/~nsz/c/c11/n1570.html#7.31.2).

* `punc73.c`

Code by [Nick S](https://stackoverflow.com/users/8209813/nick-s).
Compiles cleanly; works well.

* `punc97.c`

Code by [J Guo](https://stackoverflow.com/users/8777237/j-guo).
Compiles cleanly; works well.
It uses a very different algorithm.
It makes a modified copy of the original string, adding spaces around
punctuation, so that the copy can be parsed with `strtok()`.

### Gruesome test cases

The original sentence was:

    Hello, my name is Sarah!

A more complex sentence is:

    It isn't true that Padraig O'Malley came in 3rd!

A still more complex sentence is:

    Isn't it true that Padraig O'Malley didn't win (he came in 3rd!)? 'Tain't necessarily so!;

This has a word (`'Tain't`) starting with an apostrophe.
It's possible to have words ending with an apostrophe too (`Jesus'` is a
classic example).
Identifying embedded apostrophes is easy enough.
Identifying leading or trailing apostrophes is harder.

Hence, a last example:

    'Tain't an Archimedes' Screw

### Compilation issues

The code relies on a package `aoscopy.[ch]` which provides management
for arrays of strings (AoS or aos) by copying.
This code has not yet made it to the SOQ repository.
Consequently, this is (as yet) of limited help.

