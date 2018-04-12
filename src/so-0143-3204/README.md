### Stack Overflow Question 0143-3204

[SO 0143-3204](https://stackoverflow.com/q/01433204) &mdash;
How do I use extern to share variables between source files in C?

* The text of the answer is in `extern-definitions`.

* The code for the answer is in the various source files.

    * `broken_header.h`
    * `external.h`
    * `externdef.h`
    * `faulty_header.h`
    * `file1.c`
    * `file10.c`
    * `file11.c`
    * `file12.c`
    * `file1a.c`
    * `file1b.c`
    * `file1c.h`
    * `file2.c`
    * `file2a.c`
    * `file2b.c`
    * `file2c.h`
    * `file2d.h`
    * `file3.h`
    * `file3a.h`
    * `file3b.h`
    * `file3c.c`
    * `file4c.c`
    * `file5c.c`
    * `file6c.c`
    * `file7c.c`
    * `file8c.c`
    * `file8c.h`
    * `file9c.c`
    * `prog1.c`
    * `prog1.h`
    * `prog2.c`
    * `prog2.h`
    * `prog3.c`
    * `prog3.h`
    * `prog4.c`
    * `prog4.h`
    * `prog5.c`
    * `prog8.c`
    * `seldom_correct.h`

* The `makefile` will build the various programs.
  It also arranges to interpolate the source code into the answer text to create
  `extern-definitions.txt`, which is the answer shown on Stack Overflow.
  It has a rule to create `so-1433204.tar.gz`, a gzipped tar file
  containing all this material, which is effectively the material for a
  'release' of this answer.
  At the moment, the release is not accessible on GitHub.

* The `insert-code.pl` script does the actual interpolation.

* The script `check-references.sh` is used to ensure that the references
  in `extern-definitions` are complete &mdash; that there is a reference
  in the first argument to each of the other arguments in the specific
  format that `insert-code.pl` uses.
  It does not yet check that each reference in the first argument matches
  one of the other arguments, but in theory, it should.

