### Stack Overflow Question 4404-0027

[SO 4404-0027](https://stackoverflow.com/q/44040027) &mdash;
Spell checker in C

Convoluted history, with much of the action not visible on SO.
Emails with the OP caused some confusion (helped by Gmail truncating an
email at the exact end of the first of two spreadsheets and me not
spotting the truncation until a (much) later email mentioned the second
one.)

Two commands, `wordoffsets` and `checkoffsets`, were created to validate
the data generated.
However, when it came down to it, offsets weren't the problem.

There was a problem with the trie building code in question, it
eventually transpired, and also a problem in the trie search code.
This led to words being omitted from the output.

* The code in `sc19.c` uses 1-based offsets into the file.

* The code in `sc61.c` uses 0-based offsets into the file.
  It also adds rudimentary argument handling.

* Both these have the flawed build and search code.

* The code in `sc59.c` is a development of `sc61.c` with more complete
  argument handling, extra options, using `stderr.h` and `timer.h`, and
  with the trie build and search code fixed.

* The code in `spell-checker-ac.c` is the code used by the OP.

* The script `mknopunct.sh` takes the file `linux.words` (a Linux word
  list downloaded from
  http://www.math.wichita.edu/~axmann/Math714/Misc/linux.words) and
  copies the lines which contain only alphabetic characters into
  `no-punctuation-linux.words`.

For a while there was confusion about the nature of the problem, and the
`wordoffsets` and `checkoffsets` programs are in part a manifestation of
that confusion.
However, they do have semi-plausible uses separately from this.
They are mastered in RCS still — one year, I'll resolve how my systems
are going to handle the lack of version numbers in Git.
I really don't like VCS that don't handle version numbers cleanly and
automatically, but Git definitely falls into that category (so does
Atria ClearCase).

The programs expect to use a dictionary of pure alphabetic words,
strictly one word per line.
The default file name is `dictionary.txt`.
The programs expect to analyze an article, which may have punctuation in
it, of course, but the punctuation will be ignored except as a word
break.
The default file name is `article.txt`.
The programs expect to write 'misspelled' words to a text file.
The default file name is `misspelling.txt`.

