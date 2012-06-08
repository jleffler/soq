/* JL comments in old-style C comments */

#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int prepare_rsa_public_file(char const *cfg_in, char const *cfg_out, char **req_tags, int num_tags);

enum { BUFFER_SIZE = 4096 };
enum { BYTE_KEY_SIZE = 4096 };
enum { OK = 0, ERROR = 1 };

#define COMMA ",\r\n"

static int err_report(char const *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    return(ERROR);
}

/* All material above here added to ensure compilation */

// Write Hex value with TAG.
/*
** NB: strtok() does no memory allocation; there is no call to free
** anything.  NB: this code processes invalid data, generating extra hex
** digits if a value is out of the range 0..255.
**
** NB: If the file is on Windows, the \n will be converted to \r\n
** automatically.
*/
static void rsa_copy_key(char *tag, FILE *fphex, char *value)
{
    char *pch;

    fprintf(fphex, "%s = ", tag);

    pch = strtok(value, COMMA);
    while (pch != NULL)
    {
        fprintf(fphex, "%.2X", atoi(pch));
        pch = strtok(NULL, COMMA);
    }

    fprintf(fphex, "\n");
}

enum { MAX_TAG_SIZE = 7 };

/* Is the given tag in the list of tags? */
/* If so, remove the tag from the list, decreasing list size */
static bool interesting_tag(char *tag, char **tags, int *num_tags)
{
    int num = *num_tags;
    for (int i = 0; i < num; i++)
    {
        if (strcmp(tag, tags[i]) == 0)
        {
            /* It is interesting */
            if (i < num - 1)
            {
                tags[i] = tags[num - 1];
                tags[num - 1] = 0;
            }
            (*num_tags)--;
            return true;
        }
    }
    return false;
}

/* Read one key (x = nn,nn,nn) line */
static int rsa_read_one_key(FILE *fpdec, FILE *fphex, char **tags, int *num_tags)
{
    char buffer[BUFFER_SIZE];
    char value[BYTE_KEY_SIZE];
    char tag[MAX_TAG_SIZE+1];
    char fmt[16];

    sprintf(fmt, "%%%ds = %%%ds", MAX_TAG_SIZE, BYTE_KEY_SIZE-1);

    if (fgets(buffer, sizeof (buffer), fpdec) == NULL)
        return err_report("%s: fgets()#1 returned NULL\n", __func__);
    if (sscanf(buffer, fmt, tag, value) != 2)
        return err_report("%s: sscanf()#1 returned a value other than 2\n", __func__);

    /* Is the tag read an interesting one? */
    if (interesting_tag(tag, tags, num_tags))
        rsa_copy_key(tag, fphex, value);
    return OK;
}

/*
** Design decision time.
**
** The existing system is tied to expecting an N and an E entry in
** exactly that sequence.  Extra material in the input (after the
** required material) isn't a problem; it is ignored.  Missing material
** is a problem.
**
** The new requirement is for some extra "x = hex-number-list" entries to be allowed.
** The problems arising include:
** 1.  Are the new items mandatory or optional?
** 2.  Must the items appear in the given order?
** 3.  What happens if an item is repeated?
** 4.  How does what determine what is and is not allowed?
** 5.  Should excess material be ignored?
**
** For the revision, the decisions are:
** 1.  Presence mandatory.
** 2.  Sequence mandatory.
** 3.  Repetition allowed if sequence says so (no check).
** 4.  Sequence defined by a string of key letters.
** 5.  EOF after last item is required (excess material is an error).
*/

/*
** Design decision time - Part 2
**
** The previous system required tags to be present in sequence, no
** extras allowed.
**
** The revised design must look for specified tags in sequence, but
** interlopers are allowed and ignored.  Further, the tags are now
** strings, not single letters.  Repeats are ignored.  Search can stop
** when all required tags have been converted.  EOF before getting
** required tags is an error.
**
** Tags will be not longer than 7 characters.
*/

// Read Decimal value as per TAG which i provided.
static int rsa_read_key(FILE *fpdec, FILE *fphex, char **req_tags, int num_tags)
{
    char *tags[num_tags];

    /* Copy tag list - it will be adjusted as we go */
    for (int i = 0; i < num_tags; i++)
        tags[i] = req_tags[i];

    while (num_tags > 0)
    {
        if (rsa_read_one_key(fpdec, fphex, tags, &num_tags) != OK)
            return ERROR;
    }
    return OK;
}

/*
** Open files and, if successful, call rsa_read_key() to transfer the
** data between the files, and then close the files afterwards.
**
** Use simple "r" and "w" modes to get native text line endings (CRLF on
** Windows, LF aka NL on Unix).  The code doesn't use the update mode
** for the output file; you probably want the output file truncated.
*/
int prepare_rsa_public_file(char const *cfg_in, char const *cfg_out, char **req_tags, int num_tags)
{
    FILE *fpdec = NULL;
    FILE *fphex = NULL;
    int   ret   = OK;

    if ((fpdec = fopen(cfg_in, "r")) == NULL)
        ret = err_report("Failed to Open Configuration File %s (%d: %s)\n", cfg_in, errno, strerror(errno));
    else if ((fphex = fopen(cfg_out, "w")) == NULL)
    {
        int errnum = errno;
        fclose(fpdec);
        ret = err_report("Failed to Open Configuration File %s (%d: %s)\n", cfg_out, errnum, strerror(errnum));
    }
    else
    {
        if (rsa_read_key(fpdec, fphex, req_tags, num_tags) != OK)
            ret = err_report("Failed: rsa_read_key() returned an error\n");
        fclose(fphex);
        fclose(fpdec);
    }
    return ret;
}

/* Simple test program to exercise the prepare_rsa_public_file() function */
int main(int argc, char **argv)
{
    int rc = EXIT_FAILURE;
    if (argc < 4)
        fprintf(stderr, "Usage: %s file-in file-out key [...]\n", argv[0]);
    else if (prepare_rsa_public_file(argv[1], argv[2], &argv[3], argc - 3) == OK)
        rc = EXIT_SUCCESS;
    return rc;
}

