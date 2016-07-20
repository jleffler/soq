#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int verbose = 0;

struct AddressRange
{
    uint64_t lo;
    uint64_t hi;
};

/* Compile the regular expression or report error and exit */
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

/* Match the string against the compiled regular expression */
static int match_regex(regex_t *r, const char *to_match, struct AddressRange *addr)
{
    const int n_matches = 10;
    regmatch_t match[n_matches];
    int rc = 0;

    if (verbose)
        printf("-->> %s:\n", __func__);

    if (regexec(r, to_match, n_matches, match, 0) == 0)
    {
        uint64_t values[3] = { 0, 0, 0 };
        for (int i = (verbose ? 0 : 1); i < n_matches && match[i].rm_so != -1; i++)
        {
            int start = match[i].rm_so;
            int finish = match[i].rm_eo;
            if (verbose)
                printf("$%d = (%2d:%-2d) '%.*s'\n",
                       i, start, finish, finish - start, to_match + start);
            values[i] = strtoul(to_match + start, 0, 16);
        }
        addr->lo = values[1];
        addr->hi = values[2];
        rc = 1;
    }

    if (verbose)
        printf("<<-- %s: %d\n", __func__, rc);
    return rc;
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
        perror(filename);
        return 1;
    }

    regex_t r;
    const char regex_text[] = "\\[(0x[0-9a-fA-F]+) - (0x[0-9a-fA-F]+)\\].*\\[stack\\]";
    compile_regex(&r, regex_text);

    char line[1024];
    struct AddressRange addresses[100];
    size_t n_addr = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (match_regex(&r, line, &addresses[n_addr]))
            n_addr++;
    }

    fclose(fp);
    regfree(&r);

    for (size_t i = 0; i < n_addr; i++)
    {
        printf("[%2zu] [0x%12" PRIX64 " - 0x%12" PRIX64 "]\n",
               i, addresses[i].lo, addresses[i].hi);
    }

    return 0;
}
