/* SO 4801-3629 */
/* Code by J Guo (https://stackoverflow.com/users/8777237/j-guo) */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char *stnc_org, *stnc_new;
    int size;
    printf("What is the expected size of the sentence: ");
    if (scanf("%d", &size) != 1)
	exit(1);
    stnc_org = (char *)malloc(size * sizeof(char));
    char *stnc_free = stnc_org;

    printf("Input: \n");
    if (scanf(" %[^\n]", stnc_org) != 1)
	exit(1);

    // get the number of punct
    int punct_num = 0;
    int i;
    for (i = 0; *(stnc_org + i) != '\0'; i++) {
        if (ispunct(*(stnc_org + i))) {
            punct_num++;
        }
    }

    char * stnc_backup = (char *)malloc((size + punct_num) * sizeof(char));
    stnc_new = stnc_backup;

    // copy the original str to the new and add space before each punc
    for (i = 0; *(stnc_org + i) != '\0'; i++) {
        if (ispunct(*(stnc_org + i))) {
            // copy the content before the punctuation
            strncpy(stnc_new, stnc_org, i);
            // insert a space character before copying the punctuation
            *(stnc_new + i) = ' ';
            *(stnc_new + i + 1) = *(stnc_org + i);
            // add the terminating null character to the copy text
            // when reaching the end of the original text
            if (*(stnc_org + i + 1) == '\0') {
                *(stnc_new + i + 2) = '\0';
            }
            // reset the pointers and the index i
            stnc_new = stnc_new + (i + 1);
            stnc_org = stnc_org + i;
            i = 0;
        }
    }

    printf("\nOutput:\n");
    char *str;
    str = strtok(stnc_backup, " \n\r");

    while(str != NULL) {
        printf("%s\n", str);
        str = strtok(NULL, " \n\r");
    }

    free(stnc_free);        // JL: added
    free(stnc_backup);      // JL: added
    return 0;               // JL: added
}
