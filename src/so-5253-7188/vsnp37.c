/* SO 5253-7188 */
/* Format strings safely when vsnprintf is not available */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern char *formatString(const char *format, ...);

char *formatString(const char *format, ...)
{
    static FILE *fp_null = NULL;

    if (fp_null == NULL)
    {
        fp_null = fopen("/dev/null", "w");
        if (fp_null == NULL)
            return NULL;
    }

    va_list ap;

    va_start(ap, format);
    int size = vfprintf(fp_null, format, ap);
    va_end(ap);

    if (size < 0)
        return NULL;

    char *result = (char *) malloc(size + 1);
    if (result == NULL)
        return NULL;

    va_start(ap, format);
    int check = vsprintf(result, format, ap);
    va_end(ap);

    assert(check == size);

    return result;
}

int main(void)
{
    char *r1 = formatString("%d Dancing Pigs = %4.2f%% of annual GDP (grandiose dancing pigs!)\n",
                            34241562, 21.2963);
    char *r2 = formatString("%s [%-13.10s] %s is %d%% %s\n", "Peripheral",
                            "sub-atomic hyperdrive", "status", 99, "of normality");

    if (r1 != NULL)
        printf("r1 = %s", r1);

    if (r2 != NULL)
        printf("r2 = %s", r2);

    free(r1);
    free(r2);
    return 0;
}
