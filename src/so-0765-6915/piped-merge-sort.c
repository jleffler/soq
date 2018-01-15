#include "posixver.h"
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* Error reporting */
static void err_vremark(char *fmt, va_list args)
{
    char buffer[256];
    int errnum = errno;
    int buflen = snprintf(buffer, sizeof(buffer), "%d: ", (int)getpid());
    buflen += vsnprintf(buffer + buflen, sizeof(buffer) - buflen, fmt, args);
    if (errnum != 0)
        buflen += snprintf(buffer + buflen, sizeof(buffer) - buflen,
                           ": errno = %d (%s)", errnum, strerror(errnum));
    fprintf(stderr, "%s\n", buffer);
}

static void err_error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vremark(fmt, args);
    va_end(args);
    exit(1);
}

static void err_remark(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    err_vremark(fmt, args);
    va_end(args);
}

enum { READ = 0 };
enum { WRITE = 1 };
enum { BUFFER_SIZE = 256 };

static int *a_data = 0;
static int  a_used = 0;
static int  a_size = 0;

void readFile(char const *fileName);
void freeMem(void);
void sortArray(void);
int  intcmp(void const *n1, void const *n2);

static void sortMergeFiles(int fd, int number, char **names);
static void sortOneFile(int fd, const char *file);
static void convertToString(int fd, FILE *fp);

int main(int argc, char **argv)
{
    int m_pipe[2];
    pid_t pid;
    if (pipe(m_pipe) < 0)
        err_error("Failed to create master pipe");
    if ((pid = fork()) < 0)
        err_error("Failed to fork master");
    else if (pid == 0)
    {
        close(m_pipe[READ]);
        sortMergeFiles(m_pipe[WRITE], argc - 1, &argv[1]);
        close(m_pipe[WRITE]);
    }
    else
    {
        close(m_pipe[WRITE]);
        convertToString(m_pipe[READ], stdout);
        close(m_pipe[READ]);
    }
    return 0;
}

static void convertToString(int fd, FILE *fp)
{
    int value;
    while (read(fd, &value, sizeof(int)) == sizeof(int))
        fprintf(fp, "%d\n", value);
}

static int readInteger(int fd, int *value)
{
    if (read(fd, value, sizeof(int)) != sizeof(int))
        return EOF;
    return 0;
}

static void writeInteger(int fd, int value)
{
    if (write(fd, &value, sizeof(int)) != sizeof(int))
        err_error("Failed to write integer to fd %d", fd);
}

static void mergeFiles(int fd_in1, int fd_in2, int fd_out)
{
    int value_1;
    int value_2;
    int eof_1 = readInteger(fd_in1, &value_1);
    int eof_2 = readInteger(fd_in2, &value_2);

    while (eof_1 != EOF && eof_2 != EOF)
    {
        err_remark("v1: %d; v2: %d", value_1, value_2);
        if (value_1 <= value_2)
        {
            writeInteger(fd_out, value_1);
            eof_1 = readInteger(fd_in1, &value_1);
        }
        else
        {
            writeInteger(fd_out, value_2);
            eof_2 = readInteger(fd_in2, &value_2);
        }
    }

    while (eof_1 != EOF)
    {
        err_remark("v1: %d", value_1);
        writeInteger(fd_out, value_1);
        eof_1 = readInteger(fd_in1, &value_1);
    }

    while (eof_2 != EOF)
    {
        err_remark("v2: %d", value_2);
        writeInteger(fd_out, value_2);
        eof_2 = readInteger(fd_in2, &value_2);
    }
}

static void sortMergeFiles(int fd, int number, char **names)
{
    assert(number >= 0);
    if (number == 0)
        return;
    else if (number == 1)
        sortOneFile(fd, names[0]);
    else
    {
        err_remark("Non-Leaf: processing %d files (%s .. %s)", number, names[0], names[number-1]);
        int mid = number / 2;
        int l_pipe[2];
        int r_pipe[2];
        pid_t l_pid;
        pid_t r_pid;
        if (pipe(l_pipe) < 0 || pipe(r_pipe) < 0)
            err_error("Failed to create pipes");
        if ((l_pid = fork()) < 0)
            err_error("Failed to fork left child");
        else if (l_pid == 0)
        {
            close(l_pipe[READ]);
            close(r_pipe[READ]);
            close(r_pipe[WRITE]);
            sortMergeFiles(l_pipe[WRITE], mid, names);
            close(l_pipe[WRITE]);
            exit(0);
        }
        else if ((r_pid = fork()) < 0)
            err_error("Failed to fork right child");
        else if (r_pid == 0)
        {
            close(r_pipe[READ]);
            close(l_pipe[READ]);
            close(l_pipe[WRITE]);
            sortMergeFiles(r_pipe[WRITE], number - mid, names + mid);
            close(r_pipe[WRITE]);
            exit(0);
        }
        else
        {
            close(l_pipe[WRITE]);
            close(r_pipe[WRITE]);
            mergeFiles(l_pipe[READ], r_pipe[READ], fd);
            close(l_pipe[READ]);
            close(r_pipe[READ]);
            err_remark("Non-Leaf: finished %d files (%s .. %s)", number, names[0], names[number-1]);
        }
    }
}

static void addNumberToArray(int number)
{
    assert(a_used >= 0 && a_used <= a_size);
    if (a_used == a_size)
    {
        int  n_size = (a_size + 1) * 2;
        int *n_data = realloc(a_data, sizeof(*n_data) * n_size);
        if (n_data == 0)
            err_error("Failed to allocate space for %d numbers", n_size);
        a_data = n_data;
        a_size = n_size;
    }
    a_data[a_used++] = number;
}

/* Could be compressed to write(fd, a_data, a_used * sizeof(int)); */
/* Arguably should check for write errors - but not SIGPIPE */
static void writeArray(int fd)
{
    for (int i = 0; i < a_used; i++)
    {
        err_remark("Write: %d", a_data[i]);
        if (write(fd, &a_data[i], sizeof(int)) != (ssize_t)sizeof(int))
            err_error("failed to write %zu bytes to pipe: ", sizeof(int));
    }
}

void readFile(char const *fileName)
{
    char buffer[BUFFER_SIZE];
    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL)
        err_error("Failed to open file %s for reading", fileName);

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        char *nl = strchr(buffer, '\n');
        if (nl != 0)
            *nl = '\0';
        err_remark("Line: %s", buffer);
        addNumberToArray(atoi(buffer));
    }

    fclose(fp);
}

int intcmp(const void *n1, const void *n2)
{
    const int num1 = *(const int *) n1;
    const int num2 = *(const int *) n2;
    return (num1 < num2) ? -1 : (num1 > num2);
}

void sortArray(void)
{
    qsort(a_data, a_used, sizeof(int), intcmp);
}

void freeMem(void)
{
    free(a_data);
}

static void sortOneFile(int fd, const char *file)
{
    err_remark("Leaf: processing file %s", file);
    readFile(file);
    sortArray();
    writeArray(fd);
    freeMem();
    err_remark("Leaf: finished file %s", file);
}

