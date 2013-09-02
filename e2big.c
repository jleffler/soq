/* SO 18559403: How big an argument list is allowed */

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;  /* Sometimes in <unistd.h> */

enum { BYTES_PER_KIBIBYTE = 1024 };
enum { BYTES_PER_MEBIBYTE = BYTES_PER_KIBIBYTE * BYTES_PER_KIBIBYTE };
enum { E_GOT_E2BIG =  37 };
enum { E_NOT_E2BIG = 219 };

enum { R_TOO_LARGE = +1, R_TOO_SMALL = -1 };

static char *print_kib(int size, char *buffer, size_t buflen)
{
    snprintf(buffer, buflen, "%d (%d KiB)", size, size / BYTES_PER_KIBIBYTE);
    return buffer;
}

static int test_arg_size(int size)
{
    char buffer[32];
    int result = R_TOO_SMALL;
    assert(size % 8 == 0);
    fflush(0);
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork at size %s\n",
                print_kib(size, buffer, sizeof(buffer)));
        exit(1);
    }
    else if (pid == 0)
    {
        int self = getpid();
        printf("Child: %d\n", self);
        char *args[10] = { "ls" };
        size_t bytes_per_arg = size / 8;
        for (int j = 1; j < 9; j++)
        {
            args[j] = malloc(bytes_per_arg);
            if (args[j] == 0)
            {
                fprintf(stderr, "Failed to allocate argument space at size %s\n",
                        print_kib(size, buffer, sizeof(buffer)));
                exit(E_NOT_E2BIG);
            }
            memset(args[j], j + '0', bytes_per_arg - 1);
            args[j][bytes_per_arg - 1] = '\0';
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
            fprintf(stderr, "%d: got E2BIG (%d: %s) at size %s\n", self, errnum, strerror(errnum),
                    print_kib(size, buffer, sizeof(buffer)));
            exit(E_GOT_E2BIG);
        }
        fprintf(stderr, "%d: got errno %d (%s) at size %s\n", self, errnum, strerror(errnum),
                print_kib(size, buffer, sizeof(buffer)));
        exit(E_NOT_E2BIG);
    }
    else
    {
        int self = getpid();
        int corpse;
        int status;
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
                    result = R_TOO_LARGE;
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
            printf(" at size %s\n", print_kib(size, buffer, sizeof(buffer)));
            fflush(stdout);
        }
    }
    return result;
}

static int env_size(void)
{
    int size = 0;
    for (char **ep = environ; *ep != 0; ep++)
        size += strlen(*ep) + 1;
    return size;
}

int main(void)
{
    int env = env_size();
    int lo = 0;
    int hi = BYTES_PER_MEBIBYTE;

    /* Binary search -- the kilobyte slop means termination does not have to be accurate */
    while (lo + 1 * BYTES_PER_KIBIBYTE < hi)
    {
        int mid = (lo + hi) / 2;
        if (test_arg_size(mid) == R_TOO_LARGE)
            hi = mid;
        else
            lo = mid;
    }

    char buffer1[32];
    char buffer2[32];
    printf("Environment size = %d\n", env);
    printf("Best guess: maximum argument size in range %s to %s\n",
           print_kib(lo + env, buffer1, sizeof(buffer1)),
           print_kib(hi + env, buffer2, sizeof(buffer2)));

    return 0;
}
