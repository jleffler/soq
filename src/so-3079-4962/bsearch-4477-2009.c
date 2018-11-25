/* SO 4477-2009 */
/* CS50 PSET 3 binary search inconsistent success with test data */

extern int binary_search(const int values[], int n, int value);

int binary_search(const int values[], int n, int value)
{
    int top = n - 1;
    int bottom = 0;
    while (top >= bottom)
    {
        int searchpos = bottom + (top - bottom) / 2;
        /*
        printf("T = %2d, B = %2d, M = %2d, V = %d, S = %d\n",
               top, bottom, searchpos, value, values[searchpos]);
        */
        if (value == values[searchpos])
        {
            return searchpos;
        }
        else if (value > values[searchpos])
        {
            bottom = searchpos + 1;
        }
        else // if (value < values[searchpos])
        {
            top = searchpos - 1;
        }
    }
    return -1;
}
