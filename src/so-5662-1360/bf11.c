#include <stdio.h>
#include <assert.h>

static
void format_binary8v(unsigned char x, int n, char buffer[static 9])
{
    assert(n > 0 && n <= 8);
    int start = 1 << (n - 1);
    for (int b = start; b != 0; b /= 2)
    {
        *buffer++ = ((b & x) != 0) ? '1' : '0';
        x &= ~b;
    }
    *buffer = '\0';
}

static
void format_binary32(unsigned x, char buffer[static 33])
{
    for (unsigned b = 2147483648; b != 0; b /= 2)
    {
        *buffer++ = ((b & x) != 0) ? '1' : '0';
        x &= ~b;
    }
    *buffer = '\0';
}

struct R
{
    unsigned int opcode : 6;
    unsigned int rs : 5;
    unsigned int rt : 5;
    unsigned int rd : 5;
    unsigned int shamt : 5;
    unsigned int funct : 6;
};

static void dump_R(const char *tag, struct R r)
{
    union X
    {
        struct R r;
        unsigned i;
    };

    printf("%s:\n", tag);
    union X x = { .r = r };
    char buffer[33];
    format_binary32(x.i, buffer);
    printf("Binary: %s\n", buffer);
    format_binary8v(x.r.opcode, 6, buffer);
    printf(" - opcode: %s\n", buffer);
    format_binary8v(x.r.rs, 5, buffer);
    printf(" - rs:      %s\n", buffer);
    format_binary8v(x.r.rt, 5, buffer);
    printf(" - rt:      %s\n", buffer);
    format_binary8v(x.r.rd, 5, buffer);
    printf(" - rd:      %s\n", buffer);
    format_binary8v(x.r.shamt, 5, buffer);
    printf(" - shamt:   %s\n", buffer);
    format_binary8v(x.r.funct, 6, buffer);
    printf(" - funct:  %s\n", buffer);
}

int main(void)
{
    char filename[] = "filename.bin";
    FILE *fp = fopen(filename, "w+b");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file '%s' for reading and writing\n", filename);
        return 1;
    }
    struct R test  = {32, 0, 11, 21, 19, 0};
    //struct R test  = { 32, 7, 11, 21, 19, 3 };

    fwrite(&test, sizeof(test), 1, fp);

    dump_R("test - after write", test);

    rewind(fp);
    fread(&test, sizeof(test), 1, fp);
    dump_R("test - after read", test);

    fclose(fp);
    return 0;
}
