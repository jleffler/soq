### `sortlines1`, `sortlines2` and `sortlines3`

Three variants of how to sort lines from a file.

* The `sortlines1` version is limited to 1000 lines maximum.

* The `sortlines2` version allocates line pointers as needed, but it
  uses the buffer allocated by POSIX
  [`getline()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html)
  and makes it allocate anew for each line.  This is wasteful,
  especially for short lines, since it typically allocates 256 byte to
  avoid needing to reallocate for most lines.

* The `sortlines3` version also allocates line pointers as needed, also
  using POSIX `getline()`, but it uses POSIX
  [`strdup()`](http://pubs.opengroup.org/onlinepubs/9699919799/functions/strdup.html)
  to store the data, so it uses far less memory for typical source code
  files, etc.

### `sortwords1` and `sortwords2`

* The `sortwords1` version is a simple adaptation of the code from
  `sortlines3`, where `sscanf()` is used to split the line read by
  `getline()` into words.
  The word buffer (`nxt_word`) is made big enough for a oine consisting
  of a single line, with assert protection against lines bigger than 1
  MiB.

* The `sortwords2` program uses my `stderr.[ch]` package for error
  reporting (using a fixed argument to `err_setarg0()` rather than
  modifying `main()` to accept arguments).
  It also uses the `aoscopy.[ch]` code to store the array of strings.
  That conceals a lot of details, which is valuable.

### History

I couldn't identify which SO question these provide an answer to.
There was such a question; the comments indicate that there was an
incorrect answer and this code was written to demonstrate that.
But the Git history is silent on the details.

However, they are applicable, after a fashion, to
[SO 5769-8054: How to fscanf() word by word in a file?](https://stackoverflow.com/questions/57698054/how-to-fscanf-word-by-word-in-a-file)
though the programs `sortlines3` and `sortwords1` and `sortwords2` were
specifically written as possible responses to that question.

The programs were originally `sortfile1` and `sortfile2`, but the names
using `lines` and `words` are more apposite and were changed when
looking at SO 5769-8054.
