#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

enum { DISPLAY_ROWS = 24, DISPLAY_COLS = 50 };

typedef struct screen_graph
{
    char field[DISPLAY_ROWS][DISPLAY_COLS];
    bool expired;
} screen_graph_t;

static bool ascii_graphics_erase(screen_graph_t *local);
static bool __screen_graph_interator(screen_graph_t *local, char **buffer,
                                     uint32_t *iteration, uint32_t start_x, uint32_t start_y,
                                     uint32_t width, uint32_t height);

static void execute_ascii_test(void)
{
    screen_graph_t changes;

    ascii_graphics_erase(&changes);

    printf("Won't get here\n");
}

static bool ascii_graphics_erase(screen_graph_t *local)
{
    char *local_char = NULL;
    uint32_t interation = 0;

    while (__screen_graph_interator(local, &local_char, &interation, 0, 0, DISPLAY_COLS, DISPLAY_ROWS))
    {
        assert(local_char >= &local->field[0][0] &&
               local_char <= &local->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);
        *local_char = '\0';
    }

    return true;
}

static bool __screen_graph_interator(screen_graph_t *local, char **buffer,
                                     uint32_t *iteration, uint32_t start_x, uint32_t start_y,
                                     uint32_t width, uint32_t height)
{
    int x = start_x + *iteration % width;
    int y = start_y + *iteration / width;

    if (*iteration > (width * height) - 1)
    {
        *buffer = NULL;
        return false;
    }

    *buffer = &(local->field[x][y]);

    (*iteration)++;
    assert(*buffer >= &local->field[0][0] &&
           *buffer <= &local->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);

    return true;
}

int main(void)
{
    execute_ascii_test();
    return 0;
}
