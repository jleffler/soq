/* SO 3945-8053 Determine shift used for text encrypted using Caesar Cipher */

#include "posixver.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/* Letter frequencies a-z in English */
static const float freq_en[] =
{
    .082, .015, .028, .043, .127, .022,
    .020, .061, .070, .002, .008, .040,
    .024, .067, .075, .019, .001, .060,
    .063, .091, .028, .010, .024, .002,
    .020, .001
};

int main(void)
{
    char *buffer = 0;
    size_t buflen = 0;
    size_t freq[26] = { 0 };
    size_t count = 0;

    while (getline(&buffer, &buflen, stdin) != -1)
    {
        char *ptr = buffer;
        unsigned char u;
        while ((u = (unsigned char)*ptr++) != '\0')
        {
            if (isalpha(u))
            {
                count++;
                freq[tolower(u) - 'a']++;
            }
        }
    }
    free(buffer);

    if (count == 0)
    {
        fprintf(stderr, "No data read!\n");
        return 1;
    }

    double chisq[26];
    for (int shift = 0; shift < 26; shift++)
    {
        chisq[shift] = 0.0;
        for (int letter = 0; letter < 26; letter++)
        {
            int index = (shift + letter) % 26;
            double delta = freq[index] - count * freq_en[letter];
            chisq[shift] += (delta * delta) / (count * freq_en[letter]);
        }
        printf("'%c' = %13.6f\n", shift + 'A', chisq[shift]);
    }

    int min_i = 0;
    double val_i = chisq[0];
    for (int i = 1; i < 26; i++)
    {
        if (chisq[i] < val_i)
        {
            val_i = chisq[i];
            min_i = i;
        }
    }

    printf("Best match is (%d) '%c' = %10.6f\n", min_i, min_i + 'A', val_i);
    return 0;
}

