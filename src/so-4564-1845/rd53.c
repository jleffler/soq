/* SO 4564-1845 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char line[4096];
    while (fgets(line, sizeof(line), stdin) != 0)
    {
        line[strcspn(line, "\n")] = '\0';
        int nbr[20];
        int num = 0;
        int n;
        int val;
        char data[4];
        int off = 0;
        while (sscanf(line + off, "%3c%n", data, &n) == 1)
        {
            data[n] = '\0';
            if (sscanf(data, "%d", &val) != 1)
            {
                fprintf(stderr, "Oops! [%s]\n", data);
                break;
            }
            printf("Got: [%s] - [%s] = %d (%d)\n", data, line + off, val, n);
            off += n;
            nbr[num++] = val;
        }

        for (int i = 0; i < num; i++)
            printf("%3d", nbr[i]);
        putchar('\n');
    }
    return 0;
}
