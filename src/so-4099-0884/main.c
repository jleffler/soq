/* SO 4098-8815 */
/*
** Code by [NanonA](http://stackoverflow.com/users/2390668/nanona).
** This is code modified by NanonA based on SO 4098-8815 (which morphed
** into SO 4099-0884).
**
** This works compared with the question - because the arguments height
** and width here are in the reverse order compared to the code in the
** question.  The fix is equivalent to reversing the arguments to the
** call.
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define DISPLAY_ROWS 10
#define DISPLAY_COLS 5

typedef struct screen_graph {
    char field[DISPLAY_ROWS][DISPLAY_COLS];
    bool expired;
} screen_graph_t;

static bool screen_graph_interator(screen_graph_t* local, char** buffer, uint32_t* iteration, uint32_t start_x, uint32_t start_y, uint32_t height, uint32_t width) {

    int x, y;

    x = start_x + *iteration % width;
    y = start_y + *iteration / width;

    if(*iteration > (width * height)-1) {

        *buffer = NULL;

        return false;
    }

    *buffer = &(local->field[x][y]);

    assert(*buffer >= &local->field[0][0] &&
           *buffer <= &local->field[DISPLAY_ROWS-1][DISPLAY_COLS-1]);

    printf("x: %d\n", x);
    printf("y: %d\n\n", y);

    (*iteration)++;

    return true;
}

static bool ascii_graphics_erase(screen_graph_t* local) {
    char* local_char = NULL;

    uint32_t interation = 0;

    while(screen_graph_interator(local, &local_char, &interation, 0, 0, DISPLAY_COLS, DISPLAY_ROWS)) {
        *local_char = 'a';
    }

    return true;
}

static void execute_ascii_test(void) {
   screen_graph_t changes;
   size_t index;

   ascii_graphics_erase(&changes);

   for(index = 0; index < DISPLAY_ROWS; index++)
   {
       printf("%s\n", changes.field[index]);
   }

   printf("Won't get here");
}

int main(void)
{
    execute_ascii_test();
    return 0;
}
