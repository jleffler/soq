#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_RESIDUE = 64 };

static int debug = 0;

static inline size_t max_size(size_t x, size_t y) { return (x > y) ? x : y; }

static char *str_gsub_matchnull(const char *haystack, const char *new_needle)
{
    size_t h_len = strlen(haystack);
    size_t n_len = strlen(new_needle);

    size_t r_len = (h_len + 1) * (n_len + 1);
    char *result = malloc(r_len);
    if (result == 0)
        return 0;
    char *dst = result;
    const char *src = haystack;
    const char *end = haystack + h_len;
    while (src <= end)
    {
        memmove(dst, new_needle, n_len);
        dst += n_len;
        *dst++ = *src++;
    }
    return result;
}

static char *str_gsub(const char *haystack, const char *old_needle, const char *new_needle)
{
    if (*old_needle == '\0')
        return str_gsub_matchnull(haystack, new_needle);
    size_t h_len = strlen(haystack);
    size_t o_len = strlen(old_needle);
    size_t n_len = strlen(new_needle);

    size_t r_len = max_size(h_len, (h_len / o_len + 1) * n_len) + 1;
    if (debug)
        printf("h_len = %zu; o_len = %zu; n_len = %zu; r_len = %zu\n", h_len, o_len, n_len, r_len);
    char *result = malloc(r_len);
    if (result == 0)
        return 0;
    char *dst = result;
    const char *src = haystack;
    const char *end = haystack + h_len;
    char *rep;
    if (debug)
        printf("src = [%s]\n", src);
    while (src < end && (rep = strstr(src, old_needle)) != 0)
    {
        size_t p_len = rep - src;
        memmove(dst, src, p_len);
        dst += p_len;
        memmove(dst, new_needle, n_len);
        dst += n_len;
        src = rep + o_len;
        if (debug)
            printf("src = [%s]\n", src);
    }
    size_t t_len = h_len - (src - haystack) + 1;
    if (debug)
        printf("src = %zu [%s]\n", strlen(src), src);
    memmove(dst, src, t_len);
    dst += t_len;
    size_t x_len = dst - result + 1;

    if (r_len > MAX_RESIDUE && x_len < r_len - MAX_RESIDUE)
    {
        if (debug)
            printf("r_len = %zu; x_len = %zu; saving = %zu\n", r_len, x_len, r_len - x_len);
        char *trunc = realloc(result, x_len);
        if (trunc != 0)
            result = trunc;
    }

    return result;
}

#include "timer.h"
#include <time.h>

static char speed[] =
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
static char correct[] =
    "A 2345678901234567890123456789012345678901234567890 "
    ;

#if 1
enum { MAX_COUNT = 80000 };
#else
enum { MAX_COUNT = 1 };
#endif

typedef char *(Replace)(const char *haystack, const char *needle, const char *thread);

static void test_replace(const char *tag, Replace replace)
{
    debug = 0;
    int len = strlen(speed);
    char *source = strdup(speed);
    Clock clk;
    clk_init(&clk);
    clk_start(&clk);
    for (int current = 0; current < MAX_COUNT; current++)
    {
        strcpy(source, speed);
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
    int len = strlen(correct);
    char *source = strdup(correct);
    strcpy(source, correct);
    for (int i = 0; i < 4; i++)
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
    test_replace_values("",        "cyan",    str_gsub);
    test_replace_values("1234",    "",        str_gsub);

    debug = 1;
    char same1[] = "AAAAAA";
    printf("Source: [%s]\n", same1);
    char *loop1 = str_gsub(same1, "A", "-quad-");
    printf("Target: [%s]\n", loop1);
    free(loop1);

    printf("Source: [%s]\n", same1);
    char *loop2 = str_gsub(same1, "", "-none-");
    printf("Target: [%s]\n", loop2);
    free(loop2);

    printf("Source: [%s]\n", "");
    char *loop3 = str_gsub("", "", "-none-");
    printf("Target: [%s]\n", loop3);
    free(loop3);

    printf("Source: [%s]\n", "");
    char *loop4 = str_gsub("", "", "");
    printf("Target: [%s]\n", loop4);
    free(loop4);

    printf("Source: [%s]\n", correct);
    char *loop5 = str_gsub(correct, "XYZ", "pqr");
    printf("Target: [%s]\n", loop5);
    free(loop5);

    printf("Source: [%s]\n", speed);
    char *loop6 = str_gsub(speed, "XYZ", "=wallaby=");
    printf("Target: [%s]\n", loop6);
    free(loop6);

    return 0;
}
