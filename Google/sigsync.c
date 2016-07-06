#include "posixver.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int verbose = 1;
static volatile sig_atomic_t sig_num = 0;

static void sigusr1(int signum)
{
    sig_num = signum;
}

static void be_childish(const char *file, pid_t parent)
{
    char str[512];
    fprintf(stderr, "Child: %d (parent %d)\n", (int)getpid(), (int)parent);
    FILE *fpr = fopen(file, "r");
    if (fpr == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", file);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        rewind(fpr);
        fprintf(stderr, "Child: pausing\n");
        if (sig_num == 0)
            pause();
        if (verbose)
            printf("Child:  got %d\n", sig_num);
        while (fscanf(fpr, "%511[^\n]\n", str) == 1)
            printf("%s\n", str);
        kill(parent, SIGUSR1);
        sig_num = 0;
    }

    /*NOTREACHED*/
    fclose(fpr);
}

static void be_parental(const char *file, pid_t child)
{
    char str[512];
    const char profile[] = "/etc/profile";

    fprintf(stderr, "Parent: %d (child %d)\n", (int)getpid(), (int)child);
    FILE *fpr = fopen(profile, "r");
    if (fpr == NULL)
    {
        fprintf(stderr, "Failed to open file %s for reading\n", profile);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fpr, "%511[^\n]\n", str) != EOF)
    {
        fprintf(stderr, "Parent: read [%s]\n", str);
        if (strlen(str) > 0)
        {
            FILE *fpw = fopen(file, "w");
            if (fpw == 0)
            {
                fprintf(stderr, "Failed to open file %s for reading\n", profile);
                kill(child, SIGTERM);
                exit(EXIT_FAILURE);
            }
            fprintf(fpw, "%s\n", str);
            fclose(fpw);
            kill(child, SIGUSR1);
            fprintf(stderr, "Parent: pausing\n");
            if (sig_num == 0)
                pause();
            if (verbose)
                printf("Parent: got %d\n", sig_num);
            sig_num = 0;
        }
    }
    fclose(fpr);
    kill(child, SIGTERM);
}

int main(void)
{
    int child;
    int parent = getpid();
    const char filename[] = "bufor";

    /* Make sure file exists and is empty */
    FILE *fp = fopen(filename, "w");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s for writing\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    if (getenv("SIGSYNC_VERBOSE") != 0)
        verbose = 1;

    struct sigaction sa;
    sa.sa_handler = sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, 0) != 0)
    {
        fprintf(stderr, "Failed to set signal handler\n");
        exit(EXIT_FAILURE);
    }

    if ((child = fork()) < 0)
    {
        fprintf(stderr, "Failed to fork\n");
        exit(EXIT_FAILURE);
    }
    else if (child == 0)
        be_childish(filename, parent);
    else
        be_parental(filename, child);

    return 0;
}
