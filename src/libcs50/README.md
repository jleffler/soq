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

* https://github.com/cs50/libcs50

The code underwent a lot of revisions during the middle of 2016
(May-September).
This included renaming all the functions from `Get[A-Z]*` to
`get_[a-z]*`.
This name change wasn't entirely popular; they've created pointers to
functions with the old names as some sort of transitional measure.
The old names underwent deprecation and then undeprecation.

The new functions are much more complex, using variable length argument
lists and having the ability to prompt the user.
Each function call is over-ridden by a macro which does some complex
preprocessor magic to determine what's present in the argument list.
The actual functions have an eccentric interface, such as:

    string get_string(va_list *args, char const *format, ...)

A function taking both a `va_list` as an argument and then `, ...` too
is, shall we say, unusual.

The `get_string()` function also allocates memory, but has a
'destructor' invoked via `atexit()` that releases the memory for you.
The destructor also sets standard output to non-buffered output.
Your code cannot safely free the memory that is allocated by
`get_string()`, which (frankly) is a step backwards in functionality.
Someone got far too clever for their own good.

This is no longer code that the victims (sorry, I mean students) of CS50
can be expected to understand (I'm not sure I understand all of it!).
I am moderately convinced this is not a useful change.

<hr>

The code in old-cs50.h and old-cs50.c was directly copied from the
Harvard site in early 2016.
It is the version prior to the name changing.

The code in cs50.h and cs50.c was copied from GitHub on 2017-08-13.

Note that on a Mac running macOS Sierra 10.12.6, there is a
system-provided function `get_string()` with a different interface.
It is not documented by a man page.
It allows programs to link, but they crash when running.

Don't use this for your own code &mdash; get the code from GitHub.
The `makefile` builds the library as a static archive.
Using `make install` places the library and header in the correct
directories so that other code using the library will compile correctly.
