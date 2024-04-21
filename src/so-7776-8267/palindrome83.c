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
        printf("[%s]\n", string);

        bool is_palindrome = true;
        while (i < j)
        {
            while (!isalpha((unsigned char)string[i]) && i < j)
                i++;
            while (!isalpha((unsigned char)string[j]) && i < j)
                j--;
            printf("i = %zu, j = %zu\n", i, j);
            //if (i >= j)
                //break;
            if (tolower((unsigned char)string[i]) != tolower((unsigned char)string[j]))
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

