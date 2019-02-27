#include <stdio.h>
#include <string.h>

char line[1001];
char lines[11][1001];
char info[100];

char *extra_info(char string_1[], char string_2[], char string_3[],
                 char string_4[], char string_5[]);

int main(void)
{
    char result[100], text[20];
    const char filename[] = "test.txt";
    FILE *file;

    strcpy(text, "String No.");

    file = fopen(filename, "w+");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file '%s' for writing/update\n", filename);
        return 1;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i != 9)
            sprintf(result, "%s%d, ", text, i);
        else
            sprintf(result, "%s%d ", text, i);

        fprintf(stderr, "Iteration %d:\n", i);
        fprintf(stderr, "1 result (%4zu): [%s]\n", strlen(result), result);
        fprintf(stderr, "1 line   (%4zu): [%s]\n", strlen(line), line);
        extra_info("st", "nd", "rd", "th", "th");
        fprintf(stderr, "2 line   (%4zu): [%s]\n", strlen(line), line);
        fprintf(stderr, "1 info   (%4zu): [%s]\n", strlen(info), info);
        strncat(line, info, 100);
        fprintf(stderr, "3 line   (%4zu): [%s]\n", strlen(line), line);
        printf("%s", result);
        strncat(line, result, 15);
        fprintf(stderr, "3 line   (%4zu): [%s]\n", strlen(line), line);
    }

    fprintf(stderr, "4 line   (%4zu): [%s]\n", strlen(line), line);
    strncat(line, "\n\n", 2);

    for (int j = 0; j < 10; j++)
    {
        strcpy(lines[j], line);
        fputs(lines[j], file);
    }

    fclose(file);

    return 0;
}

char *extra_info(char string_1[], char string_2[], char string_3[],
                 char string_4[], char string_5[])
{
    char text[100];

    sprintf(text, " 1%s", string_1);
    fprintf(stderr, "EI 1: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_1), string_1, strlen(line), line);
    strncat(line, text, 100);

    sprintf(text, ", 2%s", string_2);
    fprintf(stderr, "EI 2: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_2), string_2, strlen(line), line);
    strncat(line, text, 100);

    sprintf(text, ", 3%s", string_3);
    fprintf(stderr, "EI 3: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_3), string_3, strlen(line), line);
    strncat(line, text, 100);

    sprintf(text, ", 4%s", string_4);
    fprintf(stderr, "EI 4: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_4), string_4, strlen(line), line);
    strncat(line, text, 100);

    sprintf(text, ", 5%s.", string_5);
    fprintf(stderr, "EI 5: add (%zu) [%s] to (%zu) [%s]\n", strlen(string_5), string_5, strlen(line), line);
    strncat(line, text, 100);

    fprintf(stderr, "EI 6: copy (%zu) [%s] to info\n", strlen(line), line);
    strcpy(info, line);

    return line;
}
