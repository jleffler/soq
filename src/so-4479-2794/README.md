### Stack Overflow Question 4479-2794

[SO 4479-2794](https://stackoverflow.com/q/44792794) &mdash;
Transferring a directory through sockets

<hr>

This code is not really ready for GitHub.

<hr>

Why am I doing anything about this?
Because I'm stupid, that's why!

### Command line interface for cpd-server

    cpd-server [-dhvV][-p port][-l log]

    -d       Daemonize process
    -h       Print this help message and exit
    -l log   Record errors in log file
    -p port  Listen on this port (default 30991 - arbitrary)
    -v       Set verbose mode
    -V       Print version information and exit

### Command line interface for cpd-client

    cpd-client [-hV][-s host][-p port][-S source][-T target]

    -h         Print this help message and exit
    -l log     Record errors in log file
    -p port    Connect to cpd-server on this port (default 30991)
    -s host    Connect to cpd-server on this host (default localhost)
    -v         Set verbose mode
    -S source  Source directory (default .)
    -T target  Target directory (default - realpath for .)
    -V         Print version information and exit

<hr>

The question on SO has been deleted (so you need 10K to find it).
The OP ws not very reasonable in his attitude.

* `client-20170706.c`
* `server-20170706.c`

  This code corresponds more or less to what was provided by the OP, but
  some was gleaned from email sent to me.

* `cpd-client.c`
* `cpd-server.c`

  This code corresponds to the specification above.

The other code needed from the JLSS canon includes:

* `config.h` — this needs to be like the one from $HOME/lib/JL
* `cpd.h`
* `daemonize.c`
* `debug.h`
* `emalloc.c`
* `emalloc.h`
* `errhelp.c`
* `estrdup.c`
* `kludge.h`
* `mkpath.c`
* `mkpath.h`
* `posixver.h`
* `stderr.c`
* `stderr.h`
* `sysstat.h`
* `tcp_accept.c`
* `tcp_connect.c`
* `tcp_listen.c`
* `unp.h`
* `unpv13e.h`

The `.gitignore` file ignores the name `pater-familias` which was used
for testing.
