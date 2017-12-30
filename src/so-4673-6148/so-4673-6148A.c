
/* SO 4673-6148 */
/*
** I have got a sequence in which first four numbers are given
** (specifically they are 1, 9, 8, 9 and the fifth one is solved as a5
** =(a1+a2+a3+a4)%10.  Then the numbers move to the right and process of
** solving fifth number is the same (meaning they are 9, 8, 9, 7 now).
** My task is to find out, whether there will be a sequence of 1, 9, 8,
** 9 again and after how many iterations.
*/

#include <stdio.h>

int main(void)
{
    int val = 1989;
    int seq[4] = { 1, 9, 8, 9 };
    char used[10000] = { [1989] = 1 };

    for (int i = 0; i < 10000; i++)
    {
        int new_digit = (seq[0] + seq[1] + seq[2] + seq[3]) % 10;
        int new_value = ((seq[1] * 10 + seq[2]) * 10 + seq[3]) * 10 + new_digit;
        if (new_value == val)
        {
            printf("Found result %.4d (iteration %d)\n", new_value, i);
            break;
        }
        if (used[new_value])
        {
            printf("Loop: %.4d has been seen before (iteration %d)\n", new_value, i);
            break;
        }
        printf("Next: %.4d (iteration %d)\n", new_value, i);
        for (int j = 1; j < 4; j++)
            seq[j-1] = seq[j];
        seq[3] = new_digit;
    }

    return 0;
}
