### Stack Overflow Question 7113-2499

[SO 7113-2499](https://stackoverflow.com/q/71132499) &mdash;
SIGINFO&#39;s si_pid sets itself to 0 after a few calls of the same function

### Diagnosis

Most of the time, when I was testing on a MacBook Pro running Big Sur 11.6.3, the commands run to completion.  I'm using a program `tester` to run the server and then the client — the advantage of the program is that I can report the exit statuses of the client and server programs accurately.  I've been using increasingly elaborate test rigs to capture the information.

Every so often, I seem to get the server dying immediately.  I believe that's a **timing issue** due to the o/s scheduler.  The launch code runs the client after launching the server, but it so happens that the system scheduler runs the client before the server has set up its signal handler and so the server is killed by the client's initial signal.

### Supporting Evidence

I modified both the client and server programs to include `alarm(15);`
so that the processes time out after 15 seconds.  Most of the time, it
takes the pair less than a second to complete.  On those occasions when
things fail, I get the server exiting with status 0x001E (which
indicates it died from a SIGUSR1 signal) and on the same runs, the
client exits 15 seconds later with status 0x000E (which indicates it
died from a SIGALRM signal).  The log files contain no '`received`"
messages.

```none
$ rmk && timecmd -m -- ./tester | tpipe -sx "grep -c -e '^C received'" "grep -c -e '^S received'" "grep -E -e 'PID =|^Child|(Server|Client) PID'"  "cat > log.$(isodate -c)"
2022-02-15 14:25:07.172 [PID 10210] ./tester
tpipe: + grep -c -e '^C received'
tpipe: + grep -c -e '^S received'
tpipe: + grep -E -e 'PID =|^Child|(Server|Client) PID'
tpipe: + cat > log.20220215.142507
Server PID: 10211
Client PID: 10212
10212: sent signal to PID = 10211
Child 10211 exited with status 0x001E
Child 10212 exited with status 0x000E
2022-02-15 14:25:22.193 [PID 10210; status 0x0000]  -  15.021s
0
0
$
```

The status message for 10211 appeared almost immediately; that for 10212
waited for just over 15 seconds.  The two zeros are from the `grep -c`
commands — there were no interesting messages.

For contrast, the prior run showed:
```none
$ rmk && timecmd -m -- ./tester | tpipe -sx "grep -c -e '^C received'" "grep -c -e '^S received'" "grep -E -e 'PID =|^Child|(Server|Client) PID'"  "cat > log.$(isodate -c)"
2022-02-15 14:25:05.965 [PID 10196] ./tester
tpipe: + grep -c -e '^C received'
tpipe: + grep -c -e '^S received'
tpipe: + grep -E -e 'PID =|^Child|(Server|Client) PID'
tpipe: + cat > log.20220215.142505
Server PID: 10197
Client PID: 10198
PID = 10197
10198: sent signal to PID = 10197
Child 10197 exited with status 0x0000
Child 10198 exited with status 0x0000
2022-02-15 14:25:06.481 [PID 10196; status 0x0000]  -  0.515s
5000
5000
$
```
The 5000 entries here are the counts from the `grep -c` commands run via
the `tpipe` program.  (The `rmk` is a variant of `make`; `tpipe` is a
program a bit like `tee` except it writes to processes rather than files
(see also the unfortunately named
[`pee`](https://www.putorius.net/linux-pee-command-tee-standard-input-into-pipes.html)
program); `isodate` prints the date in a compressed ISO 8601 format such
as `20220215.142505`; `timecmd -m` executes a command and times it to
milliseconds, reporting the command and the status, etc.)

I've not logged a case where `info->si_pid == 0`, nor a case where
there's a problem after some intermediate number of signal exchanges —
it's been 0 or 5000 and no other value.  Consequently, I may not have
accurately reproduced your scenario.

Using a shell script to launch the server and then the client didn't
reproduce the premature signal — the delays inherent in processing a
shell script seem to be just enough to allow the server to set up its
signal processing before the client sends the initial signal.

Script tested:

    time=$(isodate -c)
    server > server.$time.log &
    client $! > client.$time.log

### Modified Code

JFTR, here's my revised code.  It uses some code that is available in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository on GitHub as files `stderr.c` and `stderr.h` in the
[src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.

### `client.c`
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "stderr.h"

static void ft_send_signal(int pid)
{
    if (kill(pid, SIGUSR1) != 0)
        err_syserr("failed to send initial signal to PID %d: ", pid);
    printf("%d: sent signal to PID = %d\n", getpid(), pid);
    fflush(stdout);
}

static void ft_signal_handler(int sig, siginfo_t *info, void *context)
{
    static int  i = 0;

    (void)context;
    if (sig == SIGUSR1)
    {
        printf("C received - %d PID: %d\n", i, info->si_pid);
        fflush(stdout);
        i++;
        if (info->si_pid != 0)
        {
            if (kill(info->si_pid, SIGUSR1) != 0)
                err_syserr("failed to send signal to PID %d: ", info->si_pid);
        }
        else
            err_error("info->si_pid == 0 at iteration %d\n", i);
        if (i == 5000)
            exit(EXIT_SUCCESS);
    }
}

int main(int ac, char **av)
{
    err_setarg0("client");
    struct sigaction    action;
    sigset_t            set;

    if (ac != 2)
        err_usage("PID");

    alarm(15);
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = ft_signal_handler;
    action.sa_mask = set;
    sigaction(SIGUSR1, &action, NULL);
    ft_send_signal(atoi(av[1]));
    while(1)
        pause();
    return (0);
}
```

### `server.c`
```c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stderr.h"

static void ft_respond(int sig, siginfo_t *info, void *context)
{
    static int  i = 0;
    (void)context;
    if (sig == SIGUSR1)
    {
        i++;
        printf("S received - %d PID: %d\n", i, info->si_pid);
        fflush(stdout);
        if (info->si_pid != 0)
        {
            if (kill(info->si_pid, SIGUSR1) != 0)
                err_syserr("failed to send signal to PID %d: ", info->si_pid);
        }
        else
            err_error("info->si_pid == 0 at iteration %d\n", i);
        if (i == 5000)
            exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    err_setarg0("server");
    struct sigaction    reaction;

    sigemptyset(&reaction.sa_mask);
    alarm(15);
    reaction.sa_flags = SA_SIGINFO;
    reaction.sa_sigaction = ft_respond;
    sigaction(SIGUSR1, &reaction, NULL);
    printf("PID = %d\n", getpid());
    fflush(stdout);
    while (1)
        pause();
    return(0);
}
```

### `tester.c`
```c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "stderr.h"

int main(void)
{
    err_setarg0("tester");
    alarm(20);
    pid_t server = fork();
    if (server < 0)
        err_syserr("failed to fork for server: ");
    if (server == 0)
    {
        char *args[] = { "./server", 0 };
        execv(args[0], args);
        err_syserr("failed to exec server: ");
    }
    printf("Server PID: %d\n", server);
    fflush(stdout);

    pid_t client = fork();
    if (client < 0)
        err_syserr("failed to fork for client: ");
    if (client == 0)
    {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%d", server);
        char *argc[] = { "./client", buffer, 0 };
        execv(argc[0], argc);
        err_syserr("failed to exec client: ");
    }
    printf("Client PID: %d\n", client);
    fflush(stdout);

    int corpse;
    int status;
    while ((corpse = wait(&status)) > 0)
    {
        printf("Child %d exited with status 0x%.4X\n", corpse, status);
        fflush(stdout);
    }

    return 0;
}
```
## Prescription

I'm not sure that there's a good way to fix this other than adding a
call to the client code to delay it from sending the initial signal for
some significant time — a millisecond or two would probably be
sufficient.  This delay would mean that the server has time to set up
its signal handling.  Equivalently, the `tester` program could add a
delay between launching the server and the client.

Why no problem on Linux?  Luck?  Or the o/s scheduler doesn't run the
second child of `tester` before the first child, so the server always
gets to set up its signal handling before the client sends the first
signal.

