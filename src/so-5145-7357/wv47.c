#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRLEN 10
#define PICKED 10

int main(void) { 
    int array[ARRLEN];

    srand((unsigned)time(NULL));        // seed the PRNG

    for(int i = 0; i < ARRLEN; i++) {       // generate the numbers
        array[i] = i + 1;
    }

    for(int i = 0; i < ARRLEN; i++) {       // shuffle the array
        int index = rand() % ARRLEN;
        int temp = array[i];
        array[i] = array[index];        // by randomly swapping
        array[index] = temp;
    }

    for(int i = 0; i < PICKED; i++) {       // output the numbers
        printf("%d ",  array[i]);
    }
    printf("\n");
}

/* Weather Vane: https://stackoverflow.com/users/4142924/weather-vane */
/* SO Answer: https://stackoverflow.com/a/51458654 */
/* SO Question: https://stackoverflow.com/questions/51457357/ */
/* How can I use rand() to generate a different number that hasn't been generated before */

