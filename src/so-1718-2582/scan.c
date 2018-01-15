/* SO 1718-2582 */

/*
** Consider if you are dealing with a file formatted with data such as
** `centre (23, 41) size (19, 42)`, then your format string is likely to
** be `"centre (%d ,%d ) size (%d ,%d )"`.  This is nearly sound.
** However, there is no way with that format to spot that the second
** close parenthesis is missing.  To be sure that it is read and
** present, you'd need a format string like `"centre (%d ,%d ) size (%d
** ,%d %[)]"`, where the space before the `%[)]` allows for spaces after
** the digits, and the scan set requires a close parenthesis.  You would
** test that the `scanf()` returned 5 fields.
*/

#include <stdio.h>

int main(void)
{
    int x1, y1, x2, y2;
    char str[10];
    const char *data[] =
    {
        "centre ( 19, 43 ) size ( 21, 37 )",
        "centre (19, 43) size (21, 37)",
        "centre (19, 43) size (21, 37",
        "centre(19,43) size(21,37)",
        "centre(19,43) size(21,37",
        "centre ( 19 , 43 ) size ( 21 , 37 )))",
    };
    enum { NUM_DATA = sizeof(data) / sizeof(data[0]) };

    const char *format5[] =
    {
        "centre (%d ,%d ) size (%d ,%d %[)]",
        "centre (%d,%d) size (%d,%d%[)]",
    };
    enum { NUM_FORMAT5 = sizeof(format5) / sizeof(format5[0]) };

    const char *format4[] =
    {
        "centre (%d ,%d ) size (%d ,%d )",
        "centre (%d,%d) size (%d,%d)",
    };
    enum { NUM_FORMAT4 = sizeof(format4) / sizeof(format4[0]) };

    printf("Format 5\n");
    for (int i = 0; i < NUM_FORMAT5; i++)
    {
        printf("Format:    <<%s>>\n", format5[i]);
        for (int j = 0; j < NUM_DATA; j++)
        {
            int rc;
            printf("   Data:   <<%s>>\n", data[j]);
            if ((rc = sscanf(data[j], format5[i], &x1, &y1, &x2, &y2, str)) != 5)
                printf("!! Failed: scanf() returned %d\n", rc);
            else
                printf("== Passed: centre(%d,%d) size(%d,%d) <<%s>>\n", x1, y1, x2, y2, str);
        }
    }

    printf("\nFormat 4\n");
    for (int i = 0; i < NUM_FORMAT4; i++)
    {
        printf("Format:    <<%s>>\n", format4[i]);
        for (int j = 0; j < NUM_DATA; j++)
        {
            int rc;
            printf("   Data:   <<%s>>\n", data[j]);
            if ((rc = sscanf(data[j], format4[i], &x1, &y1, &x2, &y2)) != 4)
                printf("!! Failed: scanf() returned %d\n", rc);
            else
                printf("== Passed: centre(%d,%d) size(%d,%d)\n", x1, y1, x2, y2);
        }
    }

    printf("\nFormat 6\n");
    int len, rc;
    const char format6[] = "centre (%d ,%d ) size (%d ,%d %1[)]%n";
    printf("Format:    <<%s>>\n", format6);
    printf("   Data:   <<%s>>\n", data[5]);
    if ((rc = sscanf(data[5], format6, &x1, &y1, &x2, &y2, str, &len)) != 5)
        printf("!! Failed: scanf() returned %d\n", rc);
    else
        printf("== Passed: centre(%d,%d) size(%d,%d) len=%d <<%s>>\n", x1, y1, x2, y2, len, &data[5][len]);

    return 0;
}
