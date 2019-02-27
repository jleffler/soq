
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

static void check_sequence(int val)
{
    int seq[4] = { (val / 1000) % 10, (val / 100) % 10, (val / 10) % 10, (val / 1) % 10 };
    char used[10000] = { 0 };

    used[val] = 1;

    for (int i = 0; i < 10000; i++)
    {
        int new_digit = (seq[0] + seq[1] + seq[2] + seq[3]) % 10;
        int new_value = ((seq[1] * 10 + seq[2]) * 10 + seq[3]) * 10 + new_digit;
        if (new_value == val)
        {
            printf("Search %.4d: Found result %.4d (iteration %d)\n", val, new_value, i+1);
            return;
        }
        if (used[new_value])
        {
            //printf("Loop: %.4d has been seen before (iteration %d)\n", new_value, i+1);
            printf("Search %.4d: failed with loop (iteration %d)\n", val, i+1);
            return;
        }
        //printf("Next: %.4d (iteration %d)\n", new_value, i+1);
        for (int j = 1; j < 4; j++)
            seq[j-1] = seq[j];
        seq[3] = new_digit;
    }
    /*NOTREACHED*/
    printf("Search %.4d: failed after 10,000 iterations\n", val);
}

int main(void)
{
    for (int i = 0; i < 10000; i++)
        check_sequence(i);

    return 0;
}
