/* SO 7181-1136 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char * const card_names[] =
{
    "Ace", "2", "3", "4", "5", "6", "7",
    "8", "9", "10", "Jack", "Queen", "King"
};
enum { NUM_CARD_NAMES = sizeof(card_names) / sizeof(card_names[0]) };
static const char * const suit_names[] =
{
    "Hearts", "Diamonds", "Clubs", "Spades"
};
enum { NUM_SUIT_NAMES = sizeof(suit_names) / sizeof(suit_names[0]) };

/* OP's function - but the ' of ' was added by JL */
static void names(int card, int suit, char *answer)
{
    int i;
    int index = 0;
    answer[index] = '\0';

    for (i = 0; i < NUM_CARD_NAMES; i++)
    {
        if (i == card)
        {
            int len = strlen(card_names[i]);
            for (int j = 0; j < len; j++)
            {
                answer[index] = card_names[i][j];
                index++; // keeps track of how big our current string is
            }
        }
    }

    answer[index++] = ' ';
    answer[index++] = 'o';
    answer[index++] = 'f';
    answer[index++] = ' ';

    for (i = 0; i < NUM_SUIT_NAMES; i++)
    {
        if (i == suit)
        {
            int len = strlen(suit_names[i]);
            for (int j = 0; j < len; j++)
            {
                answer[index] = suit_names[i][j];
                index++;
            }
        }
    }

    answer[index] = '\0';
}

static void alt_names_1(int card, int suit, size_t ans_len, char *answer)
{
    assert(card >= 0 && card < NUM_CARD_NAMES);
    assert(suit >= 0 && suit < NUM_SUIT_NAMES);
    snprintf(answer, ans_len, "%s of %s", card_names[card], suit_names[suit]);
}

static void alt_names_2(int card, int suit, char *answer)
{
    assert(card >= 0 && card < NUM_CARD_NAMES);
    assert(suit >= 0 && suit < NUM_SUIT_NAMES);
    strcpy(answer, card_names[card]);
    strcat(answer, " of ");
    strcat(answer, suit_names[suit]);
}

static void print_card(int card, int suit, const char *n1, const char *n2, const char *n3)
{
    printf("Card %2d, Suit %d:", card + 1, suit + 1);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "[%s]", n1);
    printf(" %-20s", buffer);
    snprintf(buffer, sizeof(buffer), "[%s]", n2);
    printf(" %-20s", buffer);
    snprintf(buffer, sizeof(buffer), "[%s]", n3);
    printf(" %-20s", buffer);
    putchar('\n');
}

int main(void)
{
    for (int card = 0; card < NUM_CARD_NAMES; card++)
    {
        for (int suit = 0; suit < NUM_SUIT_NAMES; suit++)
        {
            char answer1[sizeof("Queen of Diamonds")] = "";
            char answer2[sizeof("Queen of Diamonds")] = "";
            char answer3[sizeof("Queen of Diamonds")] = "";
            names(card, suit, answer1);
            alt_names_1(card, suit, sizeof(answer2), answer2);
            alt_names_2(card, suit, answer3);
            print_card(card, suit, answer1, answer2, answer3);
            //printf("Card %2d, Suit %d: [%s] [%s] [%s]\n",
            //       card + 1, suit + 1, answer1, answer2, answer3);
        }
    }
    return 0;
}
