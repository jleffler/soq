/* SO 5468-0129 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { SB_SIZE = 15 };

typedef int Data;
#define DATA_PRI_FMT "d"

struct ShuffleBuffer
{
   size_t sb_last;
   Data   sb_data[SB_SIZE];
};
typedef struct ShuffleBuffer ShuffleBuffer;

static inline void sb_shuffle(ShuffleBuffer *sbp)
{
    if (sbp->sb_last > 0)
    {
        memmove(sbp->sb_data, sbp->sb_data + 1, (SB_SIZE - 1) * sizeof(sbp->sb_data[0]));
        sbp->sb_last--;
    }
}

static void sb_insert(ShuffleBuffer *sbp, Data value)
{
    if (sbp->sb_last == SB_SIZE)
        sb_shuffle(sbp);
    sbp->sb_data[sbp->sb_last++] = value;
}

static bool sb_remove(ShuffleBuffer *sbp, Data *valuep)
{
    if (sbp->sb_last == 0)
        return false;
    *valuep = sbp->sb_data[0];
    sb_shuffle(sbp);
    return true;
}

static void sb_print(const char *tag, const ShuffleBuffer *sbp)
{
    printf("%s: (last = %zu)\n", tag, sbp->sb_last);
    int nbytes = 0;
    const char *pad = "";
    for (size_t i = 0; i < sbp->sb_last; i++)
    {
        nbytes += printf("%s(%2zu: %3" DATA_PRI_FMT ")", pad, i, sbp->sb_data[i]);
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
    ShuffleBuffer rb = { 0, { 0 } };

    for (Data i = 0; i < 1000000; i++)
    {
        sb_insert(&rb, i * 7 + 23);
        if (1)
            sb_print("Post insert", &rb);
        if ((i & 1) == 1)
        {
            Data value;
            if (sb_remove(&rb, &value))
            {
                if (1)
                    printf("Value %" DATA_PRI_FMT " removed\n", value);
            }
            else
            {
                if (1)
                    sb_print("Ring Buffer Empty", &rb);
            }
        if (1)
            sb_print("Post remove", &rb);
        }
    }

    if (1)
        printf("Insert/remove loop over\n");

    Data value;
    while (sb_remove(&rb, &value))
    {
        if (1)
            printf("Value %" DATA_PRI_FMT " removed\n", value);
    }

    return 0;
}
