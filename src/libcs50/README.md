# CS50 &mdash; Harvard's CS50 Course C Library

The
[CS50](https://www.edx.org/course/introduction-computer-science-harvardx-cs50x)
course is an introductory computer science course from Harvard
University as part of its edX program.
It is available for self-study.

There is a C library available at [CS50
Library](https://manual.cs50.net/library/) which provides support
functions for the course.

* There is also the [CS50](http://cs50.stackexchange.com/) Stack
* Exchange site dedicated to the course.

The code is available from GitHub:

* https://github.com/cs50/libcs50 (and not
  https://https://github.com/cs50/c as documented in the code as of
  commit 5cde13b; issue #4 created for this glitch)

The code underwent a lot of revisions during the middle of 2016
(May-September).
This included renaming all the functions from `Get[A-Z]*` to
`get_[a-z]*`.
This name change wasn't entirely popular; they've created pointers to
functions with the old names as some sort of transitional measure.
The old names underwent deprecation and then undeprecation.

<hr>

The code in cs50.h and cs50.c was directly copied from the Harvard site
in early 2016.
It is still the version prior to the name changing.
Don't use this for your own code &mdash; get the code from GitHub.
The `makefile` builds the library as a static archive.
Using `make install` places the library and header in the correct
directories so that other code using the library will compile correctly.
