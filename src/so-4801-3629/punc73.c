/* SO 4801-3629 */
/* Fixed code by Nick S (https://stackoverflow.com/users/8209813/nick-s) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

static void skip_copied_bytes(char *str, int *i)
{
    char c = 0;
    while (*str == ' ' && str)
    {
        str++;
        (*i)++;
    }

    while (*str != ' ' && *str != '\0' && !ispunct(c))
    {
        str++;
        (*i)++;
        c = *str;
    }

    while (*str == ' ' && str)
    {
        str++;
        (*i)++;
    }
}

static int count_char(char *str)
{

    int count = 0;
    char c = 0;
    while (*str == ' ' && str)
        str++;


    while (*str != ' ' && *str != '\0' && !ispunct(c))
    {
        count++;
        str++;
        c = *str;
    }

    while (*str == ' ' && str)
    {
        str++;
    }

    return count;
}

static int count_word(char const *s, char c)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while (s[i] != '\0')
    {
        while (s[i] == c)
            i++;
        if (s[i] != '\0')
            count++;
        while (s[i] != c && s[i] != '\0') {
            if (ispunct(s[i]))
                count++;
            i++;
        }
    }

    return count;
}
int main(void)
{
    char *str = "Hello, Sara! How are You?";
    char **array;
    int i = 0;
    int j = 0;
    int size = 0;

    size = count_word(str, ' ');
    if((array = malloc(sizeof(char *) * (size + 1))) == NULL)
        return -1;

    while (str[i])
    {
        size = count_char(&str[i]);
        if ((array[j] = malloc(sizeof(char) * (size))) == NULL)
            return -1;

        strncpy(array[j], &str[i], size);
        array[j][size] = '\0';

        skip_copied_bytes(&str[i], &i);
        j++;
    }

    array[j] = 0;

    for(i = 0; array[i]; i++) {
        printf("[%s] \n", array[i]);
    }
}
