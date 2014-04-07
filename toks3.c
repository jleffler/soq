/* SO 22901191 */
#include <stdio.h>
#include <stdlib.h>

char isSeparator(char character, char *seps);
int parse_tokens(char *str, char *seps, char ***tokens);
void free_tokens(char **tokens);

char isSeparator(char character, char *seps)
{
    while (*seps != '\0')
    {
        if (*seps++ == character)
            return 1;
    }
    return 0;
}

int parse_tokens(char *str, char *seps, char ***tokens)
{
    char **foundTokens = (char **) calloc(10, sizeof(char *));
    char c;
    int tokenCount = 0;
    int tokenLetter = 0;

    while ((c = *str++) != '\0')
    {
        if (!isSeparator(c, seps))
        {
            if (foundTokens[tokenCount] == NULL)
                foundTokens[tokenCount] = (char *) malloc(30 * sizeof(char));
            foundTokens[tokenCount][tokenLetter] = c;
            ++tokenLetter;
        }
        else
        {
            if (foundTokens[tokenCount] != NULL)
            {
                foundTokens[tokenCount][tokenLetter] = '\0';
                ++tokenCount;
            }
            tokenLetter = 0;
        }
    }
    if (foundTokens[tokenCount] != NULL)
    {
        foundTokens[tokenCount][tokenLetter] = '\0';
        ++tokenCount;
    }
    foundTokens[tokenCount+1] = NULL;
    *tokens = foundTokens;
    return tokenCount;
}

void free_tokens(char **tokens)
{
    for (int i = 0; tokens[i] != NULL; i++)
        free(tokens[i]);
    free(tokens);
}

int main(void)
{
    char **argv;
    int argc = parse_tokens("hello,world", ",", &argv);

    printf("argc = %d\n", argc);
    for (int i = 0; i <= argc; i++)
        printf("%p = [%s]\n", (void *)argv[i], (argv[i] != 0) ? argv[i] : "<null>");

    free_tokens(argv);
    return 0;
}

