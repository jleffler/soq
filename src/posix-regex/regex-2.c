#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

static int verbose = 0;

/* Compile the regular expression described by "regex_text" into "r". */
static void compile_regex(regex_t *r, const char *regex_text)
{
    int status = regcomp(r, regex_text, REG_EXTENDED | REG_NEWLINE);
    if (status != 0)
    {
        char error_message[256];
        regerror(status, r, error_message, sizeof(error_message));
        fprintf(stderr, "Regex error compiling '%s': %s\n",
               regex_text, error_message);
        exit(EXIT_FAILURE);
    }
}

/*
   Match the string in "to_match" against the compiled regular
   expression in "r".
 */
static void match_regex(regex_t *r, const char *to_match)
{
    const char *p = to_match;
    const int n_matches = 10;
    regmatch_t match[n_matches];

    if (verbose)
        printf("-->> %s:\n", __func__);

    while (regexec(r, p, n_matches, match, 0) == 0)
    {
        for (int i = (verbose ? 0 : 1); i < n_matches && match[i].rm_so != -1; i++)
        {
            int start = match[i].rm_so + (p - to_match);
            int finish = match[i].rm_eo + (p - to_match);
            printf("$%d = (%2d:%-2d) '%.*s'\n",
                   i, start, finish, finish - start, to_match + start);
        }
        p += match[0].rm_eo;
    }

    if (verbose)
        printf("<<-- %s:\n", __func__);
}

int main(int argc, char **argv)
{
    const char *filename = "jain.txt";

    if (argc == 2)
        filename = argv[1];
    if (argc > 2)
        verbose = 1;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror(filename); // print the error message on stderr.
        return 1;
    }

    regex_t r;
    const char *regex_text = "\\[(0x[0-9a-fA-F]+) - (0x[0-9a-fA-F]+)\\].*\\[stack\\]";
    compile_regex(&r, regex_text);

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)     /* read a line from a file */
        match_regex(&r, line);

    fclose(fp);
    regfree(&r);

    return 0;
}
