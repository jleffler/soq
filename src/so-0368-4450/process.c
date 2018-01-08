extern int processor(int x);

int processor(int x)
{
    extern int subprocess(int);
    int sum = 0;
    for (int i = 0; i < x; i++)
        sum += subprocess((x + 3) % 7);
    return sum;
}

extern int subprocess(int x);

int subprocess(int y)
{
    return (y * 13) % 37;
}
