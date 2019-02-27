/* SO 5011-0992 */
#include "posixver.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { MAX = 100 };

int main(void)
{
    if (freopen("input.txt", "r", stdin) == 0)
	return 1;
    char s[MAX];

    char *ret = fgets(s, MAX, stdin);
    while (ret != NULL)
    {
        // Commenting out this region fixes the issue
        int status;
        pid_t pid = fork();
        if (pid == 0)
        {
            exit(0);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
        // End region
        printf("%s", s);
        ret = fgets(s, MAX, stdin);
    }
    return 0;
}
