/* SO 5201-4002 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_WORD_CNT = 8 };

#ifdef TEST
static int debug = 1;
enum { MAX_LINE_LEN = 64 };
#else
static int debug = 0;
enum { MAX_LINE_LEN = 4096 };
#endif /* TEST */

typedef struct Word
{
    size_t length;
    char  *word;
} Word;

typedef struct WordList
{
    size_t  num_words;
    size_t  max_words;
    Word   *words;
} WordList;

typedef struct LineControl
{
    size_t   line_length;
    bool     part_word;
    size_t   part_len;
    WordList list;
} LineControl;

static void init_wordlist(WordList *list)
{
    list->num_words = 0;
    list->max_words = 0;
    list->words = 0;
}

static void free_wordlist(WordList *list)
{
    assert(list != 0);
    for (size_t i = 0; i < list->num_words; i++)
        free(list->words[i].word);
    free(list->words);
    init_wordlist(list);
}

static void extend_word(const char *extn, size_t ext_len, Word *word)
{
    if (debug)
        printf("old (%zu) = [%s]; extra (%zu) = [%.*s]\n", word->length, word->word,
                ext_len, (int)ext_len, extn);
    size_t space = word->length + ext_len + 1;
    char *new_space = realloc(word->word, space);
    if (new_space == 0)
    {
        fprintf(stderr, "failed to reallocate %zu bytes of memory\n", space);
        exit(EXIT_FAILURE);
    }
    word->word = new_space;
    memmove(word->word + word->length, extn, ext_len);
    word->length += ext_len;
    word->word[word->length] = '\0';
    if (debug)
        printf("new (%zu) = [%s]\n", word->length, word->word);
    }

static void addword_wordlist(const char *word, size_t word_len, WordList *list)
{
    if (list->num_words >= list->max_words)
    {
        assert(list->num_words == list->max_words);
        size_t new_max = list->max_words * 2 + 2;
        Word *new_words = realloc(list->words, new_max * sizeof(*new_words));
        if (new_words == 0)
        {
            fprintf(stderr, "failed to allocate %zu bytes of memory\n", new_max * sizeof(*new_words));
            exit(EXIT_FAILURE);
        }
        list->max_words = new_max;
        list->words = new_words;
    }
    list->words[list->num_words].word = malloc(word_len + 1);
    if (list->words[list->num_words].word == 0)
    {
        fprintf(stderr, "failed to allocate %zu bytes of memory\n", word_len + 1);
        exit(EXIT_FAILURE);
    }
    Word *wp = &list->words[list->num_words];
    wp->length = word_len;
    memmove(wp->word, word, word_len);
    wp->word[word_len] = '\0';
    list->num_words++;
}

static void init_linectrl(LineControl *ctrl)
{
    ctrl->line_length = 0;
    ctrl->part_word = false;
    ctrl->part_len = 0;
    init_wordlist(&ctrl->list);
}

static int parse_fragment(const char *line, LineControl *ctrl)
{
    char   whisp[] = " \t";
    size_t offset = 0;
    bool   got_eol = false;

    /* The only newline in the string is at the end, if it is there at all */
    assert(strchr(line, '\n') == strrchr(line, '\n'));
    assert(strchr(line, '\n') == 0 || *(strchr(line, '\n') + 1) == '\0');
    if (debug && ctrl->part_word)
    {
        assert(ctrl->list.num_words > 0);
        printf("Dealing with partial word on entry (%zu: [%s])\n",
               ctrl->part_len, ctrl->list.words[ctrl->list.num_words - 1].word);
    }

    size_t o_nonsp = 0;
    while (line[offset] != '\0')
    {
        size_t n_whisp = strspn(line + offset, whisp);
        size_t n_nonsp = strcspn(line + offset + n_whisp, whisp);
        if (debug)
            printf("offset %zu, whisp %zu, nonsp %zu\n", offset, n_whisp, n_nonsp);
        got_eol = false;
        ctrl->line_length += n_whisp + n_nonsp;
        if (line[offset + n_whisp + n_nonsp - 1] == '\n')
        {
            assert(n_nonsp > 0);
            got_eol = true;
            n_nonsp--;
        }
        if (n_whisp + n_nonsp == 0)
        {
            o_nonsp = 0;
            break;
        }

        if (n_whisp != 0)
        {
            ctrl->part_word = false;
            ctrl->part_len = 0;
        }

        /* Add words to list if the list is not already full */
        if (n_nonsp > 0)
        {
            const char *word = line + offset + n_whisp;
            if (ctrl->part_word)
            {
                assert(ctrl->list.num_words > 0);
                extend_word(word, n_nonsp,
                            &ctrl->list.words[ctrl->list.num_words - 1]);
            }
            else
            {
                addword_wordlist(word, n_nonsp, &ctrl->list);
            }
        }

        offset += n_whisp + n_nonsp;
        if (line[offset] != '\0')
        {
            ctrl->part_word = false;
            ctrl->part_len = 0;
        }
        o_nonsp = n_nonsp;
        if (got_eol)
            break;
    }

    /* Partial word detection */
    if (o_nonsp > 0 && !got_eol)
    {
        ctrl->part_word = true;
        ctrl->part_len += o_nonsp;
    }
    else
    {
        ctrl->part_word = false;
        ctrl->part_len = 0;
    }

    /* If seen newline; line complete */
    /* If No newline; line incomplete */
    return !got_eol;
}

int main(void)
{
    char line[MAX_LINE_LEN];
    size_t lineno = 0;

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        LineControl ctrl;
        init_linectrl(&ctrl);
        lineno++;
        if (debug)
            printf("Line %zu: (%zu) [[%s]]\n", lineno, strlen(line), line);

        int extra = 0;
        while (parse_fragment(line, &ctrl) != 0 &&
               fgets(line, sizeof(line), stdin) != 0)
        {
            if (debug)
                printf("Extra %d for line %zu: (%zu) [[%s]]\n",
                       ++extra, lineno, strlen(line), line);
        }

        WordList *list = &ctrl.list;
        printf("Line %zu: length %zu, words = %zu\n",
               lineno, ctrl.line_length, list->num_words);
        size_t num_words = list->num_words;
        if (num_words > MAX_WORD_CNT)
            num_words = MAX_WORD_CNT;
        for (size_t i = 0; i < num_words; i++)
        {
            printf("  %zu: (%zu) %s\n",
                   i + 1, list->words[i].length, list->words[i].word);
        }
        putchar('\n');
        free_wordlist(&ctrl.list);
    }

    return 0;
}
