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
    char **current = foundTokens;
    char *word = NULL;
    char c;

    while ((c = *str++) != '\0')
    {
        if (!isSeparator(c, seps))
        {
            if (word == NULL)
            {
                *current = (char *) malloc(30 * sizeof(char));
                word = *current++;
            }
            *word++ = c;
        }
        else
        {
            if (word != NULL)
                *word = '\0';
            word = NULL;
        }
    }
    if (word != NULL)
        *word = '\0';
    *tokens = foundTokens;
    return current - foundTokens;
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

    argc = parse_tokens(",abc,,axolotl,,zoological society gardens,,", ",", &argv);

    printf("argc = %d\n", argc);
    for (int i = 0; i <= argc; i++)
        printf("%p = [%s]\n", (void *)argv[i], (argv[i] != 0) ? argv[i] : "<null>");

    free_tokens(argv);

    return 0;
}
