/*
** Unicode cards.
** U+1F0A0 .. U+1F0EF
** 
** U+1F0A0 - back of card
** U+1F0A1 - Ace of spades
**   ...   - ...
** U+1F0AA - Ten of spades
** U+1F0AB - Jack of spades
** U+1F0AC - Knight of spades (chevalier in French)
** U+1F0AD - Queen of spades
** U+1F0AE - King of spades
**
** Additive constants for suits:
** 0x00 = Spades
** 0x10 = Hearts
** 0x20 = Diamonds
** 0x30 = Clubs
**
** U+1FxF = various forms of joker
**
** Plain suit symbols are from a different section of Unicode:
** U+2660 = black spade
** U+2661 = black heart
** U+2662 = black diamond
** U+2663 = black club
** U+2664 = white spade
** U+2665 = white heart
** U+2666 = white diamond
** U+2667 = white club
*/

#include <ctype.h>

/* Given inputs such as 3S or KH, show the correct Unicode output */
struct card_map
{
    unsigned char letter;
    unsigned char offset;
};

static struct card_map ranks[] =
{
    { 'A',  1 },
    { '2',  2 },
    { '3',  3 },
    { '4',  4 },
    { '5',  5 },
    { '6',  6 },
    { '7',  7 },
    { '8',  8 },
    { '9',  9 },
    { 'T', 10 },
    { 'J', 11 },
    { 'Q', 13 },
    { 'K', 14 },
};
enum { NUM_RANKS = sizeof(ranks) / sizeof(ranks[0]) };

static struct card_map suits[] = 
{
    { 'S', 0x00 },
    { 'H', 0x10 },
    { 'D', 0x20 },
    { 'C', 0x30 },
};
enum { NUM_SUITS = sizeof(suits) / sizeof(suits[0]) };

enum { BOGUS_MAP  = 0xFF };
enum { BOGUS_CARD = 0x0000 };
enum { BASE_CARD  = 0x01F0A0 };

static int map_search(int size, const struct card_map *map, unsigned char code)
{
    for (int i = 0; i < size; i++)
    {
        if (map[i].letter == code)
            return map[i].offset;
    }
    return BOGUS_MAP;
}

static unsigned unicode_card(const char *card)
{
    unsigned unicode = BASE_CARD;
    unsigned char s = toupper(card[1]);
    unsigned char r = toupper(card[0]);
    int s_off = map_search(NUM_SUITS, suits, s);
    int r_off = map_search(NUM_RANKS, ranks, r);
    if (r_off == BOGUS_MAP || s_off == BOGUS_MAP)
        return BOGUS_CARD;
    return unicode + s_off + r_off;
}

/* This has got a bad case of the magic numbers! */
static const char *unicode_utf8(unsigned unicode)
{
    static char utf8[5];
    if (unicode < 0x80)
    {
        utf8[0] = unicode;
        utf8[1] = '\0';
    }
    else if (unicode < 0x800)
    {
        utf8[0] = 0xC0 |  (unicode >> 6);
        utf8[1] = 0x80 | ((unicode >> 0) & 0x3F);
        utf8[2] = '\0';
    }
    else if (unicode < 0x10000)
    {
        utf8[0] = 0xE0 |  (unicode >> 12);
        utf8[1] = 0x80 | ((unicode >>  6) & 0x3F);
        utf8[2] = 0x80 | ((unicode >>  0) & 0x3F);
        utf8[4] = '\0';
    }
    else
    {
        utf8[0] = 0xF0 |  (unicode >> 18);
        utf8[1] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[2] = 0x80 | ((unicode >>  6) & 0x3F);
        utf8[3] = 0x80 | ((unicode >>  0) & 0x3F);
        utf8[4] = '\0';
    }
    return utf8;
}

#include <stdio.h>

int main(void)
{
    char card[2];
    puts("<html>");
    puts("<head>");
    puts("<title> Cards </title>");
    puts("</head>");
    puts("<body>");
    puts("<h1> Cards </h1>");
    puts("<table>");
    for (int i = 0; i < NUM_SUITS; i++)
    {
        card[1] = suits[i].letter;
        for (int j = 0; j < NUM_RANKS; j++)
        {
            card[0] = ranks[j].letter;
            int unicode = unicode_card(card);
            if (unicode == BOGUS_CARD)
                printf("<tr><td> %.2s = bogus card </tr></td>\n", card);
            else
                printf("<tr><td> %.2s = U+%.6X = %s </tr></td>\n",
                       card, unicode, unicode_utf8(unicode));
        }
    }
    puts("</table>");
    puts("</body>");
    puts("</html>");
    return 0;
}
