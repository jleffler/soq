#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1
#define NUMOFFILES 8

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

const int BUFFER_SIZE = 256;
char **numberChar;
int *numbers;
int start, end, count, i;
int numbs = 0;
int sizeNumbers = 10;
int numSizes[10];
char *fileNames[NUMOFFILES] = { "1", "2", "3", "4", "5", "6", "7", "8" };

void readFile(char*);
void freeMem(void);
void convertToInt(void);
int intcmp(const void *n1, const void *n2);
void createLeafs(int, int);
void breed(int);

int main(void)
{
  breed(4);
  return 0;
}

void readFile(char* fileName)
{
    char buffer[BUFFER_SIZE];
    FILE *fp;
    fp = fopen(fileName, "r");

    if (fp == NULL)
        err_error("Failed to open file %s for reading", fileName);

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        start = 0;
        end = 0;

        while (end < BUFFER_SIZE && buffer[end] != '\0')
        {
            if (buffer[end] == '/' &&  buffer[end+1] == '*')
                buffer[end] = '\0';
            else
            {
                while (end < BUFFER_SIZE)
                    end++;

                if (end > start)
                {
                    if (numbs == sizeNumbers)
                    {
                        sizeNumbers += 10;
                        numberChar = (char **) realloc(numberChar, sizeNumbers*sizeof(char *));
                    }

                    numberChar[numbs] = (char *) calloc(end-start+1, sizeof(char));

                    for (i = 0; i < end-start; i++)
                        numberChar[numbs][i] = buffer[start + i];
                    numberChar[numbs][i] = '\0';
                    numbs++;
                }
                start = ++end;
            }
        }
    }

    if (numbs < sizeNumbers)
        numberChar = (char **) realloc(numberChar, numbs*sizeof(char *));
}

void convertToInt(void)
{
    numbers = (int *) malloc(numbs * sizeof (int));
    for (i = 0; i < numbs; i++)
    {
        numbers[i] = atoi(numberChar[i]);
    }

    qsort(numbers, numbs, sizeof(int), intcmp);
}

int intcmp(const void *n1, const void *n2)
{
    const int num1 = *(const int *) n1;
    const int num2 = *(const int *) n2;
    return (num1 < num2) ? -1 : (num1 > num2);
}

void freeMem(void)
{
    for (i = 0; i < numbs; i++)
        free(numberChar[i]);
    free(numberChar);
    free(numbers);
}

void createLeafs(int min, int max)
{
    int upPipe[2];
    int leftPipe[2];
    int rightPipe[2];
    pid_t leftPID;
    pid_t rightPID;
    int fMin = min;
    int fMax = max;
    int fileNumber = 0;

    if (pipe (upPipe) < 0 || pipe(leftPipe) < 0 || pipe(rightPipe) < 0)
        err_error("Failed to create one of three pipes");

    if ((leftPID = fork()) < 0)
        err_error("Left fork() failed");

    if (leftPID == 0)
    {
        err_remark("Left starting");
        fMax = ((fMax)/2);
        dup2(leftPipe[WRITE], upPipe[WRITE]);
        pipe(leftPipe);
        pipe(rightPipe);

        if (fMax == 1)
        {
            err_remark("Created left leaf");

            close(rightPipe[READ]);
            close(rightPipe[WRITE]);
            close(leftPipe[READ]);
            close(leftPipe[WRITE]);

            numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
            readFile(fileNames[fileNumber]);
            convertToInt();
            for (i = 0; i < numbs; i++)
                write(upPipe[WRITE], &numbers[i], sizeof(int));
            freeMem();
            close(upPipe[READ]);
            close(upPipe[WRITE]);
            exit(0);
        }
        else
        {
            createLeafs(fMin, fMax);
        }
    }

    if ((rightPID = fork()) < 0)
        err_error("Right fork() failed");

    if (rightPID == 0)
    {
        err_remark("Right starting");
        fMax = ((fMax)/2);
        dup2(rightPipe[WRITE], upPipe[WRITE]);
        pipe(leftPipe);
        pipe(rightPipe);

        if (fMax == 1)
        {
            err_remark("Created right leaf");

            close(rightPipe[READ]);
            close(rightPipe[WRITE]);
            close(leftPipe[READ]);
            close(leftPipe[WRITE]);

            numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
            readFile(fileNames[fileNumber]);
            fileNumber++;
            convertToInt();
            for (i = 0; i < numbs; i++)
                write(upPipe[WRITE], &numbers[i], sizeof(int));
            freeMem();

            close(upPipe[READ]);
            close(upPipe[WRITE]);
            exit(0);
        }
        else
        {
            createLeafs(fMin, fMax);
        }
    }
    wait(&leftPID);
    wait(&rightPID);

    int master = 0;
    if (fMax == 8)
    {
        err_remark("Master was set********************");
        master = 1;
        close(upPipe[READ]);
        close(upPipe[WRITE]);
    }

    int passUp = 1;
    int leftContents = 999999999;
    int rightContents = 999999999;
    int leftEmpty = 0;
    int rightEmpty = 0;
    int intbuffer;
    int nbytes;
    close(rightPipe[WRITE]);
    close(leftPipe[WRITE]);
    while (passUp)
    {
        if (leftContents == 999999999)
        {
            nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
            if (nbytes > 0)
            {
                leftContents = intbuffer;
            }
            else
            {
                leftEmpty = 1;
            }
        }

        if (rightContents == 999999999)
        {
            nbytes = read(rightPipe[READ], &intbuffer, sizeof(intbuffer));
            if (nbytes > 0)
            {
                rightContents = intbuffer;
            }
            else
            {
                rightEmpty = 1;
            }
        }

        if (leftContents < rightContents)
        {
            if (master)
                printf("Master Printout: %d\n", leftContents);
            else
                write(upPipe[WRITE], &leftContents, sizeof(int));
            leftContents = 999999999;
            err_remark("left contents sent up");
        }
        else if (rightContents < leftContents)
        {
            if (master)
                printf("Master Printout: %d\n", rightContents);
            else
                write(upPipe[WRITE], &rightContents, sizeof(int));
            rightContents = 999999999;
            err_remark("right contents sent up");
        }
        else if ((leftContents == rightContents) && (leftEmpty != 1 && rightEmpty != 1))
        {
            if (master)
            {
                printf("Master Printout: %d\n", rightContents);
                printf("Master Printout: %d\n", leftContents);
                err_remark("MASTER PROCESS WENT THROUGH*********************");
            }
            else
            {
                write(upPipe[WRITE], &rightContents, sizeof(int));
                write(upPipe[WRITE], &leftContents, sizeof(int));
            }
            leftContents = 999999999;
            rightContents = 999999999;
            err_remark("both contents sent up");
        }
        else if (leftEmpty == 1 && rightEmpty == 1)
        {
            passUp = 0;
            err_remark("exit loop");
        }
    }

    close(rightPipe[READ]);
    close(leftPipe[READ]);
    if (!master)
    {
        close(upPipe[WRITE]);
        exit(0);
    }
}

void breed(int spawns)
{
    int upPipe[2];
    int leftPipe[2];
    int rightPipe[2];
    int status;
    pid_t leftPID;
    pid_t rightPID;

    if (pipe (upPipe) < 0 || pipe(leftPipe) < 0 || pipe(rightPipe) < 0)
        err_error("Failed to create one of three pipes");

    if ((leftPID = fork()) < 0)
        err_error("Left fork() failed");

    if (leftPID == 0)
    {
        err_remark("Left starting");
        dup2(leftPipe[WRITE], upPipe[WRITE]);
        pipe(leftPipe);
        pipe(rightPipe);
        close(upPipe[READ]);
        spawns = (spawns/2);
        if (spawns == 1)
        {
            close(rightPipe[READ]);
            close(rightPipe[WRITE]);
            close(leftPipe[READ]);
            close(leftPipe[WRITE]);

            numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
            readFile(fileNames[1]);
            convertToInt();
            for (i = 0; i < numbs; i++)
                write(upPipe[WRITE], &numbers[i], sizeof(int));
            freeMem();

            close(upPipe[WRITE]);
            exit(0);
        }
        breed(spawns);
    }

    if ((rightPID = fork()) < 0)
        err_error("Right fork() failed");

    if (rightPID == 0)
    {
        err_remark("Right starting");
        dup2(rightPipe[WRITE], upPipe[WRITE]);
        pipe(leftPipe);
        pipe(rightPipe);
        spawns = (spawns/2);
        if (spawns == 1)
        {
            close(rightPipe[READ]);
            close(rightPipe[WRITE]);
            close(leftPipe[READ]);
            close(leftPipe[WRITE]);
            close(upPipe[READ]);

            numberChar = (char **) calloc(sizeNumbers, sizeof(char *));
            readFile(fileNames[2]);
            convertToInt();
            for (i = 0; i < numbs; i++)
                write(upPipe[WRITE], &numbers[i], sizeof(int));
            freeMem();

            close(upPipe[WRITE]);
            exit(0);
        }
        breed(spawns);
    }
    waitpid(leftPID, &status , 0);
    waitpid(rightPID, &status, 0);

    int master = 0;
    if (spawns == 4)
    {
        master = 1;
        close(upPipe[READ]);
        close(upPipe[WRITE]);
        err_remark("we are master");
    }

    int passUp = 1;
    int leftContents = 999999999;
    int rightContents = 999999999;
    int leftEmpty = 0;
    int rightEmpty = 0;
    int intbuffer;
    int nbytes;
    close(rightPipe[WRITE]);
    close(leftPipe[WRITE]);
    if (master)
        err_remark("Master is going into while loop");
    while (passUp)
    {
        if (leftContents == 999999999)
        {
            nbytes = read(leftPipe[READ], &intbuffer, sizeof(intbuffer));
            if (nbytes > 0)
            {
                leftContents = intbuffer;
            }
            else
            {
                leftEmpty = 1;
                err_remark("left empty");
            }
        }

        if (rightContents == 999999999)
        {
            nbytes = read(rightPipe[READ], &intbuffer, sizeof(intbuffer));
            if (nbytes > 0)
            {
                rightContents = intbuffer;
            }
            else
            {
                rightEmpty = 1;
            }
        }

        if (leftContents < rightContents)
        {
            if (master == 1)
                printf("Master Printout: %d\n", leftContents);
            else
                write(upPipe[WRITE], &leftContents, sizeof(int));
            leftContents = 999999999;
            err_remark("**left sent");
        }
        else if (rightContents < leftContents)
        {
            if (master == 1)
                printf("Master Printout: %d\n", rightContents);
            else
                write(upPipe[WRITE], &rightContents, sizeof(int));
            rightContents = 999999999;
            err_remark("**right sent");
        }
        else if ((leftContents == rightContents) && (leftEmpty != 1 && rightEmpty != 1))
        {
            if (master == 1)
            {
                printf("Master Printout: %d\n", rightContents);
                printf("Master Printout: %d\n", leftContents);
            }
            else
            {
                write(upPipe[WRITE], &leftContents, sizeof(int));
                write(upPipe[WRITE], &rightContents, sizeof(int));
            }
            leftContents = 999999999;
            rightContents = 999999999;
            err_remark("*****both sent");
        }
        else if (leftEmpty == 1 && rightEmpty == 1)
        {
            if (!master)
            {
                close(upPipe[WRITE]);
                close(upPipe[READ]);
            }
            passUp = 0;
            err_remark("exit loop");
        }
    }

    close(rightPipe[READ]);
    close(leftPipe[READ]);
    if (!master)
        exit(0);
}
