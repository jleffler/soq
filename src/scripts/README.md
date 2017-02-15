### The `scripts` Directory

This directory contains the version-controlled source of shell scripts
(and any other scripting language).
The files here have a language-specific suffix.

The 'compilation' process creates a copy of the script without any
suffix and moves it to the top-level `bin` directory, which can be added
to `$PATH`.
It is recommended that it is added at the end of the PATH, not the
beginning.

