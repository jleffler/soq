/* SO 5380-3837 */
/* Sort array of arrays of 6 integers on index positions 3, 4 */
/* Code with file scope array that is passed as a parameter to the sort code */
#include <stdio.h>
#include <stdlib.h>

enum { NUM_VALUES = 6 };

static void copy_row(int source[NUM_VALUES], int target[NUM_VALUES])
{
    for (int i = 0; i < NUM_VALUES; i++)
        target[i] = source[i];
}

static void bubbleSort(int arraySize, int sortedArray[][NUM_VALUES])
{
    int tempEntry[6];
    for (int i = 0; i < arraySize - 1; i++)
    {
        for (int j = 0; j < arraySize - 1 - i; j++)
        {
            if ((sortedArray[j][3] > sortedArray[j + 1][3]) ||
                (sortedArray[j][3] == sortedArray[j + 1][3] &&
                 sortedArray[j][4] >  sortedArray[j + 1][4]))
            {
                copy_row(sortedArray[j], tempEntry);
                copy_row(sortedArray[j+1], sortedArray[j]);
                copy_row(tempEntry, sortedArray[j+1]);
            }
        }
    }
}

static void print_array(const char *tag, size_t size, int data[size][NUM_VALUES])
{
    printf("%s (%zux%d):\n", tag, size, NUM_VALUES);
    for (size_t i = 0; i < size; i++)
    {
        printf("%3zu:", i);
        for (int j = 0; j < NUM_VALUES; j++)
            printf(" %3d", data[i][j]);
        putchar('\n');
    }
}

static int array1[][NUM_VALUES] =
{
    // random -n 30 -T '%d %d %d %d %d %d' 10 29 |
    // commalist -n 6 -B 4 -b '{ ' -w -W 3 -T ' },'
    {  25,  18,  29,  25,  12,  18, },
    {  29,  29,  24,  23,  26,  28, },
    {  16,  22,  10,  15,  23,  29, },
    {  27,  22,  16,  27,  19,  24, },
    {  17,  18,  10,  20,  15,  24, },
    {  21,  11,  19,  15,  13,  15, },
    {  16,  11,  19,  13,  10,  25, },
    {  17,  17,  15,  27,  26,  24, },
    {  12,  23,  24,  28,  24,  15, },
    {  11,  21,  25,  15,  18,  25, },
    {  12,  14,  25,  11,  13,  29, },
    {  16,  12,  11,  21,  19,  28, },
    {  18,  16,  20,  17,  15,  11, },
    {  13,  18,  11,  23,  23,  18, },
    {  29,  16,  29,  10,  22,  28, },
    {  13,  15,  24,  24,  28,  26, },
    {  28,  26,  13,  27,  18,  27, },
    {  10,  29,  18,  15,  24,  29, },
    {  24,  24,  27,  24,  21,  12, },
    {  10,  28,  12,  11,  27,  25, },
    {  12,  21,  28,  27,  11,  14, },
    {  19,  17,  11,  18,  25,  23, },
    {  19,  21,  10,  21,  20,  22, },
    {  18,  29,  12,  15,  28,  22, },
    {  25,  16,  15,  23,  27,  21, },
    {  28,  16,  11,  10,  24,  23, },
    {  29,  19,  22,  20,  28,  27, },
    {  16,  21,  17,  16,  25,  15, },
    {  11,  23,  17,  19,  27,  13, },
    {  12,  15,  18,  16,  26,  14, },
};
enum { ROWS_ARRAY1 = sizeof(array1) / sizeof(array1[0]) };

static int array2[][NUM_VALUES] =
{
    // random -N 15:20 -T '%d %d %d %d %d %d' 70 79 |
    // commalist -n 6 -B 4 -b '{ ' -w -W 3 -T ' },'
    {  73,  74,  79,  71,  76,  78, },
    {  78,  77,  79,  75,  76,  70, },
    {  72,  72,  74,  76,  78,  79, },
    {  76,  73,  76,  78,  79,  74, },
    {  70,  76,  74,  74,  74,  79, },
    {  74,  79,  71,  71,  75,  77, },
    {  73,  76,  73,  74,  74,  77, },
    {  71,  76,  70,  74,  73,  77, },
    {  73,  70,  76,  76,  75,  77, },
    {  73,  72,  71,  73,  70,  75, },
    {  70,  76,  73,  72,  79,  70, },
    {  78,  75,  74,  71,  76,  73, },
    {  75,  74,  72,  79,  77,  78, },
    {  73,  75,  79,  79,  74,  70, },
    {  73,  76,  72,  70,  70,  77, },
    {  75,  77,  70,  76,  79,  75, },
    {  75,  73,  71,  76,  74,  72, },
    {  74,  79,  78,  74,  75,  71, },
    {  78,  74,  75,  79,  77,  78, },
};
enum { ROWS_ARRAY2 = sizeof(array2) / sizeof(array2[0]) };

static int array3[][NUM_VALUES] =
{
    // random -n 20 -T '%d %d %d %d %d %d' 170 185 |
    // commalist -n 6 -B 4 -b '{ ' -w -W 3 -T ' },'
    { 178, 174, 185, 178, 179, 171, },
    { 176, 185, 183, 175, 180, 176, },
    { 172, 184, 173, 175, 181, 179, },
    { 176, 174, 180, 180, 182, 179, },
    { 182, 181, 170, 181, 170, 180, },
    { 173, 174, 178, 172, 176, 170, },
    { 181, 185, 184, 174, 176, 179, },
    { 175, 170, 174, 170, 177, 174, },
    { 180, 172, 178, 176, 170, 176, },
    { 174, 180, 184, 175, 170, 173, },
    { 185, 174, 182, 185, 177, 179, },
    { 175, 181, 174, 183, 172, 182, },
    { 179, 171, 170, 181, 185, 170, },
    { 182, 182, 180, 182, 181, 170, },
    { 179, 177, 184, 182, 177, 174, },
    { 170, 184, 172, 172, 180, 176, },
    { 172, 171, 183, 178, 179, 182, },
    { 177, 174, 171, 183, 181, 174, },
    { 173, 175, 175, 178, 182, 171, },
    { 181, 177, 178, 171, 171, 179, },
};
enum { ROWS_ARRAY3 = sizeof(array3) / sizeof(array3[0]) };

int main(void)
{
    print_array("Before", ROWS_ARRAY1, array1);
    bubbleSort(ROWS_ARRAY1, array1);
    print_array("After", ROWS_ARRAY1, array1);

    print_array("Before", ROWS_ARRAY2, array2);
    bubbleSort(ROWS_ARRAY2, array2);
    print_array("After", ROWS_ARRAY2, array2);

    print_array("Before", ROWS_ARRAY3, array3);
    bubbleSort(ROWS_ARRAY3, array3);
    print_array("After", ROWS_ARRAY3, array3);

    return 0;
}
