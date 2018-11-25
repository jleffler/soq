#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is the type that will be simulated dynamically */
/*
struct simulated
{
    int     number;
    double  value;
    char    string[32];
};
*/

/* SOF structure.h */
typedef enum Type { INT, DOUBLE, STRING } Type;

typedef struct Descriptor
{
    size_t  offset;
    Type    type;
    size_t  type_size;
    size_t  array_dim;
    char    name[32];
} Descriptor;

typedef struct Structure
{
    size_t      size;
    char        name[32];
    Descriptor *details;
} Structure;

extern void   *allocate_structure(const Structure *structure);
extern void    deallocate_structure(void *structure);
extern void   *pointer_to_element(void *p, const Descriptor *d);
extern int     get_int_element(void *p, const Descriptor *d);
extern void    set_int_element(void *p, const Descriptor *d, int newval);
extern double  get_double_element(void *p, const Descriptor *d);
extern void    set_double_element(void *p, const Descriptor *d, double newval);
extern char   *get_string_element(void *p, const Descriptor *d);
extern void    set_string_element(void *p, const Descriptor *d, char *newval);
/* EOF structure.h */

static Descriptor details[] =
{
    {   0,  INT,    sizeof(int),     1, "number"    },
    {   8,  DOUBLE, sizeof(double),  1, "value"     },
    {  16,  STRING, sizeof(char),   32, "string"    },
};

static Structure simulated = { 48, "simulated", details };

void *allocate_structure(const Structure *structure)
{
    void *p = calloc(1, structure->size);
    return p;
}

void deallocate_structure(void *structure)
{
    free(structure);
}

void *pointer_to_element(void *p, const Descriptor *d)
{
    void *data = (char *)p + d->offset;
    return data;
}

int get_int_element(void *p, const Descriptor *d)
{
    assert(d->type == INT);
    int *v = pointer_to_element(p, d);
    return *v;
}

void set_int_element(void *p, const Descriptor *d, int newval)
{
    assert(d->type == INT);
    int *v = pointer_to_element(p, d);
    *v = newval;
}

double get_double_element(void *p, const Descriptor *d)
{
    assert(d->type == DOUBLE);
    double *v = pointer_to_element(p, d);
    return *v;
}

void set_double_element(void *p, const Descriptor *d, double newval)
{
    assert(d->type == DOUBLE);
    double *v = pointer_to_element(p, d);
    *v = newval;
}

char *get_string_element(void *p, const Descriptor *d)
{
    assert(d->type == STRING);
    char *v = pointer_to_element(p, d);
    return v;
}

void set_string_element(void *p, const Descriptor *d, char *newval)
{
    assert(d->type == STRING);
    assert(d->array_dim > 1);
    size_t len = strlen(newval);
    if (len > d->array_dim)
        len = d->array_dim - 1;
    char *v = pointer_to_element(p, d);
    memmove(v, newval, len);
    v[len] = '\0';
}

extern void other_function(void *p);

int main(void)
{
    void *sp = allocate_structure(&simulated);

    if (sp != 0)
    {
        set_int_element(sp, &simulated.details[0], 37);
        set_double_element(sp, &simulated.details[1], 3.14159);
        set_string_element(sp, &simulated.details[2], "Absolute nonsense");
        printf("Main (before):\n");
        printf("Integer: %d\n", get_int_element(sp, &simulated.details[0]));
        printf("Double:  %f\n", get_double_element(sp, &simulated.details[1]));
        printf("String:  %s\n", get_string_element(sp, &simulated.details[2]));
        other_function(sp);
        printf("Main (after):\n");
        printf("Integer: %d\n", get_int_element(sp, &simulated.details[0]));
        printf("Double:  %f\n", get_double_element(sp, &simulated.details[1]));
        printf("String:  %s\n", get_string_element(sp, &simulated.details[2]));

        deallocate_structure(sp);
    }
    return 0;
}
