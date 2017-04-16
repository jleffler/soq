int cmpint(const void *a, const void *b)    /* Ascending */
{
    return (*(int *)b < *(int *)a) -
           (*(int *)a < *(int *)b);
}
