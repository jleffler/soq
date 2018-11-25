/* SO-4578-8729 */
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool DEBUG = false;

static
unsigned long hash(char *data)
{
    unsigned char *str = (unsigned char *)data;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c;

    return hash;
}

static
bool getWord(char *line, int *idx, char *word)
{
    int wordIdx = 0;

    for ( ; line[*idx] != '\0'; *idx = (*idx + 1))
    {
        if (isalpha(line[*idx]) || (line[*idx] == '-'))
        {
            word[wordIdx++] = tolower(line[*idx]);
        }
        else if (isspace(line[*idx]))
        {
            *idx += 1;
            return true;
        }
    }

    return true;
}

static
void processFile(FILE *textFp)
{
    char line[1024] = "";
    char *word = malloc(sizeof(char) * 50);
    int *lineIdx = malloc(sizeof(int));
    int lineCount = 1;

    *lineIdx = 0;

    while (fgets(line, sizeof(line), textFp) != NULL)
    {
        int charcount = 0;
        int wordCount = 1;

        for (int m = 0; line[m] != '\0'; m++)
        {
            if ((line[m] == ' ') && (m == 0 || line[m - 1] != ' '))
            {
                wordCount++;
            }
            if (line[m] != '\n' && line[m] != '\r')
            {
                charcount++;
            }
            else
            {
                line[m] = '\0';
            }
        }

        if (DEBUG == true)
        {
            fprintf(stdout, "line %d:\n", lineCount);
            fprintf(stdout, "  words in line: %d\n", wordCount);
            fprintf(stdout, "  charcount: %d\n", charcount);
            fprintf(stdout, "  lineIdx: %d\n", *lineIdx);
            fprintf(stdout, "  value: \"%s\"\n\n", line);
        }

        while (*lineIdx < (charcount - 1))
        {
            for (int i = 0; i < 50; i++)
            {
                word[i] = '\0';
            }

            getWord(line, lineIdx, word);
            unsigned long hash_output = hash(word);

            if (DEBUG == true)
            {
                fprintf(stdout, "key: %10lu,\t", hash_output);
                fprintf(stdout, "value: %8s,\t", word);
                fprintf(stdout, "lineIdx: %2d\n", *lineIdx);
            }
        }

        if (DEBUG == true)
        {
            fprintf(stdout, "\n========\n\n");
        }

        *lineIdx = 0;
        lineCount++;
    }

    if (DEBUG == true)
    {
        if (feof(textFp))
        {
            fprintf(stderr, "Reached FEOF.\n");
        }
    }

    free(lineIdx);
    free(word);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "usage: main afile.txt\n");
        exit(-1);
    }

    if (argc >= 3)
    {
        if (strcmp("-d", argv[2]) == 0)
        {
            DEBUG = true;
            fprintf(stdout, "+++++++++++++++++++++++++++++++++++++++\n");
            fprintf(stdout, "+            [DEBUGGING ON]           +\n");
            fprintf(stdout, "+++++++++++++++++++++++++++++++++++++++\n\n");
        }
    }

    FILE *fp = fopen(argv[1], "r+");

    if (fp == 0)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(1);
    }
    if (DEBUG == true)
    {
        fprintf(stdout, "File exists.\n");
    }
    if (DEBUG == true)
    {
        fprintf(stdout, "\n");
        fprintf(stdout, "================================================================================\n");
    }

    processFile(fp);

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "File did not close.\n");
    }
    if (DEBUG == true)
    {
        fprintf(stdout, "File closed.\n");
    }
    if (DEBUG == true)
    {
        fprintf(stdout, "================================================================================\n");
        fprintf(stdout, "\n");
    }

    exit(0);
}
