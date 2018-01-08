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
        int val;
        char data[4];
        int off = 0;
        int len = strlen(line);
        while (off < len)
        {
            memmove(data, line + off, 3);
            data[3] = '\0';
            if (sscanf(data, "%d", &val) != 1)
            {
                fprintf(stderr, "Oops! [%s]\n", data);
                break;
            }
            printf("Got: [%s] - [%s] = %d\n", data, line + off, val);
            off += 3;
            nbr[num++] = val;
        }

        for (int i = 0; i < num; i++)
            printf("%3d", nbr[i]);
        putchar('\n');
    }
    return 0;
}
