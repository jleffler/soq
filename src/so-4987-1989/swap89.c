/* SO 5055-9106 - answer for this question */
/* SO 4987-1989 - the answer to this also has a generic_swap() which is very similar! */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(USE_GENSWAP_1) && !defined(USE_GENSWAP_2) && !defined(USE_GENSWAP_3)
#define USE_GENSWAP_1
#endif

extern void generic_swap(void *v1, void *v2, size_t size);

#ifdef USE_GENSWAP_1
void generic_swap(void *v1, void *v2, size_t size)
{
    char temp[size];
    memmove(temp, v1, size);
    memmove(v1, v2, size);
    memmove(v2, temp, size);
}
#endif

#ifdef USE_GENSWAP_2
void generic_swap(void *v1, void *v2, size_t size)
{
    size_t chunk = (size > 1024) ? 1024 : size;
    size_t offset = 0;
    char *s1 = v1;
    char *s2 = v2;
    char  temp[chunk];
    while (size > 0)
    {
        size_t length = (size > chunk) ? chunk : size;
        memmove(temp, s1 + offset, length);
        memmove(s1 + offset, s2 + offset, length);
        memmove(s2 + offset, temp, length);
        size -= length;
        offset += length;
    }
}
#endif

#ifdef USE_GENSWAP_3
void generic_swap(void *v1, void *v2, size_t size)
{
    void *v3 = malloc(size);
    if (v3 != 0)
    {
        memmove(v3, v1, size);
        memmove(v1, v2, size);
        memmove(v2, v3, size);
        free(v3);
    }
}
#endif

static size_t min_len(size_t x, size_t y) { return (x < y) ? x : y; }

static void dump_long_buffer(const char *tag, size_t length, char buffer[length])
{
    int maxpadlen = strlen(tag) + sizeof(" = ") - 1;
    printf("%s = ", tag);
    size_t offset = 0;
    int padlen = 0;
    while (length > 0)
    {
        int linelen = min_len(length, 80 - maxpadlen - sizeof("[]\n"));
        printf("%*s[%.*s]\n", padlen, "", linelen, buffer + offset);
        offset += linelen;
        length -= linelen;
        padlen = maxpadlen;
    }
}

int main(void)
{
    int i = 37;
    int j = 99;

    printf("i = %d; j = %d\n", i, j);
    generic_swap(&i, &j, sizeof(i));
    printf("i = %d; j = %d\n", i, j);

    char data[80] = "A tabloid writer's nightmare on steroids";
    char info[80] = "Obsequiousness will get you nowhere fast";

    printf("data = [%s]\ninfo = [%s]\n", data, info);
    generic_swap(data, info, sizeof(data));
    printf("data = [%s]\ninfo = [%s]\n", data, info);

    char maxibuff1[2560];
    char maxibuff2[2560];

    for (size_t k = 0; k < sizeof(maxibuff1); k++)
    {
        maxibuff1[k] = k % 64 + '!';
        maxibuff2[k] = 'z' - k % 64;
    }

    /* The aligned output is mostly the result of serendipity */
    dump_long_buffer("maxibuff1", sizeof(maxibuff1), maxibuff1);
    dump_long_buffer("maxibuff2", sizeof(maxibuff2), maxibuff2);
    generic_swap(maxibuff1, maxibuff2, sizeof(maxibuff1));
    dump_long_buffer("maxibuff1", sizeof(maxibuff1), maxibuff1);
    dump_long_buffer("maxibuff2", sizeof(maxibuff2), maxibuff2);

    return 0;
}

