/* SO 22395738 */
#include <stdio.h>

int rc;
int foo(int a, int b);
int bar(int a, char *b, int *c);

extern void LogRet(const char *fn, const char *file, const char *from, int ln, int ret);

void LogRet(const char *fn, const char *file, const char *from, int ln, int ret)
{
    printf("%s.%s.%d: %s()  ret:%08x\n", file, from, ln, fn, ret);
}

#define foo(args, ...)  (rc = (foo)(args, ##__VA_ARGS__), LogRet("foo", __FILE__, __FUNCTION__, __LINE__, rc), rc)

#define bar(args, ...)  (rc = (bar)(args, ##__VA_ARGS__), LogRet("bar", __FILE__, __FUNCTION__, __LINE__, rc), rc)

extern void caller1(void);

void caller1(void)
{
    int d;
    int e = foo(1, 2);
    int f = bar(3, "abc", &d);
    printf("--" __FILE__ ":" __FUNCTION__ "():\n");
    printf("%s(): %d + %d + %d = %d\n", __func__, d, e, f, d + e + f);
}

#undef foo
#undef bar

#define WRAPPER(func, ...) ((rc = (func)(__VA_ARGS__)), LogRet(#func, __FILE__, __func__, __LINE__, rc), rc)

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
