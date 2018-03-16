#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* odd numbers in ascending order before even numbers in descending order */
static int oddasc_evendesc(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if ((v1 & 1) != (v2 & 1))
    {
        /* One odd, one even */
        if (v1 & 1)
            return -1;      /* Odd is smaller */
        return +1;
    }
    /* Both odd or both even */
    if ((v1 & 1) == 1)
        return (v1 < v2) ? -1 : (v1 > v2) ? +1 : 0;     /* Ascending */
    return (v1 < v2) ? +1 : (v1 > v2) ? -1 : 0;         /* Descending */
}

/* even numbers descending before odd numbers ascending */
static int evendesc_oddasc(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if ((v1 & 1) != (v2 & 1))
    {
        /* One odd, one even */
        if (v1 & 1)
            return +1;      /* Odd is larger */
        return -1;
    }
    /* Both odd or both even */
    if ((v1 & 1) == 1)
        return (v1 > v2) - (v1 < v2);     /* Ascending */
    return (v1 < v2) - (v1 > v2);         /* Descending */
}

/* odd numbers in descending order before even numbers in ascending order */
static int odddesc_evenasc(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if ((v1 & 1) != (v2 & 1))
    {
        /* One odd, one even */
        if (v1 & 1)
            return -1;      /* Odd is smaller */
        return +1;
    }
    /* Both odd or both even */
    if ((v1 & 1) == 1)
        return (v1 < v2) ? +1 : (v1 > v2) ? -1 : 0;     /* Descending */
    return (v1 < v2) ? -1 : (v1 > v2) ? +1 : 0;         /* Ascending */
}

/* even numbers ascending before odd numbers descending */
static int evenasc_odddesc(const void *vp1, const void *vp2)
{
    int v1 = *(int *)vp1;
    int v2 = *(int *)vp2;
    if ((v1 & 1) != (v2 & 1))
    {
        /* One odd, one even */
        if (v1 & 1)
            return +1;      /* Odd is larger */
        return -1;
    }
    /* Both odd or both even */
    if ((v1 & 1) == 1)
        return (v1 < v2) - (v1 > v2);     /* Descending */
    return (v1 > v2) - (v1 < v2);         /* Ascending */
}

static void dump_array(const char *tag, int num, int *data)
{
    printf("%s:\n", tag);
    int i;
    const char *pad = "";
    for (i = 0; i < num; i++)
    {
        printf("%s%+3d", pad, data[i]);
        pad = " ";
        if (i % 10 == 9)
        {
            putchar('\n');
            pad = "";
        }
    }
    if (i % 10 != 0)
        putchar('\n');      /* End partial line */
    putchar('\n');          /* Blank line */
}

int main(void)
{
    int data1[] =
    {
        /* random -n 80 -- -99 99 | commalist -b '        ' -n 10 */
        +39, +36, +78, -92, +63, -21, -51, +49,   0, -77,
        -10, -49, -98, -17, +60, +83, +30, -97, -68, +86,
        +70, +84, -56,  +3, +33, -34, +14, -40, -72, -86,
        -95, -87, -73, -20, -72, -86,  -3, -71, -55, -80,
        -60,  -4, -26, -64, -31, -84, -79, +25, +41, +80,
        -54, -51, +24, -48, +13, +61, -99, +60,  -2, +16,
        -66, -30, +24, +88,  +5, -77, +13,  +3, +16, -69,
        -60, +26, +51, +16, -13, +71,  -9,  -2, +51, +72,
    };
    enum { NUM_DATA = sizeof(data1) / sizeof(data1[0]) };
    int data2[NUM_DATA];
    int data3[NUM_DATA];
    int data4[NUM_DATA];

    memmove(data2, data1, sizeof(data1));
    memmove(data3, data1, sizeof(data1));
    memmove(data4, data1, sizeof(data1));

    printf("Sort odd numbers ascending before even numbers descending\n");
    dump_array("Before", NUM_DATA, data1);
    qsort(data1, NUM_DATA, sizeof(data1[0]), oddasc_evendesc);
    dump_array("After", NUM_DATA, data1);

    printf("Sort even numbers descending before odd numbers ascending\n");
    dump_array("Before", NUM_DATA, data2);
    qsort(data2, NUM_DATA, sizeof(data2[0]), evendesc_oddasc);
    dump_array("After", NUM_DATA, data2);

    printf("Sort odd numbers descending before even numbers ascending\n");
    dump_array("Before", NUM_DATA, data3);
    qsort(data3, NUM_DATA, sizeof(data3[0]), odddesc_evenasc);
    dump_array("After", NUM_DATA, data3);

    printf("Sort even numbers ascending before odd numbers descending\n");
    dump_array("Before", NUM_DATA, data4);
    qsort(data4, NUM_DATA, sizeof(data4[0]), evenasc_odddesc);
    dump_array("After", NUM_DATA, data4);

    return 0;
}
