#include <stdarg.h>
#include <stdio.h>

static void test_ptr(const char *fmt, va_list *argp)
{
    int x;
    x = va_arg(*argp, int);
    printf(fmt, x);
}

static void test_val(const char *fmt, va_list args)
{
    test_ptr(fmt, &args);
}

static void test(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    test_val(fmt, args);
    va_end(args);
    va_start(args, fmt);
    test_ptr(fmt, &args);
    va_end(args);
}

int main(void)
{
    test("%d", 3);
    return 0;
}
