/* SO 7274-3429 */
#define _GNU_SOURCE /* needed for vasprintf */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
static int fmt_print(const char *fmt, ...)
{
    int res = 0;
    int bytes = 0;
    char *buf;
    int len;
    va_list ap;

    va_start(ap, fmt);
    if ((len = vasprintf(&buf, fmt, ap)) < 0) {
        va_end(ap);
        return -1;
    }
    va_end(ap);

    printf("FORMAT STRING: %s\n", fmt);
    printf("Message:\n%s[END]", buf);
    return res;
}

static int fmt_print2(va_list ap, const char *fmt, ...)
{
    int res = 0;
    int bytes = 0;
    char *buf;
    int len;

    //va_start(ap, fmt);
    if ((len = vasprintf(&buf, fmt, ap)) < 0) {
        va_end(ap);
        return -1;
    }
    //va_end(ap);

    printf("FORMAT STRING: %s\n", fmt);
    printf("Message:\n%s[END]", buf);
    return res;
}
#pragma GCC diagnostic pop

static void do_print(const char *name, const char *fmt, ...)
{
    va_list ap;
    char buf[200];
    snprintf(buf, sizeof(buf), "%s%s%s", "Name:%s\r\ID:%d\r\n", fmt, "\r\n\r\n");

    // send Name:%s\r\ID:%d\r\nKey1:%s\r\nKey2:%d\r\nKey3:%s fmt string + all args.

    //fmt_print2(ap, buf, name, 42);

    va_start(ap, fmt);
    fmt_print(buf, name, 42);
    va_end(ap);
}

int main()
{
    do_print("TestName", "Key1:%s\r\nKey2:%d\r\nKey3:%s", "Bob", 4, "Alice");

    // This is also valid:
    // fmt_print("Login", "Username:%s\r\nPassword:%s", username, password);

    return 0;
}
