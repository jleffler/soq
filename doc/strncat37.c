#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char target[40];
    char *source[] = { "Just the thirty-one characters.", "More than thirty-one characters." };
    enum { NUM_SOURCES = sizeof(source) / sizeof(source[0]) };

    for (int i = 0; i < NUM_SOURCES; i++)
    {
        for (int size = 30; size < 34; size++)
        {
            memset(target, 'X', sizeof(target));
            target[0] = '\0';
            strncat(target, source[i], size);
            size_t rlen = strlen(target);
            printf("%d: source [%s] len %zu, size %d: result [%s] len %zu %s\n",
                    i, source[i], strlen(source[i]), size, target, rlen,
                    target[size] == 'X' ? "OK" : "Oops!");
        }
    }

    char dst[24] = "Clownfish: ";
    char src[] = "Marvin and Nemo";
    size_t len = strlen(dst);
    strncat(dst, src, sizeof(dst) - len - 1);
    printf("%zu: [%s]\n", strlen(dst), dst);

    strcpy(dst, "Clownfish: ");
    assert(len < sizeof(dst) - 1);
    strncat(dst + len, src, sizeof(dst) - len - 1);
    printf("%zu: [%s]\n", strlen(dst), dst);

    return 0;
}
