int cmpint(const void *v1, const void *v2)  /* Ascending */
{
    int i1 = *(int *)v1;
    int i2 = *(int *)v2;
    return (i1 > i2) - (i1 < i2);
}
