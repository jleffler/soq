/* SO 7274-3429 */
#define _GNU_SOURCE /* needed for vasprintf */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PRINTFLIKE)
#if defined(__GNUC__)
#define PRINTFLIKE(n, m) __attribute__((format(printf, n, m)))
#else
#define PRINTFLIKE(n, m) /* If only */
#endif /* __GNUC__ */
#endif /* PRINTFLIKE */

/* Attributes can go after the declarator in a function declaration, but not in a function definition */
static int fmt_print(const char *fmt1, va_list ap1, const char *fmt2, ...) PRINTFLIKE(3, 4);
static void do_print(const char *name, const char *fmt, ...) PRINTFLIKE(2, 3);

static int fmt_print(const char *fmt1, va_list ap1, const char *fmt2, ...)
{
    char *buf1;
    char *buf2;
    int len1;
    int len2;
    va_list ap2;
    char *buffer;

    printf("%s(): fmt1 = [[%s]]\n", __func__, fmt1);
    len1 = vasprintf(&buf1, fmt1, ap1);
    printf("%s(): buf1 = [[%s]]\n", __func__, buf1);

    printf("%s(): fmt2 = [[%s]]\n", __func__, fmt2);
    va_start(ap2, fmt2);
    len2 = vasprintf(&buf2, fmt2, ap2);
    va_end(ap2);
    printf("%s(): buf2 = [[%s]]\n", __func__, buf2);

    if (len1 < 0 || len2  < 0)
        return -1;

    printf("%s(): Format strings:\n[[%s]]\n[[%s]]\n", __func__, fmt1, fmt2);
    printf("%s(): Message strings:\n[[%s]]\n[[%s]]\n[END]\n", __func__, buf1, buf2);
    buffer = malloc(len1 + len2 + sizeof("\r\n\r\n"));
    if (buffer == 0)
    {
        free(buf1);
        free(buf2);
        return -1;
    }
    strcpy(buffer, buf2);
    strcpy(buffer + len2, buf1);
    strcpy(buffer + len2 + len1, "\r\n\r\n");
    printf("Full buffer: [[%s]]\n", buffer);
    free(buf1);
    free(buf2);
    free(buffer);
    return 0;
}

static void do_print(const char *name, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fmt_print(fmt, ap, "Name:%s\r\nID:%d\r\n", name, 42);
    va_end(ap);
}

int main(void)
{
    do_print("TestName", "Key1:%s\r\nKey2:%d\r\nKey3:%s", "Bob", 4, "Alice");
    return 0;
}
