/* SO 4761-5931 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct animal {
    short int id;
    char name[20];
    char species[35];
    char size;
    short int age;
};

static void debris_field(const char *tag, const char *field, size_t length)
{
    size_t nomlen = strlen(field);
    int count = 0;
    for (size_t i = nomlen; i < length; i++)
    {
        if (field[i] != '\0')
        {
            if (count == 0)
                printf("%8s (%2zu = %-20s) has debris:\n        ", tag, nomlen, field);
            count++;
            unsigned char u = field[i];
            if (isprint(u))
                putchar(u);
            else
                printf("\\x%.2X", u);
        }
    }
    if (count != 0)
        putchar('\n');
}

static void report_debris(const struct animal *info)
{
    debris_field("name", info->name, sizeof(info->name));
    debris_field("species", info->species, sizeof(info->species));
}

static void choice2(FILE *infile, int noisy)
{
    rewind(infile);
    struct animal info;
    while (fread(&info, sizeof(info), 1, infile) == 1)
    {
        if (strcmp(info.name, "unknown") == 0)
        {
            printf("Deleted: %2d %20s %30s %c %2d\n", info.id, info.name, info.species, info.size, info.age);
        }
        else
        {
            printf("Current: %2d %20s %30s %c %2d\n", info.id, info.name, info.species, info.size, info.age);
        }
        if (noisy)
            report_debris(&info);
    }
}

int main(int argc, char **argv)
{
    int noisy = 0;
    if (argc > 1 && argv[argc] == 0)    // Use argv
        noisy = 1;
    choice2(stdin, noisy);
    return 0;
}
