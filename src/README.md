# Source directory

Primarily contains other directories, some scripts, a makefile, and this README.

The scripts are:
* `add-readme.sh` &mdash; add a README.md file to directories without one.
  It gets the SO question title from SO (probably in the worst possible
  way, but it works, just about).
* `mkmk.sh` &mdash; create a skeleton makefile for directories without one.
  It uses a command, `gitignore`, for which the source is not yet
  present in GitHub (bug).
* `updmkfile.sh` &mdash; add new answer directories to the makefile.
  It uses a command, `mklist`, for which the source is not yet present
  in GitHub (bug).

One day, the scripts may be moved to a bin directory.

It should not normally contain any other files.

<hr>

A self-deleted question: [SO 3909-2852](http://stackoverflow.com/questions/39092852/whats-the-bug-in-my-code-or-is-the-bug-in-gcc)
