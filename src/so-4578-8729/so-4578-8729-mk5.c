#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long hash(char *word)
{
    unsigned char *str = (unsigned char *)word;
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c;

    return hash;
}

static void getWord(char *line, int *idx, int maxwordlen, char *word)
{
    int wordIdx = 0;
    assert(maxwordlen > 0);

    for ( ; line[*idx] != '\0'; *idx = (*idx + 1))
    {
        if (wordIdx >= maxwordlen)
        {
            word[maxwordlen] = '\0';
            fprintf(stderr, "Word overflow: %d %d [%*.*s]\n", wordIdx, maxwordlen, maxwordlen, maxwordlen, word);
            exit(EXIT_FAILURE);
        }
        if (isalpha(line[*idx]) || (line[*idx] == '-'))
        {
            word[wordIdx++] = tolower(line[*idx]);
        }
        else if (isspace(line[*idx]))
        {
            *idx += 1;
            word[wordIdx] = '\0';
            return;
        }
    }
    word[wordIdx] = '\0';
}

static void processFile(FILE *textFp)
{
    char line[1024];
    int maxwordlen = 20;
    char word[maxwordlen];
    //char *word = malloc(maxwordlen+1);
    int lineCount = 1;

    while (fgets(line, sizeof(line), textFp) != NULL)
    {
        int charcount = 0;
        int wordCount = 1;
        int lineIdx = 0;

        for (int m = 0; line[m] != '\0'; m++)
        {
            if ((line[m] == ' ') && (line[m - 1] != ' '))
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

        while (lineIdx < (charcount - 1))
        {
            // Could use memset() - but better if getWord() null
            // terminates and checks for overflow.
            //for (int i = 0; i < maxwordlen; i++)
            //{
                //word[i] = '\0';
            //}

            getWord(line, &lineIdx, maxwordlen, word);
            unsigned long hash_output = hash(word);
            printf("hash: %20lu idx: %2d len: %2zu value: [%s]\n",
                   hash_output, lineIdx, strlen(word), word);
        }
        lineCount++;
    }
    //free(word);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s textfile\n", argv[0]);
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
        fprintf(stderr, "File did not close.\n");

    exit(0);
}
