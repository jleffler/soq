### Stack Overflow Question 6557-1879

[SO 6557-1879](https://stackoverflow.com/q/65571879) &mdash;
Parse command output to a variable with file descriptors

### Question

I want to my program to execute md5sum command to generate a hash given
a file, and then storing the hash into an array (char *) variable.

I have read about popen(), but it's involving FILE * variables and I'd
like to use only file descriptors.

Is there any way to do this?

### Answer

As I noted in my
[comment](https://stackoverflow.com/questions/65571879/parse#comment115933451_65571879),
it is perfectly possible to implement the functionality of
[`popen()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/popen.html)
but have the function return a file descriptor instead of a file stream
like `popen()` does.  There isn't a standard library function for the
task.  You'll need to create a pipe and fork.  The child will do
plumbing so that the standard output of the command goes to the write
end of the pipe (and the read end is closed) and then executes the
command.  The parent will close the write end of the pipe, read the
response from the read end of the pipe, and close that.  It's not really
all that hard — it is mildly fiddly, that's all.

The code corresponding to `pclose()` is a bit trickier.  Should the code
wait for the child to die, or at least attempt to collect the zombie?
If so, how will it know which PID is appropriate wait for?  It is
tempting to just say "call `close()` with the returned file descriptor",
but that could leave zombies around.  Should it wait for the child to
die, or should it just collect the corpse if the child has died, leaving
it to other code to deal with the zombies?  The solution implemented in
the code below:

* Limits file descriptors to 128 (including standard I/O channels).
* Records the PID associated with a file descriptor in the fixed-size array `pids`.
* Waits on the child with either 0 (unconditional wait) or `WNOHANG`
  using
  [`waitpid()`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/waitpid.html)
  and the saved PID associated with the file descriptor.
* Reports the child status if the child has exited.
* Otherwise reports success — 0.

It would be feasible to alter the design so that the array of PID values
for each file descriptor is dynamically allocated.  You control whether
the `dpclose()` function waits for the child to exit or does not wait if
it has not already exited.

The code does no signal handling.  That is another layer of complication.

    /* SO 6557-1879 */

    /* #include "dpopen.h" */
    #ifndef DPOPEN_H_INCLUDED
    #define DPOPEN_H_INCLUDED

    #include <fcntl.h>      /* O_RDONLY or O_WRONLY for mode in dpopen() */
    #include <sys/wait.h>   /* WNOHANG for options in dpclose() */

    /* dpopen() - similar to popen(), but returning a file descriptor */
    /* The value in mode must be O_RDONLY or O_WRONLY */
    extern int dpopen(char *cmd, int mode);

    /* dpclose() - similar to pclose(), but working with a file descriptor returned by dpopen() */
    /* The value in options must be 0 or WNOHANG */
    /* The return value is the exit status of the child if available, 0 if not, or -1 if there is a problem */
    extern int dpclose(int fd, int options);

    #endif /* DPOPEN_H_INCLUDED */

    #include <assert.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <unistd.h>

    enum { MAX_PDOPEN_FD = 128 };
    static pid_t pids[MAX_PDOPEN_FD];

    int dpopen(char *cmd, int mode)
    {
        if (cmd == 0 || (mode != O_RDONLY && mode != O_WRONLY))
        {
            errno = EINVAL;
            return -1;
        }

        int fd[2];
        if (pipe(fd) != 0)
            return -1;

        /*
        ** Avoid embarrassment in debug builds if someone closed file
        ** descriptors too enthusiastically, and double check at run-time
        ** for non-debug builds.  In some ways, it isn't very necessary as a
        ** runtime check - the circumstances are implausible.  It is
        ** possible to code around fd[0] == STDIN_FILENO and fd[1] ==
        ** STDERR_FILENO, etc, but it is very messy to do so (having to
        ** avoid closing file descriptors, etc).  It is simpler to close the
        ** two new file descriptors and return -1 with errno set to EINVAL
        ** if they overlap with the standard I/O descriptors.  If this
        ** problem is detected, the program is already screwed up because at
        ** least one of standard input, standard output or standard error
        ** was closed.
        */
        assert(fd[0] > STDERR_FILENO && fd[1] > STDERR_FILENO);
        if (fd[0] <= STDERR_FILENO || fd[1] <= STDERR_FILENO)
        {
            close(fd[0]);
            close(fd[1]);
            errno = EINVAL;
            return -1;
        }
        if (fd[0] >= MAX_PDOPEN_FD || fd[1] >= MAX_PDOPEN_FD)
        {
            close(fd[0]);
            close(fd[1]);
            errno = EMFILE;
            return -1;
        }

        /*
        ** Prepare for forking - minimal step.  See SO 5011-0992
        ** (https://stackoverflow.com/q/50110992 and
        ** https://stackoverflow.com/a/50112169/): "Why does forking my
        ** process cause the file to be read infinitely?"
        ** See also SO 0297-9209 (https://stackoverflow.com/q/2979209 and
        ** https://stackoverflow.com/a/34247021) "Using fflush(stdin)",
        ** noting that Standard C and POSIX diverge somewhat; POSIX mandates
        ** behaviour that the C standard does not.  It would be possible to
        ** ensure standard input is 'clean' using code such as:
        **
        **     if (lseek(fileno(stdin), 0L, SEEK_CURR) >= 0)
        **         fflush(stdin);
        **
        ** Standard error is normally not a problem; by default, it is not
        ** fully buffered.
        */
        fflush(stdout);

        pid_t pid = fork();
        if (pid < 0)
        {
            close(fd[0]);
            close(fd[1]);
            return -1;
        }

        if (pid == 0)
        {
            /* Child */
            if (mode == O_RDONLY)
                dup2(fd[1], STDOUT_FILENO);
            else
                dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            char *argv[] = { "/bin/sh", "-c", cmd, 0 };
            execv(argv[0], argv);
            exit(EXIT_FAILURE);
        }

        /* Parent */
        if (mode == O_RDONLY)
        {
            close(fd[1]);
            pids[fd[0]] = pid;
            return fd[0];
        }
        else
        {
            close(fd[0]);
            pids[fd[1]] = pid;
            return fd[1];
        }
    }

    int dpclose(int fd, int options)
    {
        if (fd <= STDERR_FILENO || fd >= MAX_PDOPEN_FD || pids[fd] == 0 ||
            (options != 0 && options != WNOHANG))
        {
            errno = EINVAL;
            return -1;
        }
        if (close(fd) != 0)
            return -1;
        pid_t corpse;
        int status;
        pid_t child = pids[fd];
        pids[fd] = 0;
        if ((corpse = waitpid(child, &status, options)) == child)
            return status;
        return 0;
    }

    int main(void)
    {
        int fd1 = dpopen("ls -ltr", O_RDONLY);
        int fd2 = dpopen("cat > ls.out; sleep 10", O_WRONLY);

        if (fd1 < 0 || fd2 < 0)
        {
            fprintf(stderr, "failed to create child processes\n");
            exit(EXIT_FAILURE);
        }

        char buffer[256];
        ssize_t rbytes;
        while ((rbytes = read(fd1, buffer, sizeof(buffer))) > 0)
        {
            ssize_t wbytes = write(fd2, buffer, rbytes);
            if (wbytes != rbytes)
            {
                fprintf(stderr, "Failed to write data\n");
                close(fd1);
                close(fd2);
                exit(EXIT_FAILURE);
            }
        }

        if (dpclose(fd1, WNOHANG) < 0 || dpclose(fd2, 0) < 0)
        {
            fprintf(stderr, "failed to close pipes correctly\n");
            exit(EXIT_FAILURE);
        }

        return 0;
    }


* See also [Why does forking my process cause the file to be read infinitely?](https://stackoverflow.com/q/50110992) and
my [answer](https://stackoverflow.com/a/50112169/).
* See also [Using `fflush(stdin)`](https://stackoverflow.com/q/2979209) and
my [answer](https://stackoverflow.com/a/34247021), noting also the information in SO 5011-0992.

