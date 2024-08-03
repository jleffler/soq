#include <string.h>

#if defined(USE_EXTERN)

/*
** This declaration belongs in a header if there is more than one
** source file that uses it.  If there is only one file, then it
** should be declared and defined as a static function.  If the
** header doesn't include any other headers that define size_t,
** it should #include <stddef.h> as that's the smallest header
** that does defined size_t.  You could make the function static
** inline instead of extern, even if it is in a header.
*/
extern void generic_swap(void *v1, void *v2, size_t size);

#define STATIC_INLINE /* as nothing */

#else

#define STATIC_INLINE static inline

#endif

#if defined(USE_IMPLEMENTATION_1)

/* Implementation 1: Using VLA */
STATIC_INLINE
void generic_swap(void *v1, void *v2, size_t size)
{
    char sp[size];
    memmove(sp, v1, size);
    memmove(v1, v2, size);
    memmove(v2, sp, size);
}

#elif defined(USE_IMPLEMENTATION_3)

#include <stdlib.h>

/* Implentation 3: Using dynamic memory allocation */
STATIC_INLINE
void generic_swap(void *v1, void *v2, size_t size)
{
    char *sp = malloc(size);
    if (sp != 0)
    {
        memmove(sp, v1, size);
        memmove(v1, v2, size);
        memmove(v2, sp, size);
        free(sp);
    }
}

#else

#ifndef TEST_CHUNK_SIZE
#define TEST_CHUNK_SIZE 64
#endif

enum { CHUNK_SIZE = TEST_CHUNK_SIZE };

static inline size_t min_size(size_t x, size_t y) { return (x < y) ? x : y; }

/* Implementation 2: Using a fixed size buffer */
STATIC_INLINE
void generic_swap(void *v1, void *v2, size_t size)
{
    unsigned char sp[CHUNK_SIZE];
    unsigned char *p1 = v1;
    unsigned char *p2 = v2;
    size_t chunk;
    while ((chunk = min_size(size, CHUNK_SIZE)) != 0)
    {
        memmove(sp, p1, chunk);
        memmove(p1, p2, chunk);
        memmove(p2, sp, chunk);
        p1 += chunk;
        p2 += chunk;
        size -= chunk;
    }
}

#endif 

#include <stdio.h>

int main(void)
{
    double a = 1.0;
    double b = 2.0;

    printf("linea: %d - antes   a(%f) b(%f)\n", __LINE__, a, b);
    generic_swap(&a, &b, sizeof(double));
    printf("linea: %d - despues a(%f) b(%f)\n", __LINE__, a, b);
    return 0;
}
