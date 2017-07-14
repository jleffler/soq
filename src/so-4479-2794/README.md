### Stack Overflow Question 4479-2794

[SO 4479-2794](http://stackoverflow.com/q/44792794) &mdash;
Transferring a directory through sockets

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

