### The `scripts` Directory

This directory contains the version-controlled source of shell scripts
(and any other scripting language).
The files here have a language-specific suffix.

The 'compilation' process creates a copy of the script without any
suffix and moves it to the top-level `bin` directory, which can be added
to `$PATH`.
It is recommended that it is added at the end of the PATH, not the
beginning.

The scripts include:

* `ddpr` — double-digit prime number
* `fixin` — fix interpreter after shebang
* `pipe-rot` — Rule of Thumb: closing pipe file descriptors
* `posixcmd` — URL for POSIX command(s) specified on command line
* `posixfun` — URL for POSIX functions(s) specified on command line
* `posixhdr` — URL for POSIX header(s) specified on command line
* `man7` — URL for Linux command, system call, function (-s section)
* `rfn` — Generate unique random file name with prefix and a 2-digit prime number
    * `rfn-c` — Generate a `.c` file
    * `rfn-cpp` — Generate a `.cpp` file
    * `rfn-h` — Generate a `.h` file
    * `rfn-pl` — Generate a `.pl` file
    * `rfn-sh` — Generate a `.sh` file
    * `rfn-sql` — Generate a `.sql` file
* `so` — Indent non-empty lines by 4 spaces
* `so-books` — List of books and URLs
* `so-c-reserved` — Standard spiel about C reserved words and leading undersccores
* `so-dotarrow` — Standard spiel about spaces around the dot and arrow operators
* `so-esql` — Standard spiel about not using the `esql` tag
* `so-getchar` — Standard spiel about `getchar()`
* `so-late` — Comment for a late answer to an old question
* `so-quotes` — List of quotes about programming
* `so-reformat-c` — (Mac only) Run `decrust` (Uncrustify) on C code to `pbcopy`
* `so-stderr` — Identify source code in SOQ GitHub repository
* `soa` — Create a skeletal SO answer (rarely used)
* `sops` — Set PS1, PS2 for use with `so`, etc (rarely used)
* `soqvg` — Run Valgrind with suppressions
* `sow` — Welcome to SO; please create an MCVE
* `sscce` — Standard spiel about MCVE or SSCCE
* `wso` — Welcome to SO; please accept an answer
