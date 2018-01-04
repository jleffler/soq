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

