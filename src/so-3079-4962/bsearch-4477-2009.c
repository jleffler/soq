/* https://stackoverflow.com/questions/44772009/cs50-pset-3-binary-search-inconsistent-success-with-test-data */
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
