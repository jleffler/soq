SO 367309: Which command line commands style do you prefer?

Vote up the one you like best! Use comments to justify your choice.

As I know there are two types of command line commands.  If you can
think of another one, post an example (as a community-wiki answer).

Originally asked 2008-12-15 02:02 by FerranB, but subsequently closed.
A pity since the answers were far better than the question (and mine was
the accepted answer, with 7 up-votes).

Now transferred to:
SO 1081-8443: Short/long options with option argument -- Is this some sort of convention?
SO 2160083:  What is the general syntax of a Unix shell command?

My answer (in MarkDown):

How many different types of options do you recognize?  I can think of
many, including:

* Single-letter options preceded by single dash, groupable when there is
  no argument, argument can be attached to option letter or in next
  argument (many, many Unix commands; most POSIX commands).
* Single-letter options preceded by single dash, grouping not allowed,
  arguments must be attached (RCS).
* Single-letter options preceded by single dash, grouping not allowed,
  arguments must be separate (pre-POSIX SCCS, IIRC).  
  <sup>_It appears this is a mis-remembrance; arguments in SCCS needed
  to be attached to the option letter in general
  (e.g. `sccs delta -y'Because I said so' file.c`)._</sup>
* Multi-letter options preceded by single dash, arguments may be
  attached or in next argument (X11 programs).
* Multi-letter options preceded by single dash, may be abbreviated
  (Atria Clearcase).
* Multi-letter options preceded by single plus (obsolete).
* Multi-letter options preceded by double dash; arguments may follow '='
  or be separate (GNU utilities).
* Options without prefix/suffix, some names have abbreviations or are
  implied, arguments must be separate.  ([AmigaOS
  Shell](http://www.amigahistory.co.uk/command.html))

Options taking an optional argument sometimes must be attached,
sometimes must follow an '=' sign.  POSIX doesn't support optional
arguments meaningfully (the POSIX getopt() only allows them for the last
option on the command line).

All sensible option systems use an option consisting of double-dash
('`--`') alone to mean "end of options" - the following arguments are
"non-option arguments" (usually file names) even if they start with a
dash.  (I regard supporting this notation as an imperative.)
Note, however, that if `-a` takes an argument, writing `somecmd -a --
-x` uses the `--` as the argument to `-a`, not as the end of options, so
the `-x` will also be interpreted by `somecmd`.

Many but not all programs accept single dash as a file name to mean
standard input (usually) or standard output (occasionally).  Sometimes,
as with GNU '`tar`', both can be used in a single command line:

    tar -cf - -F - | ...

The first solo dash means 'write to stdout'; the second means 'read file
names from stdin'.

Some programs use other conventions - that is, options not preceded by a
dash.  Many of these are from the oldest days of Unix.  For example,
'tar' and 'ar' both accept options without a dash, so:

    tar cvzf /tmp/somefile.tgz some/directory

The `dd` command uses `opt=value` exclusively:

    dd if=/some/file of=/another/file bs=16k count=200

Some programs allow you to interleave options and other arguments
completely; the C compiler, make and the GNU utilities run without
POSIXLY_CORRECT in the environment are examples.  Many programs expect
the options to precede the other arguments.

<hr>

I don't have strong preferences between the different systems.  When
there are few enough options, then single letters with mnemonic value
are convenient.  GNU supports this, but recommends backing it up with
multi-letter options preceded by a double-dash.

There are some things I do object to.  One of the worst is the same
option letter being used with different meanings depending on what other
option letters have preceded it.  In my book, that's a no-no, but I know
of software where it is done.

Another objectionable behaviour is inconsistency in style of handling
arguments (especially for a single program, but also within a suite of
programs).  Either require attached arguments or require detached
arguments (or allow either), but do not have some options requiring an
attached argument and others requiring a detached argument.  And be
consistent about whether '`=`' may be used to separate the option and
the argument.

As with many, many (software-related) things - consistency is more
important than the individual decisions.

---

Whatever you do, please, read the [TAOUP's Command-Line Options][1] and
consider [Standards for Command Line Interfaces][2].  (*Added by J F
Sebastian - thanks; I agree.*)


  [1]: http://catb.org/~esr/writings/taoup/html/ch10s05.html
  [2]: http://www.gnu.org/prep/standards/html_node/Command_002dLine-Interfaces.html
