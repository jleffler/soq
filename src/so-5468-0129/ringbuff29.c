/* SO 5468-0129 */
#include <stdbool.h>
#include <stdio.h>

enum { RB_SIZE = 16 };

typedef int Data;
#define DATA_PRI_FMT "d"

struct RingBuffer
{
   size_t rb_head;
   size_t rb_tail;
   Data   rb_data[RB_SIZE];
};
typedef struct RingBuffer RingBuffer;

static inline size_t rb_nextpos(size_t pos)
{
    return (pos + 1) % RB_SIZE;
}

static void rb_insert(RingBuffer *rbp, Data value)
{
    rbp->rb_data[rbp->rb_head] = value;
    rbp->rb_head = rb_nextpos(rbp->rb_head);
    if (rbp->rb_tail == rbp->rb_head)
        rbp->rb_tail = rb_nextpos(rbp->rb_tail);
}

static bool rb_remove(RingBuffer *rbp, Data *valuep)
{
    if (rbp->rb_head == rbp->rb_tail)
        return false;
    *valuep = rbp->rb_data[rbp->rb_tail];
    rbp->rb_tail = rb_nextpos(rbp->rb_tail);
    return true;
}

static void rb_print(const char *tag, const RingBuffer *rbp)
{
    printf("%s: (head = %zu, tail = %zu)\n", tag, rbp->rb_head, rbp->rb_tail);
    int nbytes = 0;
    const char *pad = "";
    for (size_t i = rbp->rb_tail; i != rbp->rb_head; i = rb_nextpos(i))
    {
        nbytes += printf("%s(%2zu: %3" DATA_PRI_FMT ")", pad, i, rbp->rb_data[i]);
        if (nbytes > 40)
        {
            putchar('\n');
            nbytes = 0;
            pad = "";
        }
        else
            pad = " ";
    }
    if (nbytes != 0)
        putchar('\n');
}

int main(void)
{
    RingBuffer rb = { 0, 0, { 0 } };

    for (Data i = 0; i < 1000000; i++)
    {
        rb_insert(&rb, i * 7 + 23);
        if (1)
            rb_print("Post insert", &rb);
        if ((i & 1) == 1)
        {
            Data value;
            if (rb_remove(&rb, &value))
            {
                if (1)
                    printf("Value %" DATA_PRI_FMT " removed\n", value);
            }
            else
            {
                if (1)
                    rb_print("Ring Buffer Empty", &rb);
            }
        if (1)
            rb_print("Post remove", &rb);
        }
    }

    if (1)
        printf("Insert/remove loop over\n");

    Data value;
    while (rb_remove(&rb, &value))
    {
        if (1)
            printf("Value %" DATA_PRI_FMT " removed\n", value);
    }

    return 0;
}
