### Stack Overflow Question 7274-3429

[SO 7274-3429](https://stackoverflow.com/q/72743429) &mdash;
Prepend variadic arguments and pass to another function

### Question
oI am having some trouble with a variadic printf-style function that I wrote, which works correctly when there are no variadic arguments but not when there are, e.g:

`do_print("TestName", "");` works.

`do_print("TestName", "Key1:%s\r\nKey2:%d\r\nKey3:%s", "Bob", 4, "Alice");` doesn't

I have done some debugging and I believe the issue is that the variadic arguments themselves are not getting processed as they should be. I looked at some examples and similar questions, and that has led me to believe that I'm misusing `va_start` and `va_end` in one of the functions. The format string that I'm generating is correct, but I'm getting a repeat for the first variadic arg of the name itself and then garbage values for the remaining variadic arguments:

```
Message:
Name:TestName
ID:42
Key1:TestName
Key2:-1
Key3:��-�*
```

(should be:)
```
Message:
Name:TestName
ID:42
Key1:Bob
Key2:4
Key3:Alice
```

My thought was perhaps that I should eliminate a `va_start` / `va_end` and just pass the ap in directly, although in certain cases I call the `fmt_print` function directly so I'm not sure what I would pass in for ap then. That's what I was playing with `fmt_print2` for, but right now that just segfaults and is even worse than the original.

And yes, I do need vasprintf. The code here is printf-style, but ultimately I do need the entire message in a single buffer because I then pass it to the `write` function, not a `printf`-style function, so `fmt_print` does need to do the work of combining everything into a single buffer.

Here is a full minimal reproducible example, which I've been testing here: https://www.onlinegdb.com/online_c_compiler

```
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
    snprintf(buf, sizeof(buf), "%s%s%s", "Name:%s\r\nID:%d\r\n", fmt, "\r\n\r\n");
    
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
    fmt_print("Login", "Name:%s\r\nID:%d\r\nUsername:%s\r\nPassword:%s", "Login", 41, username, password);

    return 0;
}
```

Could someone point me in the right direction of what approach is best suited for this?


### Answer

As I said before in a comment, you can't do what you are trying to do
the way you are trying to do it.  The `snprintf()` in `do_print()` is
trying to set a format string that requires two separate `va_list`
values to process it.  You will have to keep the two lots of formatting
separate.  And then, if necessary, combine the two strings.

This code works.  It contains a lot of diagnostic printing which you can
remove, but it showed me where things were going wrong.  It includes the
trailing `\r\n\r\n` as a separate operation.
```
/* SO 7274-3429 */
#define _GNU_SOURCE /* needed for vasprintf */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char buf[] = "Name:%s\r\nID:%d\r\n";

    va_start(ap, fmt);
    fmt_print(fmt, ap, buf, name, 42);
    va_end(ap);
}

int main(void)
{
    do_print("TestName", "Key1:%s\r\nKey2:%d\r\nKey3:%s", "Bob", 4, "Alice");
    return 0;
}
```
The output from it is:
```none
fmt_print(): fmt1 = [[Key1:%s
Key2:%d
Key3:%s]]
fmt_print(): buf1 = [[Key1:Bob
Key2:4
Key3:Alice]]
fmt_print(): fmt2 = [[Name:%s
ID:%d
]]
fmt_print(): buf2 = [[Name:TestName
ID:42
]]
fmt_print(): Format strings:
[[Key1:%s
Key2:%d
Key3:%s]]
[[Name:%s
ID:%d
]]
fmt_print(): Message strings:
[[Key1:Bob
Key2:4
Key3:Alice]]
[[Name:TestName
ID:42
]]
[END]
Full buffer: [[Name:TestName
ID:42
Key1:Bob
Key2:4
Key3:Alice

]]
```
Note that this code frees the memory allocated by `vasprintf()`.

Since you try to compile with `-Wmissing-format-attribute`, you will
still get errors from a verbatim copy of this code.  It will compile
cleanly with your options if you add:
```
#if !defined(PRINTFLIKE)
#if defined(__GNUC__)
#define PRINTFLIKE(n, m) __attribute__((format(printf, n, m)))
#else
#define PRINTFLIKE(n, m) /* If only */
#endif /* __GNUC__ */
#endif /* PRINTFLIKE */
```
and change the function definition lines to:
```
static int PRINTFLIKE(3, 4) fmt_print(const char *fmt1, va_list ap1, const char *fmt2, ...)
```
and
```
static void PRINTFLIKE(2, 3) do_print(const char *name, const char *fmt, ...)
```
and in `do_print()`, modify the call to `fmt_print()` to take a literal
format (eliminating the variable `buf`):
```
    fmt_print(fmt, ap, "Name:%s\r\nID:%d\r\n", name, 42);
```
A lot of the time, the 'non-literal format' check is helpful and
sensible, but there are times when it is counter-productive.
