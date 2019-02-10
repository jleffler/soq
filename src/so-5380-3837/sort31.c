/* SO 5380-3837 */
/* Sort array of arrays of 6 integers on index positions 3, 4 */
/* More or less the code provided by the OP */

#include <stdio.h>
#include <stdlib.h>

enum { NUM_VALUES = 6 };
enum { NUM_OF_ELEMENTS_IN_ARRAY = NUM_VALUES };

static int sortedArray[][NUM_VALUES] =
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

enum { NUM_ROWS = sizeof(sortedArray) / sizeof(sortedArray[0]) };

static void copyTripleToArray(int PrimitivePythagoreanTriple[], int index, int buffer, int tempArray[])
{
    //if (buffer == 1)
    //{
        //for (int i = 0; i < NUM_OF_ELEMENTS_IN_ARRAY; i++)
            //outputBuffer[index][i] = PrimitivePythagoreanTriple[i];
    //}
    //else if (buffer == 0)
    if (buffer == 0)
    {
        for (int i = 0; i < NUM_OF_ELEMENTS_IN_ARRAY; i++)
            sortedArray[index][i] = PrimitivePythagoreanTriple[i];
        return;
    }
    else
    {
        for (int i = 0; i < NUM_OF_ELEMENTS_IN_ARRAY; i++)
            tempArray[i] = PrimitivePythagoreanTriple[i];
    }
}

static void bubbleSort(int arraySize)
{
    int tempEntry[6];
    for (int i = 0; i < arraySize - 1; i++)
    {
        for (int j = 0; j < arraySize - 1 - i; j++)
        {
            if (sortedArray[j][3] > sortedArray[j + 1][3])
            {
                copyTripleToArray(sortedArray[j], 0, 2, tempEntry);
                copyTripleToArray(sortedArray[j + 1], j, 0, NULL);
                copyTripleToArray(tempEntry, j + 1, 0, NULL);
            }
            if (sortedArray[j][3] == sortedArray[j + 1][3] &&
                sortedArray[j][4] >  sortedArray[j + 1][4])
            {
                copyTripleToArray(sortedArray[j], 0, 2, tempEntry);
                copyTripleToArray(sortedArray[j + 1], j, 0, NULL);
                copyTripleToArray(tempEntry, j + 1, 0, NULL);
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

int main(void)
{
    print_array("Before", NUM_ROWS, sortedArray);
    bubbleSort(NUM_ROWS);
    print_array("After", NUM_ROWS, sortedArray);
    return 0;
}
