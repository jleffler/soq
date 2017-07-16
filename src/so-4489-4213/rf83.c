#include <stdlib.h>
#include <string.h>

enum { MAX_RESIDUE = 64 };

static inline size_t max_size(size_t x, size_t y) { return (x > y) ? x : y; }

static char *str_gsub(const char *haystack, const char *old_needle, const char *new_needle)
{
    size_t h_len = strlen(haystack);
    size_t o_len = max_size(strlen(old_needle), 1);
    size_t n_len = strlen(new_needle);

    size_t r_len = max_size(h_len, (h_len / o_len + 1) * n_len) + 1;
    //printf("h_len = %zu; o_len = %zu; n_len = %zu; r_len = %zu\n", h_len, o_len, n_len, r_len);
    char *result = malloc(r_len);
    if (result == 0)
        return 0;
    char *dst = result;
    const char *src = haystack;
    char *rep;
    while ((rep = strstr(src, old_needle)) != 0)
    {
        size_t p_len = rep - src;
        memmove(dst, src, p_len);
        dst += p_len;
        memmove(dst, new_needle, n_len);
        dst += n_len;
        src = rep + o_len;
        //printf("res = [%.*s]\n", (int)(dst - result), result);
        //printf("src = [%s]\n", src);
    }
    size_t t_len = h_len - (src - haystack) + 1;
    //printf("src = %zu [%s]\n", strlen(src), src);
    memmove(dst, src, t_len);
    dst += t_len;
    size_t x_len = dst - result + 1;

    if (r_len > MAX_RESIDUE && x_len < r_len - MAX_RESIDUE)
    {
        char *trunc = realloc(result, x_len);
        if (trunc != 0)
            result = trunc;
    }

    return result;
}

#include <stdio.h>
#include "timer.h"
#include <time.h>

static char data[] =
    "A 2345678901234567890123456789012345678901234567890 "
    "B 2345678901234567890123456789012345678901234567890 "
    "C 2345678901234567890123456789012345678901234567890 "
    "D 2345678901234567890123456789012345678901234567890 "
    "E 2345678901234567890123456789012345678901234567890 "
    "F 2345678901234567890123456789012345678901234567890 "
    "G 2345678901234567890123456789012345678901234567890 "
    "H 2345678901234567890123456789012345678901234567890 "
    "I 2345678901234567890123456789012345678901234567890 "
    "J 2345678901234567890123456789012345678901234567890 "
    "K 2345678901234567890123456789012345678901234567890 "
    "L 2345678901234567890123456789012345678901234567890 "
    "M 2345678901234567890123456789012345678901234567890 "
    "N 2345678901234567890123456789012345678901234567890 "
    "O 2345678901234567890123456789012345678901234567890 "
    "P 2345678901234567890123456789012345678901234567890 "
    "Q 2345678901234567890123456789012345678901234567890 "
    "R 2345678901234567890123456789012345678901234567890 "
    "S 2345678901234567890123456789012345678901234567890 "
    "T 2345678901234567890123456789012345678901234567890 "
    "U 2345678901234567890123456789012345678901234567890 "
    "V 2345678901234567890123456789012345678901234567890 "
    "W 2345678901234567890123456789012345678901234567890 "
    "X 2345678901234567890123456789012345678901234567890 "
    "Y 2345678901234567890123456789012345678901234567890 "
    "Z 2345678901234567890123456789012345678901234567890 "
    ;

enum { MAX_COUNT = 80000 };

typedef char *(Replace)(const char *haystack, const char *needle, const char *thread);

static void test_replace(const char *tag, Replace replace)
{
    int len = strlen(data);
    char *source = strdup(data);
    Clock clk;
    clk_init(&clk);
    clk_start(&clk);
    for (int current = 0; current < MAX_COUNT; current++)
    {
        strcpy(source, data);
        for (int i = 0; i < 20; i++)
            source[rand() % len] = (rand() % 10) + '0';
        //printf("Source: [%s]\n", source);
        char find[2] = { (rand() % 10) + '0', '\0' };
        //printf("Needle: [%s]\n", find);
        char *temp = replace(source, find, "black");
        //printf("Target: [%s]\n", temp);
        free(temp);
    }
    clk_stop(&clk);
    char buffer[32];
    printf("%-10s %12s\n", tag, clk_elapsed_us(&clk, buffer, sizeof(buffer)));
    free(source);
}

static void test_replace_values(const char *needle, const char *thread, Replace replace)
{
    int len = strlen(data);
    char *source = strdup(data);
    strcpy(source, data);
    for (int i = 0; i < 20; i++)
        source[rand() % len] = (rand() % 10) + '0';
    printf("Source: [%s]\n", source);
    printf("Needle: [%s]\n", needle);
    printf("Thread: [%s]\n", thread);
    char *temp = replace(source, needle, thread);
    printf("Target: [%s]\n", temp);
    free(temp);
    free(source);
}

int main(void)
{
    srand(time(0));

    test_replace("str_gsub", str_gsub);

    test_replace_values("23",      "black",   str_gsub);
    test_replace_values("234",     "white",   str_gsub);
    test_replace_values("2345",    "green",   str_gsub);
    test_replace_values("23456",   "orange",  str_gsub);
    test_replace_values("234567",  "yellow",  str_gsub);
    test_replace_values("1234567", "magenta", str_gsub);
    //test_replace_values("",        "cyan",    str_gsub);
    test_replace_values("1234",    "",        str_gsub);

    return 0;
}
