/* SO 5201-4002 */
#include <assert.h>
#include <stdio.h>
#include <string.h>

enum { MAX_WORD_CNT = 4 };

#ifdef TEST
static int debug = 1;
enum { MAX_WORD_LEN = 8 };
enum { MAX_BUFF_LEN = 64 };
#else
static int debug = 0;
enum { MAX_WORD_LEN = 32 };
enum { MAX_BUFF_LEN = 4096 };
#endif /* TEST */

typedef struct LineControl
{
    size_t  lineno;
    size_t  line_length;
    size_t  num_words;
    char    words[MAX_WORD_CNT][MAX_WORD_LEN+1];
} LineControl;

static int parse_fragment(const char *line, LineControl *ctrl)
{
    char   whisp[] = " \t";
    size_t offset = 0;

    /* The only newline in the string is at the end, if it is there at all */
    assert(strchr(line, '\n') == strrchr(line, '\n'));
    assert(strchr(line, '\n') == 0 || *(strchr(line, '\n') + 1) == '\0');

    while (line[offset] != '\0')
    {
        size_t n_whisp = strspn(line + offset, whisp);
        size_t n_nonsp = strcspn(line + offset + n_whisp, whisp);
        if (debug)
            printf("offset %zu, whisp %zu, nonsp %zu\n", offset, n_whisp, n_nonsp);
        if (n_whisp + n_nonsp == 0)
            break;
        int newline = 0;
        ctrl->line_length += n_whisp + n_nonsp;
        if (line[offset + n_whisp + n_nonsp - 1] == '\n')
        {
            assert(n_nonsp > 0);
            newline = 1;
            n_nonsp--;
        }
        if (n_nonsp > MAX_WORD_LEN)
            fprintf(stderr, "Line %zu: word %zu is too long (%zu: [%.*s])\n",
                    ctrl->lineno, ctrl->num_words + 1, n_nonsp, (int)n_nonsp,
                    line + offset + n_whisp); 
        if (ctrl->num_words < MAX_WORD_CNT && n_nonsp > 0)
        {
            size_t copy = n_nonsp;
            if (copy > MAX_WORD_LEN)
                copy = MAX_WORD_LEN;
            memmove(ctrl->words[ctrl->num_words], line + offset + n_whisp, copy);
            ctrl->words[ctrl->num_words][copy] = '\0';
        }
        if (n_nonsp > 0)
            ctrl->num_words++;
        offset += n_whisp + n_nonsp;
        if (newline != 0)
            return 0;       /* Newline seen; line complete */
    }
    return 1;               /* No newline; line incomplete */
}

int main(void)
{
    char line[MAX_BUFF_LEN];
    LineControl ctrl = { 0, 0, 0, { { 0 } } };

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        ctrl.lineno++;
        ctrl.line_length = 0;
        ctrl.num_words = 0;
        if (debug)
            printf("Line %zu: [[%s]]\n", ctrl.lineno, line);        // Debug

        while (parse_fragment(line, &ctrl) != 0 &&
               fgets(line, sizeof(line), stdin) != 0)
        {
            if (debug)
                printf("Extra %zu: [[%s]]\n", ctrl.lineno, line);   // Debug
        }

        printf("Line %zu: length %zu, words = %zu\n",
               ctrl.lineno, ctrl.line_length, ctrl.num_words);
        size_t num_words = ctrl.num_words;
        if (num_words > MAX_WORD_CNT)
            num_words = MAX_WORD_CNT;
        for (size_t i = 0; i < num_words; i++)
            printf("  %zu: %s\n", i+1, ctrl.words[i]);
    }
    return 0;
}
