/* SO 4438-1848 */
/* Find the longest arithmetic progression from an array */
#include <stdio.h>

static void print_array(const char *tag, int size, int data[size], int do_delta)
{
    printf("%s [%d] = {", tag, size);
    const char *pad = "";
    if (size < 100)
    {
        for (int i = 0; i < size; i++)
        {
            printf("%s %d", pad, data[i]);
            pad = ",";
        }
    }
    else
        printf(" ...omitted... ");
    printf(" }");
    if (do_delta)
        printf(" delta = %d", data[1] - data[0]);
    putchar('\n');
}

static void test_array(int size, int data[size])
{
    int longest_length = 0;
    int longest_start  = 0;

    print_array("Data set", size, data, 0);

    for (int i = 0; i < size - 1; i++)
    {
        int diff = data[i+1]-data[i];
        int curr_length = 1;
        for (int j = i + 1; j < size - 1; j++)
        {
            if (data[j+1] - data[j] != diff)
                break;
            curr_length++;
        }
        if (curr_length > longest_length)
        {
            longest_length = curr_length;
            longest_start  = i;
        }
        i += curr_length - 1;
    }

    printf("Start %d: ", longest_start);
    print_array("LAP", longest_length + 1, &data[longest_start], 1);
}

#include <stdlib.h>
#include <time.h>

int main(void)
{
    printf("Longest arithmetic progressions\n");

    int array1[] = { 5, 1, 2, 4, 6, 8, 12 };
    enum { ARRAY1_SIZE = sizeof(array1) / sizeof(array1[0]) };
    test_array(ARRAY1_SIZE, array1);

    int array2[] = { 5, 1, 2, 4, 6, 8, 12, 9, 6, 3, 0, -3, -6, 2, 3, 4, 5 };
    enum { ARRAY2_SIZE = sizeof(array2) / sizeof(array2[0]) };
    test_array(ARRAY2_SIZE, array2);

    int array3[] = { 5, 6, 4, 5, 7, 8, 12, 9, 5, 3, 0, -1, -3, 2, 3, 7, 5 };
    enum { ARRAY3_SIZE = sizeof(array3) / sizeof(array3[0]) };
    test_array(ARRAY3_SIZE, array3);

    enum { MAX_SIZE = 1000000 };
    int array4[MAX_SIZE];
    srand(time(0));
    for (int i = 0; i < MAX_SIZE; i++)
        array4[i] = rand() % 10000;
    int delta = rand() % 1000 - 500;
    int fixed = rand() % 100;
    for (int i = rand() % (MAX_SIZE - fixed), l = i + fixed; i < l; i++)
        array4[i] = array4[i - 1] + delta;
    test_array(MAX_SIZE, array4);

    return 0;
}
