/* SO 7776-8267 */
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>    /* Won't be need in C23 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char string[100];
    while (scanf(" %99[^\n]", string) == 1)
    {
        assert(strlen(string) != 0);
        size_t j = strlen(string) - 1;
        size_t i = 0;
        unsigned char *text = (unsigned char *)string;

        bool is_palindrome = true;
        while (i < j)
        {
            while (i < j && !isalpha(text[i]))
                i++;
            while (i < j && !isalpha(text[j]))
                j--;
            if (i == j)
                break;
            if (tolower(text[i]) != tolower(text[j]))
            {
                is_palindrome = false;
                break;
            }
            i++;
            j--;
        }

        printf("The string [%s] %s a palindrome\n", string,
                (is_palindrome ? "is" : "is not"));
    }
    return 0;
}

