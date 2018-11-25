#include <stdio.h>
#include <string.h>

extern void other_function(void *p);

struct simulated
{
    int     number;
    double  value;
    char    string[32];
};

void other_function(void *p)
{
    struct simulated *s = (struct simulated *)p;

    printf("Other function:\n");
    printf("Integer: %d\n", s->number);
    printf("Double:  %f\n", s->value);
    printf("String:  %s\n", s->string);

    s->number *= 2;
    s->value  /= 2;
    strcpy(s->string, "Codswallop");
}
