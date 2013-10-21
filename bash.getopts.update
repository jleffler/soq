
<hr>

Note that GNU has created an alternative program called (confusingly)
`getopt` that has a different calling convention from classic Unix
program of the same name.  For a discussion of how to use that, see the
[answer][1] by [Urban Vagabond][2].  _Do not treat the two as
interchangeable_; they are not.  For example, if one of the arguments is
`'${OPTION}'` on the command line, using the GNU-style `eval set --
$(getopt ... -- "$@")` with an old-style `getopt` will cause the shell
to evaluate `${OPTION}` where the GNU-style `getopt` will leave it
unchanged.  (Actually, the `--` in the GNU-style `getopt` argument list
is incompatible with the old-style `getopt`.)

If your code is destined only for platforms where the GNU-style `getopt`
is available, by all means use it.  If your code is destined for other
platforms (for example, HP-UX, AIX, Solaris) where the GNU-style
`getopt` is not available, use (first choice) `getopts` as a built-in
with single character options only or (second choice) the `getopt`
example code above.  There isn't a common invocation that works
correctly with both the GNU-style and old-style versions of `getopt`
under all circumstances.  IMNSHO, the extended GNU `getopt` should have
been given a new name, such as `getoptx` or `getopt_long`, to recognize
that it is not the same as the original `getopt` program.



But see GNU getopt(1) manual, including:-


NAME

       getopt - parse command options (enhanced)

SYNOPSIS

       getopt optstring parameters

       getopt [options] [--] optstring parameters

       getopt [options] -o|--options optstring [options] [--] parameters

...

If the environment variable GETOPT_COMPATIBLE is set, or if its first
parameter is not an option (does not start with a ‘-’, this is the
first format in the SYNOPSIS), getopt will generate output that is
compatible with that of other versions of getopt(1).  It will still do
parameter shuffling and recognize optional arguments (see section
COMPATIBILITY for more information).

...

COMPATIBILITY

This version of getopt(1) is written to be as compatible as possible to
other versions.  Usually you can just replace them with this version
without any modifications, and with some advantages.

If the first character of the first parameter of getopt is not a
‘-’, getopt goes into compatibility mode.  It will interpret its
first parameter as the string of short options, and all other arguments
will be parsed.  It will still do parameter shuffling (ie. all
non-option parameters are outputed at the end), unless the environment
variable POSIXLY_CORRECT is set.

The environment variable GETOPT_COMPATIBLE forces getopt into
compatibility mode.  Setting both this environment variable and
POSIXLY_CORRECT offers 100% compatibility for ‘difficult’ programs.
Usually, though, neither is needed.

In compatibility mode, leading ‘-’ and ‘+’ characters in the
short options string are ignored.



  [1]: http://stackoverflow.com/questions/402377/using-getopts-in-bash-shell-script-to-get-long-and-short-command-line-options/7948533#7948533
    [2]: http://stackoverflow.com/users/907263/urban-vagabond
