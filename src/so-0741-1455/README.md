# Stack Overflow Question 0741-1455

[SO 0741-1455](https://stackoverflow.com/q/07411455) &mdash;
What does &quot;export&quot; do in shell programming?

There have been multiple edits that have confused things.

* [Davis Herring](https://stackoverflow.com/users/8586227/davis-herring)
* [Elliptical View](https://stackoverflow.com/users/1483904/eliptical-view)
* [Fedorqui](https://stackoverflow.com/users/1983854/fedorqui)
* [Victor Yarema](https://stackoverflow.com/users/2753851/victor-yarema)

### Markup Answer as of Revision 9 (2018-12-25 00:03:48Z - JL)

Exported variables such as `$HOME` and `$PATH` are available to
(inherited by) other programs run by the shell that exports them (and
the programs run by those other programs, and so on) as environment
variables.  Regular (non-exported) variables are not available to other
programs.

    $ env | grep '^variable='
    $                                 # No environment variable called variable
    $ variable=Hello                  # Create local (non-exported) variable with value
    $ env | grep '^variable='
    $                                 # Still no environment variable called variable
    $ export variable                 # Mark variable for export to child processes
    $ env | grep '^variable='
    variable=Hello
    $
    $ export other_variable=Goodbye   # create and initialize exported variable
    $ env | grep '^other_variable='
    other_variable=Goodbye
    $

For more information, see the entry for the [`export`
builtin](http://www.gnu.org/software/bash/manual/bash.html#index-export)
in the GNU Bash manual, and also the sections on [command execution
environment](https://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
and
[environment](https://www.gnu.org/software/bash/manual/bash.html#Environment).

Note that non-exported variables will be available to subshells run via
`( ... )` and similar notations because those subshells are direct
clones of the main shell:

    $ othervar=present
    $ (echo $othervar; echo $variable; variable=elephant; echo $variable)
    present
    Hello
    elephant
    $ echo $variable
    Hello
    $

The subshell can change its own copy of any variable, exported or not,
and may affect the values seen by the processes it runs, but the
subshell's changes cannot affect the variable in the parent shell, of
course.

Some information about subshells can be found under [command
grouping](http://www.gnu.org/software/bash/manual/bash.html#Command-Grouping.html)
and [command execution
environment](http://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
in the Bash manual.

### Markup Answer as of Revision 8 (2017-12-17 06:30:00Z - Davis Herring)

Exported variables (such as `$HOME` and `$PATH`) are available to other
programs.
Regular (non-exported) variables are not available to other programs.

    $ env | grep '^variable='
    $                                 # No environment variable called variable
    $ variable=Hello                  # Create local (non-exported) variable with value
    $ env | grep '^variable='
    $                                 # Still no environment variable called variable
    $ export variable                 # Mark variable for export to child processes
    $ env | grep '^variable='
    variable=Hello
    $
    $ export other_variable=Goodbye   # create and initialize exported variable
    $ env | grep '^other_variable='
    other_variable=Goodbye
    $

For more information, see the entry for the [`export`
builtin](http://www.gnu.org/software/bash/manual/bash.html#index-export)
in the GNU Bash manual.

Note that non-exported variables will be available to subshells run via
`(...)` and similar notations:

    $ othervar=present
    $ (echo $othervar; echo $variable; variable=elephant; echo $variable)
    present
    Hello
    elephant
    $ echo $variable
    Hello
    $

The subshell cannot affect the variable in the parent shell, of course.

Some information about subshells can be found under [command
grouping](http://www.gnu.org/software/bash/manual/bash.html#Command-Grouping.html)
and [command execution
environment](http://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
in the Bash manual.

### Markup Answer as of Revision 7 (2017-12-17 06:30:00Z - Elliptical View)

Exported variables (such as `$HOME` and `$PATH`) are available to other
programs.
Regular (non-exported) variables are not available to other programs.

    $ env | grep '^variable='
    $                                 # No environment variable called variable
    $ variable=Hello                  # Create local (non-exported) variable with value
    $ env | grep '^variable='
    $                                 # Still no environment variable called variable
    $ export variable                 # Mark variable for export to child processes
    $ env | grep '^variable='
    variable=Hello
    $
    $ export other_variable=Goodbye   # create and initialize exported variable
    $ env | grep '^other_variable='
    other_variable=Goodbye
    $

For more information, see the entry for the [`export`
builtin](http://www.gnu.org/software/bash/manual/bash.html#index-export)
in the GNU Bash manual.

Note that non-exported variables will be available to subshells run via
`(...)` and similar notations:

    $ othervar=present
    $ (echo $othervar; echo $variable; variable=elephant; echo $variable)
    present
    Hello
    elephant
    $ echo $variable
    Goodbye
    $

The subshell cannot affect the variable in the parent shell, of course.

Some information about subshells can be found under [command
grouping](http://www.gnu.org/software/bash/manual/bash.html#Command-Grouping.html)
and [command execution
environment](http://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
in the Bash manual.

### Markup Answer as of Revision 6 (2015-04-26 19:43:06Z - JL)

Exported variables (such as `$HOME` and `$PATH`) are available to other
programs.  Regular (non-exported) variables are not available to other
programs.

    $ env | grep '^variable='
    $                                 # No environment variable called variable
    $ variable=Hello                  # Create local (non-exported) variable with value
    $ env | grep '^variable='
    $                                 # Still no environment variable called variable
    $ export variable                 # Mark variable for export to child processes
    $ env | grep '^variable='
    variable=Hello
    $
    $ export other_variable=Goodbye   # create and initialize exported variable
    $ env | grep '^other_variable='
    other_variable=Goodbye
    $

For more information, see the entry for the [`export`
builtin](http://www.gnu.org/software/bash/manual/bash.html#index-export)
in the GNU Bash manual.

Note that non-exported variables will be available to subshells run via
`(...)` and similar notations:

    $ othervar=present
    $ (echo $othervar; echo $variable; variable=elephant; echo $variable)
    present
    Goodbye
    elephant
    $ echo $variable
    Goodbye
    $

The subshell cannot affect the variable in the parent shell, of course.

Some information about subshells can be found under [command
grouping](http://www.gnu.org/software/bash/manual/bash.html#Command-Grouping.html)
and [command execution
environment](http://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
in the Bash manual.

### Markup Answer as of Revision 5 (2015-04-26 18:51:47Z - fedorqui)

Exported variables (such as `$HOME` and `$PATH`) are available to other
programs.
Regular (non-exported) variables are not available to other programs.

    $ env | grep '^variable='
    $                                 # No environment variable called variable

    $ variable=Hello                  # Create local (non-exported) variable with value
    $ env | grep '^variable='
    $                                 # Still no environment variable called variable

    $ export variable                 # Mark variable for export to child processes
    $ env | grep '^variable='
    variable=Hello

    $ export other_variable=Goodbye   # create and initialize exported variable
    $ env | grep '^other_variable='
    other_variable=Goodbye

For more information, see the entry for the [`export`
builtin](http://www.gnu.org/software/bash/manual/bash.html#index-export)
in the GNU Bash manual.

Note that non-exported variables will be available to subshells run via
`(...)` and similar notations:

    $ othervar=present
    $ (echo $othervar; echo $variable; variable=elephant; echo $variable)
    present
    Goodbye
    elephant
    $ echo $variable
    Goodbye
    $

The subshell cannot affect the variable in the parent shell, of course.

Some information about subshells can be found under [command
grouping](http://www.gnu.org/software/bash/manual/bash.html#Command-Grouping.html)
and [command execution
environment](http://www.gnu.org/software/bash/manual/bash.html#Command-Execution-Environment)
in the Bash manual.

### Markup Answer as of Revision 4 (2015-04-26 17:48:01Z - JL)
### Markup Answer as of Revision 3 (2015-02-26 23:11:10Z - JL)
### Markup Answer as of Revision 2 (2015-02-26 22:05:43Z - Victor Yarema)
### Markup Answer as of Revision 1 (2011-09-14 05:27:07Z - JL)
