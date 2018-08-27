/* SO 5201-4002 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { MAX_WORD_CNT = 4 };

#ifdef TEST
static int debug = 1;
enum { MAX_WORD_LEN = 8 };
//enum { MAX_LINE_LEN = 64 };
enum { MAX_LINE_LEN = 6 };
#else
static int debug = 0;
enum { MAX_WORD_LEN = 32 };
enum { MAX_LINE_LEN = 4096 };
#endif /* TEST */

typedef struct LineControl
{
    size_t  lineno;
    size_t  line_length;
    size_t  num_words;
    bool    part_word;
    size_t  part_len;
    char    words[MAX_WORD_CNT][MAX_WORD_LEN+1];
} LineControl;

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
        assert(ctrl->num_words > 0);
        printf("Dealing with partial word on entry (%zu: [%s])\n",
               ctrl->part_len, ctrl->words[ctrl->num_words - 1]);
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

        /* Detect and report overlong words */
        if (ctrl->part_word && n_whisp == 0 && (n_nonsp + ctrl->part_len) > MAX_WORD_LEN)
        {
            size_t len = n_nonsp + ctrl->part_len;
            fprintf(stderr, "Line %zu: partial word %zu is too long (%zu: [%s%.*s])\n",
                    ctrl->lineno, ctrl->num_words, len, ctrl->words[ctrl->num_words - 1], (int)n_nonsp,
                    line + offset + n_whisp); 
        }
        else if (n_nonsp > MAX_WORD_LEN)
            fprintf(stderr, "Line %zu: word %zu is too long (%zu: [%.*s])\n",
                    ctrl->lineno, ctrl->num_words + 1, n_nonsp, (int)n_nonsp,
                    line + offset + n_whisp); 

        if (n_whisp != 0)
        {
            ctrl->part_word = false;
            ctrl->part_len = 0;
        }

        /* Add words to list if the list is not already full */
        if ((ctrl->num_words < MAX_WORD_CNT || ctrl->part_word) && n_nonsp > 0)
        {
            size_t copy = n_nonsp;
            size_t word_num = ctrl->num_words;
            if (ctrl->part_word && n_whisp == 0)
            {
                printf("Processing part word (%zu) [[%s]]\n", ctrl->part_len,
                       ctrl->words[ctrl->num_words - 1]);
                word_num--;
            }
            if (ctrl->part_len < MAX_WORD_LEN)
            {
                if (copy > (MAX_WORD_LEN - ctrl->part_len))
                    copy = MAX_WORD_LEN - ctrl->part_len;
                assert(word_num < MAX_WORD_CNT);
                memmove(&ctrl->words[word_num][ctrl->part_len],
                        line + offset + n_whisp, copy);
                ctrl->words[word_num][ctrl->part_len + copy] = '\0';
                ctrl->part_len += copy;
                printf("Word %zu: (%zu) [%s]\n", word_num + 1, ctrl->part_len, ctrl->words[word_num]);
            }
        }

        if (n_nonsp > 0 && !ctrl->part_word)
            ctrl->num_words++;
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
        printf("<<-- (1) part_len = %zu\n", ctrl->part_len);
    }
    else
    {
        ctrl->part_word = false;
        ctrl->part_len = 0;
        printf("<<-- (2) part_len = %zu\n", ctrl->part_len);
    }

    /* If seen newline; line complete */
    /* If No newline; line incomplete */
    return !got_eol;
}

int main(void)
{
    char line[MAX_LINE_LEN];
    LineControl ctrl;

    ctrl.lineno = 0;

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        ctrl.lineno++;
        ctrl.line_length = 0;
        ctrl.num_words = 0;
        ctrl.part_word = false;
        ctrl.part_len = 0;
        if (debug)
            printf("Line %zu: [[%s]]\n", ctrl.lineno, line);        // Debug

        int extra = 0;
        while (parse_fragment(line, &ctrl) != 0 &&
               fgets(line, sizeof(line), stdin) != 0)
        {
            if (debug)
                printf("Extra %d for line %zu: [[%s]]\n", ++extra, ctrl.lineno, line);   // Debug
        }

        printf("Line %zu: length %zu, words = %zu\n",
               ctrl.lineno, ctrl.line_length, ctrl.num_words);
        size_t num_words = ctrl.num_words;
        if (num_words > MAX_WORD_CNT)
            num_words = MAX_WORD_CNT;
        for (size_t i = 0; i < num_words; i++)
            printf("  %zu: %s\n", i+1, ctrl.words[i]);
        putchar('\n');
    }

    return 0;
}
