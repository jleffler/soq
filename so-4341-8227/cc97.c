/* SO 4341-8227 */
/* CodeChef: https://www.codechef.com/APRIL17/problems/ROWSOLD */
/* Quadratic solution - exceeds time limit on N = 5000 or bigger */

#include <assert.h>
#include <stdio.h>
#include <string.h>

static inline int num_char(const char *data, char c)
{
    int count = 0;
    for (int i = 0; data[i] != '\0'; i++)
        if (data[i] == c)
            count++;
    return count;
}

int main(void)
{
    char buffer[10002];
    int d;
    if (fgets(buffer, sizeof(buffer), stdin) == 0)
        return 1;
    if (sscanf(buffer, "%d", &d) != 1)
        return 1;
    //printf("%d entries\n", d);
    for (int i = 0; i < d; i++)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == 0)
            return 1;
        buffer[strcspn(buffer, "\n")] = '\0';
        int buflen = strlen(buffer);
        int tot_1s = num_char(buffer, '1');
        int tot_0s = num_char(buffer, '0');
        if (tot_1s + tot_0s != buflen)
            return 1;
        int lm1 = 0;
        int count = 0;
        //printf("Input:  %s (1s = %d, 0s = %d)\n", buffer, tot_1s, tot_0s);
        while (lm1 < buflen - tot_1s)
        {
            //printf("Before: %s (count = %d; lm1 = %d)\n", buffer, count, lm1);
            while (buffer[lm1] == '0')
                lm1++;
            int lm0 = lm1;
            while (buffer[lm0] == '1')
                lm0++;
            if (lm0 >= buflen)
                break;
            assert(lm0 < buflen);
            count++;    // select time
            buffer[lm0 - 1] = '0';
            while (buffer[lm0] == '0')
            {
                count++;    // move time
                lm0++;
            }
            buffer[lm0 - 1] = '1';
            //printf("After:  %s (count = %d; lm1 = %d)\n", buffer, count, lm1);
        }
        printf("%d\n", count);
    }
    return 0;
}

