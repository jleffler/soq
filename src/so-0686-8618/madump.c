#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

extern void A(int *base, int ndims, ...);
extern void B(void);

void A(int *base, int ndims, ...)
{
    va_list args;
    int dims[ndims];
    int size = 1;
    va_start(args, ndims);
    assert(ndims > 0);
    for (int i = 0; i < ndims; i++)
    {
        dims[i] = va_arg(args, int);
        size *= dims[i];
    }
    int mods[ndims];
    for (int i = 0; i < ndims; i++)
    {
        int v = size;
        for (int j = 0; j <= i; j++)
            v /= dims[j];
        mods[i] = v;
    }
    for (int offset = 0; offset < size; offset++)
    {
        printf("%s", "array");
        for (int i = 0; i < ndims; i++)
        {
            int p = offset / mods[i];
            printf("[%d]", p % dims[i]);
        }
        printf(" = %d\n", base[offset]);
    }
}

void B(void)
{
    enum { dim1 = 4, dim2 = 6 };
    int array1[dim1][dim2] =
    {
        {  0,  1,  2,  3,  4,  5 },
        { 22, 21, 20, 19, 18, 17 },
        { 32, 31, 30, 39, 38, 37 },
        { 42, 41, 40, 49, 48, 47 },
    };
    int array2[dim2][dim1][dim2] =
    {
        {
            { 15, 68, 67, 16, 105,  4 },
            { 25, 58, 67, 16, 115,  4 },
            { 35, 48, 67, 16, 125,  4 },
            { 45, 38, 67, 16, 135,  4 },
        },
        {
            { 19, 69, 77, 16, 205,  5 },
            { 29, 59, 77, 16, 215,  5 },
            { 39, 49, 77, 16, 225,  5 },
            { 49, 39, 77, 16, 235,  5 },
        },
        {
            { 12, 64, 87, 16, 305,  6 },
            { 22, 54, 87, 16, 315,  6 },
            { 32, 44, 87, 16, 325,  6 },
            { 42, 34, 87, 16, 335,  6 },
        },
        {
            { 17, 63, 97, 16, 405,  7 },
            { 27, 53, 67, 16, 415,  7 },
            { 37, 43, 97, 16, 425,  7 },
            { 47, 33, 97, 16, 435,  7 },
        },
        {
            { 10, 60, 90, 10, 500, 97 },
            { 20, 50, 60, 20, 510, 87 },
            { 30, 40, 90, 30, 520, 77 },
            { 40, 30, 90, 40, 530, 67 },
        },
        {
            { 11, 63, 97, 36, 605, 39 },
            { 21, 53, 67, 46, 615, 38 },
            { 31, 43, 97, 56, 625, 27 },
            { 41, 33, 97, 66, 635, 26 },
        },
    };
    A(&array1[0][0],    2, dim1, dim2);
    A(&array2[0][0][0], 3, dim2, dim1, dim2);
}

int main(void)
{
    B();
    return(0);
}
