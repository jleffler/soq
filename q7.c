#include <stdio.h>

const int c0 = (0.0299 * 128 + 0.5);
const int c1 = (0.4701 * 128 + 0.5);
const int c2 = (0.4701 * 128 + 0.5);
const int c3 = (0.0299 * 128 + 0.5);

const int half = (0.5000 * 128 + 0.5);

enum { Q7_BITS = 7 };

void put_q7(signed char out);
void firFixed(signed char input[4]);

void firFixed(signed char input[4])
{
    int sum = c0*input[0] + c1*input[1] + c2*input[2] + c3*input[3];
    signed char output = (signed char)((sum + half) >> Q7_BITS);
    put_q7(output);
}

void put_q7(signed char out)
{
    printf("out = %d\n", out);
}

int main(void)
{
    printf("c0 = c3 = %3d = 0x%.2X\n", c0, c0);
    printf("c1 = c2 = %3d = 0x%.2X\n", c1, c1);
    signed char data[] = { 27, 39, 69, 99, 82, 71, 42, 63 };
    for (size_t i = 0; i < sizeof(data) - 4; i++)
        firFixed(data + i);
    return 0;
}
