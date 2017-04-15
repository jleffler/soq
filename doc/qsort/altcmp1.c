int cmpint(const void *a, const void *b)
{
    return (*(int *)b < *(int *)a) -
           (*(int *)a < *(int *)b);
}
