#include "logic.h"

#if 0
void word_not_0(word *R, word *A)
{
    for (int i = 0; i<16; i++)
    {
        if ((A+i))
            {*(R+i) = ZERO;}
        else
            {*(R+i) = ONE; }
    }
}
#endif /* 0|1 */

void word_not_1(word *R, word *A)
{
    for (int i = 0; i < 16; i++)
    {
        if ((*A)[i])
            (*R)[i] = ZERO;
        else
            (*R)[i] = ONE;
    }
}

void word_not_2(word *R, word *A)
{
    for (int i = 0; i < 16; i++)
        (*R)[i] = !(*A)[i];
}

void word_not_3(word R, word A)
{
    for (int i = 0; i < 16; i++)
    {
        if (A[i])
            R[i] = ZERO;
        else
            R[i] = ONE;
    }
}

void word_not_4(word R, word A)
{
    for (int i = 0; i < 16; i++)
        R[i] = !A[i];
}

#include <stdio.h>

int main(void)
{
    word in =
    {
        ZERO,  ONE, ZERO, ONE,
        ONE,  ZERO, ONE,  ZERO,
        ZERO, ZERO, ONE,  ONE,
        ONE,  ONE,  ZERO, ZERO,
    };
    word out1;
    word out2;
    word out3;
    word out4;

    word_not_1(&out1, &in);
    word_not_2(&out2, &in);
    word_not_3(out3, in);
    word_not_4(out4, in);

    for (int i = 0; i < 16; i++)
        printf("%d: %d %d %d %d\n", in[i], out1[i], out2[i], out3[i], out3[i]);
    printf("sizeof(BIT) = %zu; sizeof(word) = %zu\n", sizeof(BIT), sizeof(word));
    return 0;
}
