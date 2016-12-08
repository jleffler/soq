#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>

enum { DISPLAY_ROWS = 24, DISPLAY_COLS = 50 };
//enum { DISPLAY_ROWS = 24, DISPLAY_COLS = 24 };

typedef struct screen_graph
{
    char field[DISPLAY_ROWS][DISPLAY_COLS];
    bool expired;
} screen_graph_t;

static bool screen_graph_interator(screen_graph_t *local, char **buffer,
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

    assert(*buffer >= &local->field[0][0] &&
           *buffer <= &local->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);

    (*iteration)++;

    return true;
}

static bool screen_graph_changes(screen_graph_t *old_graph, screen_graph_t *new_graph)
{
    char *old_char = NULL;
    char *new_char = NULL;
    uint32_t iteration = 0;

    //while (screen_graph_interator(old_graph, &old_char, &iteration, 0, 0, DISPLAY_COLS, DISPLAY_ROWS))
    while (screen_graph_interator(old_graph, &old_char, &iteration, 0, 0, DISPLAY_ROWS, DISPLAY_COLS))
    {
        iteration--;
        //screen_graph_interator(new_graph, &new_char, &iteration, 0, 0, DISPLAY_COLS, DISPLAY_ROWS);
        screen_graph_interator(new_graph, &new_char, &iteration, 0, 0, DISPLAY_ROWS, DISPLAY_COLS);
        assert(old_char >= &old_graph->field[0][0] &&
               old_char <= &old_graph->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);
        assert(new_char >= &new_graph->field[0][0] &&
               new_char <= &new_graph->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);

        if (*old_char != *new_char && *new_char != '\0')
        {
            printf("Different: %" PRIu32 "\n", iteration);
            return true;
        }
    }
    return false;
}

int main(void)
{
    screen_graph_t old_graph = { 0 };
    screen_graph_t new_graph = { 0 };
    old_graph.field[DISPLAY_ROWS-1][DISPLAY_COLS-1] = 'O';
    new_graph.field[DISPLAY_ROWS-1][DISPLAY_COLS-1] = 'N';
    screen_graph_changes(&old_graph, &new_graph);
    return 0;
}
