/* JL comments in old-style C comments */

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int prepare_rsa_public_file(char const *cfg_in, char const *cfg_out, char const *req_seq);

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
static void rsa_copy_key(char tag, FILE *fphex, char *value)
{
    char *pch;

    fprintf(fphex, "%c = ", tag);

    pch = strtok(value, COMMA);
    while (pch != NULL)
    {
        fprintf(fphex, "%.2X", atoi(pch));
        pch = strtok(NULL, COMMA);
    }

    fprintf(fphex, "\n");
}

/* Read one key (x = nn,nn,nn) line */
static int rsa_read_one_key(FILE *fpdec, FILE *fphex, char req_letter)
{
    char buffer[BUFFER_SIZE];
    char value[BYTE_KEY_SIZE];
    char act_letter;

    if (fgets(buffer, sizeof (buffer), fpdec) == NULL)
        return err_report("%s: fgets()#1 returned NULL\n", __func__);
    if (sscanf(buffer, "%c = %s", &act_letter, value) != 2)
        return err_report("%s: sscanf()#1 returned a value other than 2\n", __func__);
    if (act_letter != req_letter)
        return err_report("%s: letter read was '%c', not '%c' as required\n", __func__, act_letter, req_letter);
    rsa_copy_key(req_letter, fphex, value);
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

// Read Decimal value as per TAG which i provided.
static int rsa_read_key(FILE *fpdec, FILE *fphex, char const *req_seq)
{
    char c;
    while ((c = *req_seq++) != '\0')
    {
        if (rsa_read_one_key(fpdec, fphex, c) != OK)
            return ERROR;
    }
    if (getc(fpdec) != EOF)
        return err_report("%s: extra material in input file\n", __func__);
    return OK;
}

// Just open both files
/* ...and if successful, call rsa_read_key() to transfer the data between
** the files, and then close the files afterwards.
*/
/*
** Using simple "r" and "w" modes to get native text line endings (CRLF
** on Windows, LF aka NL on Unix).  The code doesn't use the update mode
** for the output file; you probably want the output file truncated.
*/
int prepare_rsa_public_file(char const *cfg_in, char const *cfg_out, char const *req_seq)
{
    FILE *fpdec = NULL;
    FILE *fphex = NULL;
    int ret;

    ret = OK;

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
        // Here i have to change function in dynamic way like we have to pass TAG value.
        if (rsa_read_key(fpdec, fphex, req_seq) != OK)
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
    if (argc != 4)
        fprintf(stderr, "Usage: %s key file-in file-out\n", argv[0]);
    else if (prepare_rsa_public_file(argv[2], argv[3], argv[1]) == OK)
        rc = EXIT_SUCCESS;
    return rc;
}

