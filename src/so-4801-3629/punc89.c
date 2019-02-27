/* SO 4801-3269 */
/* J Guo - second solution */

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

    char *stnc_backup = (char *)malloc((size + punct_num * 2) * sizeof(char));
    stnc_new = stnc_backup;

    // copy the original str to the new and add space before each punct
    for (i = 0; *(stnc_org + i) != '\0'; i++) {
        if (ispunct(*(stnc_org + i))) { // found a punct
            // boundary check!!!
            // 1. the first character is the punct
            if (i == 0) {
                *(stnc_new + i) = *(stnc_org + i);
                *(stnc_new + i + 1) = ' ';
                stnc_new = stnc_new + (i + 2);
            }
            // 2. the last character is the punct
            else if (*(stnc_org + i + 1) == '\0') {
                if (*(stnc_org + i - 1) != ' ') {
                    strncpy(stnc_new, stnc_org, i);
                    *(stnc_new + i) = ' ';
                    *(stnc_new + i + 1) = *(stnc_org + i);
                    *(stnc_new + i + 2) = '\0';
                    stnc_new = stnc_new + (i + 1);
                }
            }

            // check the previous and next characters of the punct
            // 3. previous not the space && next is space -> insert ' ' before the punct
            else if (*(stnc_org + i - 1) != ' ' && *(stnc_org + i + 1) == ' ') {
                strncpy(stnc_new, stnc_org, i);
                *(stnc_new + i) = ' ';
                *(stnc_new + i + 1) = *(stnc_org + i);
                stnc_new = stnc_new + (i + 1);
            }

            // 4. previous is space && next is not space -> insert ' ' after the punct
            else if (*(stnc_org + i - 1) == ' ' && *(stnc_org + i + 1) != ' ') {
                strncpy(stnc_new, stnc_org, i);
                *(stnc_new + i) = *(stnc_org + i);
                *(stnc_new + i + 1) = ' ';
                stnc_new = stnc_new + (i + 2);
            }

            // 5. no space before or after -> insert ' ' both before and after the punct
            else if (*(stnc_org + i - 1) != ' ' && *(stnc_org + i + 1) != ' ') {
                strncpy(stnc_new, stnc_org, i);
                *(stnc_new + i) = ' ';
                *(stnc_new + i + 1) = *(stnc_org + i);
                *(stnc_new + i + 2) = ' ';
                stnc_new = stnc_new + (i + 3);
            }

            // reset the pointer of the original text
            stnc_org = stnc_org + i + 1;
            // reset the index, so that it starts from 0 in the next loop
            i = -1;
        }
    }

    //printf("%s\n", stnc_backup);

    printf("\nOutput:\n");
    char *str;
    str = strtok(stnc_backup, " \n\r");

    while(str != NULL) {
        printf("%s\n", str);
        str = strtok(NULL, " \n\r");
    }
}
