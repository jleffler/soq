/*
@(#)File:           errhelp.c
@(#)Purpose:        Print usage and help message in standard format.
@(#)Author:         J Leffler
@(#)Copyright:      (C) JLSS 2007-2022
@(#)Derivation:     errhelp.c 10.4 2022/04/15 16:25:30
*/

/*TABSTOP=4*/

#include "posixver.h"
#include "stderr.h"
#include <stdlib.h>

/* Some help messages can be very long */
#ifndef ERR_MAXMSGLEN
#define ERR_MAXMSGLEN 8192
#endif
enum { MAX_MSGLEN = ERR_MAXMSGLEN };

/*
** Print usage message and strings from hlp_lst, assuming that the help
** list strings all end with a newline.  Add an extra newline to match
** err_help()
*/
void err_helplist(const char *use_str, const char * const *hlp_lst)
{
    FILE *fp = stdout;
    char buffer[MAX_MSGLEN];    /* Fairly big chunk of stack! */
    flockfile(fp);
    err_fmt_usage(sizeof(buffer), buffer, use_str);
    err_logmsg(fp, ERR_REM|ERR_NOARG0, EXIT_SUCCESS,
               "%s\n\n%s", buffer, hlp_lst[0]);
    while (*++hlp_lst != 0)
        fprintf(fp, "%s", hlp_lst[0]);
    putchar('\n');
    fflush(fp);
    funlockfile(fp);
    exit(EXIT_SUCCESS);
}

void err_help(const char *use_str, const char *hlp_str)
{
    char buffer[MAX_MSGLEN];    /* Fairly big chunk of stack! */
    err_fmt_usage(sizeof(buffer), buffer, use_str);
    err_logmsg(stdout, ERR_ERR|ERR_NOARG0, EXIT_SUCCESS,
               "%s\n\n%s\n", buffer, hlp_str);
    /*NOTREACHED*/
    exit(EXIT_FAILURE);
}

#ifdef TEST

#include <unistd.h>

static const char usestr1[] = "[-hTV] [file ...]";

static const char hlpstr1[] =
    "  -V    Print version information and exit\n"
    "  -T    Test operation\n"
    "  -h    Print this help message\n"
    ;

static const char *hlplst1[] =
{
    "Use a help list when the help string is too long.\n"
    "The first help list item is normally a summary of what goes on.\n"
    "The last line of the first item should end with a newline - or with two\n"
    "to separate a summary from the subsequent output (listing options).\n\n",

    "  -T    Test operation\n"
    "  -V    Print (list variant) version information and exit\n",

    "  -h    Print (list variant) this help message\n",

    0
};

static const char usestr2[] =
    "[-htV][-s suffix][-p prefix][-F format][-T format] \\\n"
    "[-k constant][-d duplicates][-x exclude] [file ...]\n"
    ;

static const char *hlplst2[] =
{
    "  -d duplicates  Remove excess duplicates\n"
    "  -h             Print this help message\n"
    "  -k constant    Set the keep value\n",

    "  -p prefix      Set the prefix\n"
    "  -s suffix      Set the suffix\n"
    "  -t             Test operation\n",

    "  -x exclude     Do not remove these duplicates\n"
    "  -F format      Set the file name time format\n"
    "  -T format      Set the log entry time format\n",

    "  -V             Print version information and exit\n",

    0
};

int main(int argc, char **argv)
{
    int pid;
    if (argc != 0)
        err_setarg0(argv[0]);
    if ((pid = fork()) < 0)
        err_syserr("failed to fork: ");
    else if (pid == 0)
        err_help(usestr1, hlpstr1);
    else if ((pid = fork()) < 0)
        err_syserr("failed to fork: ");
    else if (pid == 0)
    {
        sleep(1);
        err_helplist(usestr1, hlplst1);
    }
    else
    {
        sleep(2);
        err_helplist(usestr2, hlplst2);
    }
    return(0);
}

#endif /* TEST */
