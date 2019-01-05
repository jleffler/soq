#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (argc == 2)
        data = argv[1];
    char spare1[16] = "abc";
    char buffer[16] = "";
    char spare2[16] = "xyz";
    strncat(buffer, data, sizeof(buffer));
    printf("%zu: [%s]\n", strlen(buffer), buffer);
    printf("spare1 [%s]\n", spare1);
    printf("spare2 [%s]\n", spare2);
    return 0;
}
