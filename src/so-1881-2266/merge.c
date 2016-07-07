/* http://stackoverflow.com/q/18812266 Merging multiple sorted files */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct File
{
    const char *file;
    FILE       *fp;
    char       *line;
    size_t      reserve;    /* Space allocated for line */
    size_t      length;     /* Space used by current line */
} File;

extern void err_exit(const char *fmt, ...);
extern void read_line(File *current);
extern void write_line(File *current);
extern void heapify(size_t *heap, size_t heap_size, File *inputs);
extern void siftup(size_t *heap, size_t lo, size_t hi, File *inputs);
extern void siftdown(size_t *heap, size_t lo, size_t hi, File *inputs);
extern int  compare(File *inputs, size_t i1, size_t i2);

const char *arg0;

int main(int argc, char **argv)
{
    File inputs[argc];
    arg0 = argv[0];

    /* Open files for reading - load first lines */
    for (int i = 1; i < argc; i++)
    {
        File *current = &inputs[i];
        current->file = argv[i];
        if ((current->fp = fopen(current->file, "r")) == 0)
            err_exit("failed to open file %s for reading", current->file);
        current->reserve = 128;
        if ((current->line = malloc(current->reserve)) == 0)
            err_exit("failed to allocate %zu bytes memory", current->reserve);
        current->length = 0;
        read_line(current);
    }

#if defined(CHECK_FUNDAMENTALS)
    for (int i = 1; i < argc; i++)
        printf("%d: %zu - %s\n", i, inputs[i].length, inputs[i].file);
#endif

    size_t heap_size = argc - 1;
    size_t heap[argc];     // heap[0] unused

    for (int i = 1; i < argc; i++)
        heap[i] = i;

#if defined(CHECK_FUNDAMENTALS)
    printf("Heap before:\n");
    for (int i = 1; i < argc; i++)
        printf("%d: %zu - %s", i, heap[i], inputs[heap[i]].line);
#endif

    heapify(heap, heap_size, inputs);

#if defined(CHECK_FUNDAMENTALS)
    printf("Heap after:\n");
    for (int i = 1; i < argc; i++)
        printf("%d: %zu - %s", i, heap[i], inputs[heap[i]].line);
#endif

#if defined(CHECK_FUNDAMENTALS)
    printf("Compare two lines:\n");
    printf("1: %s\n", inputs[1].line);
    printf("2: %s\n", inputs[2].line);
    int r12 = compare(inputs, 1, 2);
    int r21 = compare(inputs, 2, 1);
    int r11 = compare(inputs, 1, 1);
    printf("1 vs 2: %d\n", r12);
    printf("2 vs 1: %d\n", r21);
    printf("1 vs 1: %d\n", r11);
#endif

    while (heap_size > 0)
    {
        File *current = &inputs[heap[1]];
        write_line(current);
        read_line(current);
        if (current->line == 0)
            heap[1] = heap[heap_size--];
        if (heap_size > 0)
        {
            siftdown(heap, 1, heap_size, inputs);
#if defined(CHECK_FUNDAMENTALS)
            printf("Heap check:\n");
            for (int i = 1; i < argc; i++)
                printf("%d: %zu - %s", i, heap[i], inputs[heap[i]].line);
#endif
        }
    }

    return 0;
}

int compare(File *inputs, size_t i1, size_t i2)
{
    return strcmp(inputs[i1].line, inputs[i2].line);
}

void heapify(size_t *heap, size_t heap_size, File *inputs)
{
    for (size_t i = 1; i <= heap_size; i++)
        siftup(heap, 1, i, inputs);
}

/* J Bentley: More Programming Pearls
**
** Heap in array x, indexed from 1, not 0 as is normal in C.
** Implementation will allocate but not use array[0].
**
**  function siftup(l, u,    i, p) {
**          # pre  maxheap(l, u-1)
**          # post maxheap(l, u)
**          i = u
**          while (1) {
**                  # maxheap(l, u) except between i and its parent
**                  if (i <= l) break
**                  p = int(i/2)
**                  if (x[p] >= x[i]) break
**                  swap(p, i)
**                  i = p
**          }
**  }
**
**  function siftdown(l, u,  i, c) {
**          # pre  maxheap(l+1, u)
**          # post maxheap(l,u)
**          i = l
**          while (1) {
**                  # maxheap(l, u) except between i and its children
**                  c = 2*i
**                  if (c > u) break
**                  if (c + 1 <= u && x[c+1] > x[c]) c++
**                  if (x[i] >= x[c]) break
**                  swap(c, i)
**                  i = c
**          }
**  }
*/

void siftup(size_t *heap, size_t lo, size_t hi, File *inputs)
{
    size_t i = hi;
    while (1)
    {
        if (i <= lo)
            break;
        size_t p = i / 2;
        if (compare(inputs, heap[p], heap[i]) <= 0)
            break;
        size_t t = heap[p];
        heap[p] = heap[i];
        heap[i] = t;
        i = p;
    }
}

void siftdown(size_t *heap, size_t lo, size_t hi, File *inputs)
{
    size_t i = lo;
    while (1)
    {
        size_t c = 2 * i;
        if (c > hi)
            break;
        if (c + 1 <= hi && compare(inputs, heap[c+1], heap[c]) < 0)
            c++;
        if (compare(inputs, heap[i], heap[c]) <= 0)
            break;
        size_t t = heap[c];
        heap[c] = heap[i];
        heap[i] = t;
        i = c;
    }
}

void read_line(File *current)
{
    char buffer[4096];
    if (fgets(buffer, sizeof(buffer), current->fp) != 0)
    {
        size_t length = strlen(buffer) + 1;
        if (length > current->reserve)
        {
            void *space = realloc(current->line, length);
            if (space == 0)
                err_exit("failed to reallocate %zu bytes memory", length);
            current->line = space;
            current->reserve = length;
        }
        strcpy(current->line, buffer);
        current->length = length - 1;
    }
    else
    {
        fclose(current->fp);
        current->fp = 0;
        free(current->line);
        current->line = 0;
        current->length = 0;
        current->reserve = 0;
    }
}

void write_line(File *current)
{
    if (fwrite(current->line, sizeof(char), current->length, stdout) != current->length)
        err_exit("short write of line from %s of length %zu", current->file, current->length);
}

void err_exit(const char *fmt, ...)
{
    int errnum = errno;
    va_list args;
    fprintf(stderr, "%s: ", arg0);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    if (errnum != 0)
        fprintf(stderr, " (%d: %s)", errnum, strerror(errnum));
    putc('\n', stderr);
    exit(EXIT_FAILURE);
}
