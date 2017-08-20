SOQ - Stack Overflow Questions
------------------------------

A repository of material related to [Stack
Overflow](http://stackoverflow.com/) questions and answers, primarily
those where [Jonathan
Leffler](http://stackoverflow.com/users/15168/jonathan-leffler) has
contributed.
This is by no means a complete list of the questions or answers
contributed; these are just the more interesting ones where some part of
the contribution was placed under version control.

Note that some questions have been deleted and therefore users with less
than 10K of Stack Overflow reputation will not be able to see the
referenced question.

As of 2016-08-20, the repository is mostly stable.
Most of the material is present with a separate source directory for each
question, such as `src/so-3567-8399`.
There are some exceptions to this in the src directory, with composite
directories containing code related to multiple SO questions, or no SO
question at all.

For the time being, the directory name for an answer to SO question
number abcdwxyz is saved in src/so-abcd-wxyz (e.g. the code for [SO
3333-8314](http://stackoverflow.com/q/33338314) is in the directory
`src/so-3333-8314`).
Note that SO does not recognize the punctuation in the number.
Also note that if you don't know the question number, finding the
relevant material can be hard.
There are some directories in `src` that group others (`matrices`,
`miscellany`, `posix-regex`, `primes`, `python`, `tries`).
These are neither comprehensive (there could easily be other questions
that refer to the same topic) nor complete (there are many other topics
covered by several answer that could be grouped together).

The `inc` top-level directory is the directory where common headers are
installed (but the source for them is in `src/libsoq` and `src/libcs50`
or other locations as appropriate).
Similarly, the `lib` top-level directory contains the installed
libraries of common code (but the source for it is in `src/libsoq` and
`src/libcs50`).
The headers and libraries are installed by running `make install` in the
relevant source directories.

The `etc` directory contains miscellaneous files, such as the common
makefile control information and also [`valgrind`](http://valgrind.org/)
suppressions file for Mac OS X 10.11.6 (and 4 and 5) and for macOS
Sierra 10.12.5.

<a href="http://stackoverflow.com/users/15168/jonathan-leffler">
<img src="http://stackoverflow.com/users/flair/15168.png" width="208" height="58" alt="Profile for Jonathan Leffler at Stack Overflow, Q&amp;A for professional and enthusiast programmers" title="Profile for Jonathan Leffler at Stack Overflow, Q&amp;A for professional and enthusiast programmers">
</a>
