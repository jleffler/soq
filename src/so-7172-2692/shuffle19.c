/* SO 7172-2692 - 2022-04-02 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char * const suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
static const char * const face[13] =
{
    "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
    "Ten", "Jack", "Queen", "King"
};

static int deck[52];

static void displayDeck(const char *tag)
{
    printf("%s:\n", tag);
    for (int i = 0; i < 52; i++)
        printf("%2d [%2d] %s of %s\n", i, deck[i], face[deck[i] % 13], suit[deck[i] / 13]);
}

static int random_int(int range)
{
    int max = RAND_MAX - (RAND_MAX % range);
    int value;
    while ((value = rand()) > max)
        ;
    return value % range;
}

static void shuffleDeck(void)
{
    for (int i = 0; i < 52; ++i)
    {
        int ind = i + random_int(52 - i);
        int temp = deck[i];
        deck[i] = deck[ind];
        deck[ind] = temp;
    }
}

static void initDeck(void)
{
    for (int i = 0; i < 52; i++)
        deck[i] = i;
}

int main(void)
{
    srand(time(NULL));
    initDeck();
    displayDeck("Before shuffle");
    shuffleDeck();
    displayDeck("After shuffle");
}
