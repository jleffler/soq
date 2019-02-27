int deck[] = {1,1,1,1,1,1,1,1,1,1};
This should represent 10 different "cards" (identified by their index in the array), each available one time. Now, just write code that "draws" cards:

int i = 0;  // starting point for searching for the next card to draw
for (int n = 10; n > 0; --n)  // how many cards are left
{
    int skip = rand() % n;  // randomly skip 0 .. n cards
    while (1)
    {
        if (deck[i])             // card still available?
        {
            if (!skip) break;    // none more to skip -> done
            --skip;              // else one less to skip
        }

        if (++i > 9) i = 0;      // advance index, wrapping around to 0
    }
    deck[i] = 0;              // draw the card
    printf("%d\n", i+1);      // and print it out
}
