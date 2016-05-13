#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_WORDS = 64 };

static int split_words(char *buffer, char **words, int max_words)
{
    char *token;
    char *next = buffer;
    int num_words = 0;
    while ((token = strtok(next, " \n")) != 0 && num_words < max_words)
    {
        words[num_words++] = token;
        next = NULL;
    }
    return num_words;
}

static int word_in_list(char *word, char **list, int list_size)
{
    for (int i = 0; i < list_size; i++)
    {
        if (strcmp(word, list[i]) == 0)
            return 1;
    }
    return 0;
}

/* Print words in list w1 that do not appear in list w2 */
static void print_unique(char **w1, int n1, char **w2, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        if (!word_in_list(w1[i], w2, n2))
            printf("[%s]\n", w1[i]);
    }
}

int main(void)
{
    char  *line1 = NULL;
    char  *line2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;

    if (getline(&line1, &size1, stdin) > 0 &&
        getline(&line2, &size2, stdin) > 0)
    {
        char *w1[MAX_WORDS];
        char *w2[MAX_WORDS];
        int   n1 = split_words(line1, w1, MAX_WORDS);
        int   n2 = split_words(line2, w2, MAX_WORDS);

        print_unique(w1, n1, w2, n2);
        print_unique(w2, n2, w1, n1);
    }
    free(line1);
    free(line2);
    return 0;
}

/*
   Initialize size1 and size2 to zero too for safety.  You'll need two
   arrays of char pointers, one for each line of input.  You'll split the
   first line into the first array, and the second line into the second
   array.  Then you'll go through the two arrays of pointers, comparing
   strings and counting only those that do not match any of the entries in
   the other array.  (What do you do if one input line itself contains
   repeats — The Lion, the Witch, and the Wardrobe for example?  Also, do
   you need to treat The as the same as the in that example?)

   You can use strtok_r() or strtok_s() if you have them available; at a
   pinch, you could use strtok(), but it is dangerous to use that in
   library code.  And you'll need to use strcmp() to compare the strings
   — plus macros/functions from <ctype.h> to handle case-conversion if
   that's appropriate.

   Also note that strtok() is destructive.  If you've split string 1 with
   it, you can't then search in string 1 when you split string 2.  Also
   note that strstr("then came a deluge", "the") matches, even though most
   people would not regard the haystack string as containing the needle
   word the.
 */
