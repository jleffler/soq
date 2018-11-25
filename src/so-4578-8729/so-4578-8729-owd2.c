#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool getWord(char *line, int *idx, char *word)
{
    int wordIdx = 0;

    for ( ; line[*idx] != '\0'; *idx = (*idx + 1))
    {
        if (isalpha((unsigned char)line[*idx]) || (line[*idx] == '-'))
        {
            word[wordIdx++] = tolower((unsigned char)line[*idx]);
        }
        else if (isspace((unsigned char)line[*idx]))
        {
            *idx += 1;
            printf("1 [%s]\n", word);
            return true;
        }
    }

    printf("2 [%s]\n", word);
    return true;
}

static void processFile(FILE *textFp)
{
    char line[1024] = "";
    char *word = malloc(sizeof(unsigned char) * 50);
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

        while (*lineIdx < (charcount - 1))
        {
            for (int i = 0; i < 50; i++)
            {
                word[i] = '\0';
            }
            getWord(line, lineIdx, word);
        }

        *lineIdx = 0;
        lineCount++;
    }

    free(lineIdx);
    free(word);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s afile.txt\n", argv[0]);
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "r+");

    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file '%s' for reading\n", argv[1]);
        exit(1);
    }

    processFile(fp);

    if (fclose(fp) != 0)
        fprintf(stderr, "Failed to close file '%s'.\n", argv[1]);

    return(0);
}
