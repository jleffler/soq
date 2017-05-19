#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum {
    MAX_NUMBER_OF_NODES = 1500000, NUM_OF_ALPHA = 26, MAX_LENGTH_OF_WORD = 100,
    MAX_OCCURENCE_OF_SAME_WRONG_WORD = 10000, MAX_NUMBER_OF_WRONG_WORDS = 600000,
};
int trie[MAX_NUMBER_OF_NODES][NUM_OF_ALPHA + 1], next = 0;
typedef long long ll;

void build_trie(char s[]);
ll contains(char s[]);
ll get_word(char s[], FILE *in);
int wrong_word_cmp(const void *p1, const void *p2);
int ll_cmp(const void *p1, const void *p2);
void spell_check(void);

void build_trie(char s[])
{
    ll i, t = 1;
    for (i = 0; s[i] != '\0'; ++i)
    {
        if (isupper(s[i]))
        {
            s[i] = tolower(s[i]);
        }
        int pos = s[i] - 'a';
        if (trie[t][pos] == 0)
        {
            trie[t][pos] = ++next;
        }
        t = trie[t][pos];
    }
}

/* Checks if the trie contains the string s.
 * Returns 1 if contains; 0 if not. */
ll contains(char s[])
{
    ll i, t = 1;
    for (i = 0; s[i] != '\0'; ++i)
    {
        int pos = s[i] - 'a';
        if (trie[t][pos] == 0)
        {
            return 0;
        }
        t = trie[t][pos];
    }
    return 1;
}

ll current_pos = 0;
ll get_word(char s[], FILE *in)
{
    ll c, begin_of_word = 0, lim = MAX_LENGTH_OF_WORD;
    char *w = s;
    while (isspace(c = fgetc(in)) || isdigit(c))    /* Skips spaces and digits. */
    {
        ++current_pos;
    }
    if (c != EOF)
    {
        *w++ = tolower(c);
        begin_of_word = current_pos;
    }
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; ++w)
    {
        if (!isalpha(c = fgetc(in)))   /* End of word. */
        {
            current_pos = w + 1 - s + begin_of_word;
            break;
        }
        *w = tolower(c);
    }
    *w = '\0';
    return begin_of_word;
}

typedef struct WrongWord WrongWord;
struct WrongWord
{
    char word[MAX_LENGTH_OF_WORD];
    ll pos;
};

int wrong_word_cmp(const void *p1, const void *p2)
{
    return strcmp((*(const WrongWord **)p1)->word, (*(const WrongWord **)p2)->word);
}

int ll_cmp(const void *p1, const void *p2)
{
    return *((const ll **)p1) - *((const ll **)p2);
}

WrongWord *wrong_word_list[MAX_NUMBER_OF_WRONG_WORDS];
void spell_check(void)
{
    /* Builds the trie from dictionary.txt .*/
    FILE *dict = fopen("dictionary.txt", "r");
    if (!dict)
    {
        fprintf(stderr, "dictionary.txt cannot be opened!\n");
        return;
    }
    char word[MAX_LENGTH_OF_WORD];
    while (fgets(word, sizeof word, dict))
    {
        word[strcspn(word, "\r\n")] = 0;
        build_trie(word);
    }
    fclose(dict);
    FILE *in = fopen("article.txt", "r");
    if (!in)
    {
        fprintf(stderr, "article.txt cannot be opened\n");
        return;
    }
    char str[MAX_LENGTH_OF_WORD];
    ll begin_of_word = 0;
    ll wrong_word_count = 0;
    while ((begin_of_word = get_word(str, in)) != EOF)
    {
        if (!contains(str))
        {
            WrongWord *wwp = malloc(sizeof wrong_word_list[0]);
            if (!wwp)
            {
                fprintf(stderr, "Memory error!\n");
                return;
            }
            strcpy(wwp->word, str);
            wwp->pos = begin_of_word;
            wrong_word_list[wrong_word_count++] = wwp;
        }
    }
    qsort(wrong_word_list, wrong_word_count, sizeof wrong_word_list[0], wrong_word_cmp);

    /* Adds a sentinel node. */
    wrong_word_list[wrong_word_count] = malloc(sizeof wrong_word_list[0]);
    strcpy(wrong_word_list[wrong_word_count++]->word, "");

    /* Prints the result into misspelling.txt */
    FILE *out = fopen("misspelling.txt", "w");
    if (!out)
    {
        fprintf(stderr, "misspelling.txt cannot be opened!\n");
        return;
    }
    char last_word[MAX_LENGTH_OF_WORD] = "";
    ll i, j, pos[MAX_OCCURENCE_OF_SAME_WRONG_WORD], count = 0;
    for (i = 0; i < wrong_word_count; ++i)
    {
        if (strcmp(last_word, wrong_word_list[i]->word))    /* Meets a new word. */
        {
            if (*last_word)    /* Prints the last word if exists. */
            {
                fprintf(out, "%s ", last_word);
                qsort(pos, count, sizeof pos[0], ll_cmp);
                for (j = 0; j < count; ++j)
                {
                    fprintf(out, "%lld%c", pos[j], j == count - 1 ? '\n' : ' ');
                }
            }
            count = 0;
            strcpy(last_word, wrong_word_list[i]->word);
            pos[count++] = wrong_word_list[i]->pos;
        }
        else      /* Same word. */
        {
            pos[count++] = wrong_word_list[i]->pos;
        }
    }
    fclose(out);
}

int main(void)
{
    spell_check();
    return 0;
}
