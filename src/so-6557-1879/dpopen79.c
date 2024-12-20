/* SO 6557-1879 */
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* #include "dpopen.h" */
/* Goes in a header */
#ifndef DPOPEN_H_INCLUDED
#define DPOPEN_H_INCLUDED

#include <fcntl.h>  /* O_RDONLY or O_WRONLY for mode */

/* dpopen() - similar to popen(), but it returns a file descriptor */
/* Close the returned file descriptor with close() */
extern int dpopen(char *cmd, int mode);

#endif /* DPOPEN_H_INCLUDED */

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
        return fd[0];
    }
    else
    {
        close(fd[0]);
        return fd[1];
    }
}

int main(void)
{
    int fd1 = dpopen("ls -l", O_RDONLY);
    int fd2 = dpopen("cat > ls.out", O_WRONLY);

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
    close(fd1);
    close(fd2);
    return 0;
}
