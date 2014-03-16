/* SO 22395738 */
#include <stdio.h>

int foo(int a, int b);
int bar(int a, char *b, int *c);

extern int LogRet(const char *fn, const char *file, const char *from, int ln, int ret);

int LogRet(const char *fn, const char *file, const char *from, int ln, int ret)
{
    printf("%s.%s.%d: %s()  ret:%08x\n", file, from, ln, fn, ret);
    return ret;
}

#define foo(args, ...)  LogRet("foo", __FILE__, __FUNCTION__, __LINE__, (foo)(args, ##__VA_ARGS__))

#define bar(args, ...)  LogRet("bar", __FILE__, __FUNCTION__, __LINE__, (bar)(args, ##__VA_ARGS__))

extern void caller1(void);

void caller1(void)
{
    int d;
    int e = foo(1, 2);
    int f = bar(3, "abc", &d);
    printf("%s(): %d + %d + %d = %d\n", __func__, d, e, f, d + e + f);
}

#undef foo
#undef bar

#define WRAPPER(func, ...) LogRet(#func, __FILE__, __func__, __LINE__, (func)(__VA_ARGS__))

#define foo(...) WRAPPER(foo, __VA_ARGS__)
#define bar(...) WRAPPER(bar, __VA_ARGS__)

extern void caller2(void);

void caller2(void)
{
    int d;
    int e = foo(2, 3);
    int f = bar(3, "abc", &d);
    printf("%s(): %d + %d + %d = %d\n", __func__, d, e, f, d + e + f);
}

int (foo)(int a, int b)
{
    return (a + b) % 3;
}

int (bar)(int a, char *b, int *c)
{
    int d = b[a];
    *c = d;
    return a + d;
}

int main(void)
{
    caller1();
    caller2();
    return 0;
}
