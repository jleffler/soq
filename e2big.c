#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

enum { BYTES_PER_KIBIBYTE = 1024 };
enum { BYTES_PER_MEBIBYTE = BYTES_PER_KIBIBYTE * BYTES_PER_KIBIBYTE };
enum { E_GOT_E2BIG =  37 };
enum { E_NOT_E2BIG = 219 };

static void sigchld_handler(int signum)
{
    signal(signum, sigchld_handler);
}

int main(void)
{
    signal(SIGCHLD, sigchld_handler);
    for (int i = 4 * BYTES_PER_KIBIBYTE; i < BYTES_PER_MEBIBYTE; i *= 2)
    {
        fflush(0);
        pid_t pid = fork();
        if (pid < 0)
        {
            fprintf(stderr, "Failed to fork at %d\n", i);
            return 1;
        }
        else if (pid == 0)
        {
            int self = getpid();
            printf("Child: %d\n", self);
            char *args[10] = { "ls" };
            size_t bytes_per_arg = i / 8;
            for (int j = 1; j < 9; j++)
            {
                args[j] = malloc(bytes_per_arg + 1);
                if (args[j] == 0)
                {
                    fprintf(stderr, "Failed to allocate argument space at size %d\n", i);
                    exit(E_NOT_E2BIG);
                }
                memset(args[j], i + '0', bytes_per_arg);
                args[j][bytes_per_arg] = '\0';
            }

            /* Close standard I/O channels so executed command doesn't spew forth */
            int dev_null = open("/dev/null", O_RDWR);
            if (dev_null < 0)
            {
                fprintf(stderr, "Failed to open /dev/null for reading and writing\n");
                exit(E_NOT_E2BIG);
            }
            int dev_stderr = dup(2);
            if (dev_stderr < 0)
            {
                fprintf(stderr, "Failed to dup() standard error\n");
                exit(E_NOT_E2BIG);
            }
            close(0);
            dup(dev_null);
            close(1);
            dup(dev_null);
            close(2);
            dup(dev_null);
            close(dev_null);

            /* Execute ls on big file names -- error is ENAMETOOLONG */
            execvp(args[0], args);

            /* Reinstate standard error so we can report failure */
            dup2(dev_stderr, 2);
            int errnum = errno;
            if (errnum == E2BIG)
            {
                fprintf(stderr, "%d: got E2BIG (%d: %s) at size %d\n", self, errnum, strerror(errnum), i);
                exit(E_GOT_E2BIG);
            }
            fprintf(stderr, "%d: got errno %d (%s) at size %d\n", self, errnum, strerror(errnum), i);
            exit(E_NOT_E2BIG);
        }
        else
        {
            int self = getpid();
            int corpse;
            int status;
            int exit_loop = 0;
            while ((corpse = waitpid(pid, &status, 0)) != -1)
            {
                if (!WIFEXITED(status))
                    printf("%d: child %d died with exit status 0x%.4X", self, corpse, status);
                else
                {
                    int statval = WEXITSTATUS(status);
                    printf("%d: child %d died with exit status %d: ", self, corpse, statval);
                    switch (statval)
                    {
                    case E_GOT_E2BIG:
                        printf("success: got E2BIG");
                        exit_loop = 1;
                        break;
                    case E_NOT_E2BIG:
                        printf("failed: indeterminate error in child");
                        break;
                    case 1:
                        printf("command exited with status 1 - it worked");
                        break;
                    default:
                        printf("unknown: unexpected exit status %d", statval);
                        break;
                    }
                }
                printf(" at size %d (%d KiB)\n", i, i / BYTES_PER_KIBIBYTE);
                fflush(stdout);
            }
            if (exit_loop)
                break;
        }
    }
    return 0;
}
