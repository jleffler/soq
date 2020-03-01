# Packages

This directory contains some packages that I've created under different VCS systems than Git.
They're release tar files, usually.

### `daemonize`

The code for a program that, like programs such as `nice` or `sudo` or
`nohup`, changes some properties before running another program
specified on the command line.

In this case, it runs the program as a daemon, whether the process was
expecting it or not.

    daemonize: DAEMONIZE Version 1.10 (2015-02-15 17:33:13)

    Usage: daemonize [-abchptxV][-d dir][-e err][-i in][-o out][-P pidfile][-s sigs][-k fds][-m umask] command [args...]
      -V          print version and exit
      -a          output files in append mode (O_APPEND)
      -b          both output and error go to output file
      -c          create output files (O_CREAT)
      -d dir      change to given directory
      -e file     error file (standard error - /dev/null)
      -h          print help and exit
      -i file     input file (standard input - /dev/null)
      -k fd-list  keep file descriptors listed open
      -m umask    set umask (octal)
      -o file     output file (standard output - /dev/null)
      -p          print daemon PID on original stdout
      -P file     write PID and newline of continuing process to file
      -s sig-list ignore signal numbers
      -t          truncate output files (O_TRUNC)
      -x          output files must be new (O_EXCL)

See SO 0028-5015 — [Linux: Prevent a background process from being stopped after closing SSH client](https://stackoverflow.com/questions/285015/linux-prevent-a-background-process-from-being-stopped-after-closing-ssh-client/285109#285109).

The release has a SHA2-256 checksum and size as shown:

    SHA-256 232eb3623f3a51c79ac479503eb19f28dee70ba65d64a08d98bc4656c19bdee5    25882 daemonize-1.10.tgz

### `newgid`

Code for a program that changes the principal (real and effective) GID to a new value.
It isn't often needed these day, but it is occasionally useful.

It must be installed SUID `root`; if it isn't, it will witter:

    
    newgid: not SUID root -- check permissions

If invoked with no arguments, it gives the usage information:

    Usage: newgid [-V] [-] group [shell args]

The `-V` option prints the version number (1.10).  The `-` invokes a login shell.

See SO — [How do you use `newgrp` in a script then stay in that group when the script exits?](https://stackoverflow.com/questions/299728/how-do-you-use-newgrp-in-a-script-then-stay-in-that-group-when-the-script-exits)

The release has a SHA2-256 checksum and size as shown:

    SHA-256 d116d9e85c77826c1fd3ff4d18c56c311a6295c8247f83686cd7e8805963220f    28953 newgid-1.10.tgz

### `utf8-unicode`

The code for `utf8-unicode` which processes named files or standard
input as UTF-8 and prints the sequence of bytes that make up a single
character and the Unicode character it corresponds to.

For example:

    $ echo "grep –i where | wc -l" | utf8-unicode
    0x67 = U+0067
    0x72 = U+0072
    0x65 = U+0065
    0x70 = U+0070
    0x20 = U+0020
    0xE2 0x80 0x93 = U+2013
    0x69 = U+0069
    0x20 = U+0020
    0x77 = U+0077
    0x68 = U+0068
    0x65 = U+0065
    0x72 = U+0072
    0x65 = U+0065
    0x20 = U+0020
    0x7C = U+007C
    0x20 = U+0020
    0x77 = U+0077
    0x63 = U+0063
    0x20 = U+0020
    0x2D = U+002D
    0x6C = U+006C
    $

The Unicode EN DASH U+2013 was why that `grep` command was failing with
an error about being unable to find the file `where`.

### `timecmd`

The code for `timecmd` which measures elapsed time of commands specified as part of its command line.

    Usage: timecmd [-bhoqrsV][-m|-u|-n] [-d fd] [--] cmd [arg ...]

      -b     Do not print beginning information
      -d fd  Print information to file descriptor fd (default: 2, stderr)
      -h     Print this help message and exit
      -m     Print elapsed time with milliseconds
      -n     Print elapsed time with nanoseconds
      -o     Only print command name and non-option arguments
      -q     Only print command name (not arguments)
      -r     Repeat command after total time
      -s     Print elapsed time in seconds (not hours, minutes, seconds)
      -u     Print elapsed time with microseconds
      -V     Print version information and exit

Example uses:

    $  timecmd -m sleep 65
    2020-03-01 08:42:58.079 [PID 16916] sleep 65
    2020-03-01 08:44:03.086 [PID 16916; status 0x0000]  -  1m 5.007s
    $ timecmd -b -m sleep 65
    2020-03-01 12:22:54.646 [PID 18761; status 0x0000]  -  1m 5.007s
    $

    $ timecmd -u fast89
    2020-03-01 07:58:41.032007 [PID 14566] fast89
    2020-03-01 07:58:41.043518 [PID 14566; status 0x0000]  -  0.011511s
    $ timecmd -u slow61
    2020-03-01 07:58:41.053114 [PID 14568] slow61
    2020-03-01 07:58:41.128938 [PID 14568; status 0x0000]  -  0.075824s
    $ timecmd -u slow11
    2020-03-01 07:58:41.136826 [PID 14570] slow11
    2020-03-01 07:58:44.971013 [PID 14570; status 0x0000]  -  3.834187s
    $

The sample commands all produced no output.  It works fine with commands that do.

Jonathan Leffler (jonathan.leffler@gmail.com)
Sunday 1st March 2020
