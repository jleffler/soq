### Stack Overflow Question 7020-7788

[SO 7020-7788](https://stackoverflow.com/q/70207788) &mdash;
Create a child for each file and pipe to parent

I'm trying to do a homework where I need to count the lines, words and
characters of n files.

Each file in the list must be processed (counted) by a distinct process.
The hierarchical relationship between processes must be such that the
i+1 process is created by the process i;

Example:
```none
 PID    PPID
child1 parent1 File1 l=2 w=5 c=20
child2 child1  File2 l=3 w=6 c=30

Total:               l=5 w=11 c=50
```
Each process sends the numbers to the parent with a pipe and the parent
will sum them in 3 different variables (totLines, totWords, totChars).

The problem is here, this 3 variables will reset to 0 in each fork() so
my total will only show the last numbers sent to the pipe (Total: l=3
w=6 c=30) and I can't find a solution to this.  I think the problem is
on the break; of the parent; when I remove it the sum works but the
program will repeat the prints 3/4 times.

### Answer


As I noted in a
[comment](https://stackoverflow.com/questions/70207788/create#comment124109650_70207788),
given that the parent can only read from pipes it creates, the transfer
of information from a child of a child of a child (as required by the
"hierarchical relationship between processes must be such that the i+1
process is created by the process i" requirement) means that only one
pipe is in use.

Further, the initial process has no sensible way of determining the PID
of any process except its immediate child.  Therefore, more information
must be passed back from the children.  The children can all use the
same pipe as long as the data written per child is small enough and
written in a single operation and the size can be determined.  Since the
parental code must print the file name, PID and PPID, it seems
reasonable to pass 6 data items back to the parent:

1. File number
2. PID
3. PPID
4. Line count
5. Word count
6. Byte count

These observations lead me to write this code — which substantially
ignores what you have so far.  Note that I use my preferred error
reporting code, which is available in my
[SOQ](https://github.com/jleffler/soq) (Stack Overflow Questions)
repository on GitHub as files `stderr.c` and `stderr.h` in the
[src/libsoq](https://github.com/jleffler/soq/tree/master/src/libsoq)
sub-directory.

There's one sneaky twist in the code — the use of the
`random_children()` function to generate a random number of processes so
that the PID values do not (in general) increment monotonically by 1.
You'd probably want to leave that out.

Note that the output format leaves the most variable bit — the file
name — at the end of the line rather than embedding it in the middle.
It would be feasible to find the length of the longest name and format
the file name after the two PID value and before the counts — consider
it an exercise for the reader.

### `pipe83.c`

```c
/* SO 7020-7788 */
/*
** Count the lines, words and characters of n files.
**
** - Each file in the list must be processed (counted) by a distinct
**   process;
** - The hierarchical relationship between processes must be such that
**   the i+1 process is created by the process i;
**
** Example:
**
**  PID    PPID
** child1 parent1 File1 l=2 w=5 c=20
** child2 child1  File2 l=3 w=6 c=30
**
** Total:               l=5 w=11 c=50
**
** Each process sends the numbers to the parent with a pipe and the
** parent will sum them in 3 different variables.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "stderr.h"

static void count_file(const char *file, int counts[3])
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
        err_syserr("failed to open file '%s' for reading: ", file);
    int lines =0;
    int words = 0;
    int bytes = 0;
    int in_word = 0;
    int c;
    while ((c = getc(fp)) != EOF)
    {
        bytes++;
        if (c == '\n')
            lines++;
        if (isspace(c))
        {
            in_word = 0;
        }
        else
        {
            if (!in_word)
                words++;
            in_word = 1;
        }
    }
    counts[0] = lines;
    counts[1] = words;
    counts[2] = bytes;
    fclose(fp);
}

static void random_children(void)
{
    srand(getpid());
    int n = rand() % 10;
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
            err_syserr("failed to fork: ");
        if (pid == 0)
            exit(EXIT_SUCCESS);
    }
}

static void child_at_work(int fd, int argc, char **argv, int n)
{
    int data[6] = { n, getpid(), getppid(), 0, 0, 0 };
    random_children();
    count_file(argv[n], &data[3]);
    if (write(fd, data, sizeof(data)) != sizeof(data))
        err_syserr("failed to write data to pipe: ");
    if (n >= argc - 1)
        exit(0);
    pid_t pid = fork();
    if (pid < 0)
        err_syserr("failed to fork: ");
    if (pid == 0)
        child_at_work(fd, argc, argv, n + 1);
    close(fd);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    err_setarg0(argv[0]);
    if (argc < 2)
        err_usage("file [...]");

    int p[2];
    if (pipe(p) != 0)
        err_syserr("failed to create pipe: ");

    pid_t pid = fork();
    if (pid < 0)
        err_syserr("failed to fork: ");
    if (pid == 0)
    {
        err_setlogopts(ERR_LOG|ERR_MILLI);
        close(p[0]);
        child_at_work(p[1], argc, argv, 1);
        err_error("function child_at_work() returned unexpectedly\n");
    }

    close(p[1]);

    int data[6];
    /*
    ** 0 = file number
    ** 1 = PID
    ** 2 = PPID
    ** 3 = lines
    ** 4 = words
    ** 5 = bytes
    */

    int lines = 0;
    int words = 0;
    int bytes = 0;
    printf("%5s  %5s\n", "PID", "PPID");
    while (read(p[0], data, sizeof(data)) == sizeof(data))
    {
        lines += data[3];
        words += data[4];
        bytes += data[5];
        printf("%5d  %5d  l=%5d w=%5d c=%5d  %s\n",
               data[1], data[2], data[3], data[4], data[5], argv[data[0]]);
    }

    printf("%-14.14sl=%5d w=%5d c=%5d\n", "Total:", lines, words, bytes);
    close(p[0]);

    return 0;
}
```

Running that on the C files in my 'Stack Overflow Questions' directory yields:

```none
$ pipe83 *.c
  PID   PPID
56980  56979  l=   97 w=  251 c= 2206  checkeuid.c
56981  56980  l=   17 w=   55 c=  480  ex97.c
56989  56981  l=   36 w=  119 c=  752  fgets_delim67.c
56993  56989  l=   29 w=   61 c=  532  glob61.c
56995  56993  l=   35 w=  127 c=  993  lcs47.c
57001  56995  l=  195 w=  577 c= 4784  pipe13.c
57009  57001  l=   98 w=  322 c= 2906  pipe43.c
57013  57009  l=  143 w=  447 c= 3213  pipe83.c
57015  57013  l=   12 w=   36 c=  256  pragma83.c
57021  57015  l=   23 w=   66 c=  670  pth43.c
57029  57021  l=   41 w=  115 c=  908  rd83.c
57033  57029  l=  134 w=  460 c= 3461  revdigits.c
57035  57033  l=   34 w=  101 c=  593  rot71.c
57041  57035  l=   32 w=  115 c= 1076  scan13.c
57049  57041  l=   51 w=  131 c= 1033  scan67.c
57053  57049  l=   88 w=  297 c= 2946  sigcont17.c
57055  57053  l=   65 w=  139 c= 1732  sigcont31.c
57061  57055  l=   51 w=  148 c= 1384  sigcont43.c
57069  57061  l=  101 w=  194 c= 2383  so-6886-8740-1.c
57073  57069  l=   84 w=  257 c= 1938  test-strsep.c
Total:        l= 1366 w= 4018 c=34246
$ wc *.c
      97     251    2206 checkeuid.c
      17      55     480 ex97.c
      36     119     752 fgets_delim67.c
      29      61     532 glob61.c
      35     127     993 lcs47.c
     195     577    4784 pipe13.c
      98     322    2906 pipe43.c
     143     447    3213 pipe83.c
      12      36     256 pragma83.c
      23      66     670 pth43.c
      41     115     908 rd83.c
     134     460    3461 revdigits.c
      34     101     593 rot71.c
      32     115    1076 scan13.c
      51     131    1033 scan67.c
      88     297    2946 sigcont17.c
      65     139    1732 sigcont31.c
      51     148    1384 sigcont43.c
     101     194    2383 so-6886-8740-1.c
      84     257    1938 test-strsep.c
    1366    4018   34246 total
$
```

