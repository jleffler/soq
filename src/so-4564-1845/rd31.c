/* SO 4564-1845 */
#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[4096];
    while (fgets(line, sizeof(line), stdin) != 0)
    {
        int nbr[20];
        int num = 0;
        int n;
        int val;
        int off = 0;
        while (sscanf(line + off, "%3d%n", &val, &n) == 1)
        {
            printf("Got: %d - [%s] %d\n", val, line + off, n);
            off += n;
            nbr[num++] = val;
        }

        for (int i = 0; i < num; i++)
            printf("%3d", nbr[i]);
        putchar('\n');
    }
    return 0;
}
