#include <stdio.h>
#include <assert.h>

struct R
{
    unsigned int opcode : 6;
    unsigned int rs     : 5;
    unsigned int rt     : 5;
    unsigned int rd     : 5;
    unsigned int shamt  : 5;
    unsigned int funct  : 6;
};

static void format_binary8v(unsigned char x, int n, char buffer[static 9]);
static void format_binary32(unsigned x, char buffer[static 33]);
static void dump_bitfield(int nbits, unsigned value, const char *name);
static void dump_bytes(const char *tag, struct R r);
static void dump_R(const char *tag, struct R r);
static void test_r(const char *tag, struct R r, FILE *fp);

int main(void)
{
    char filename[] = "filename.bin";
    FILE *fp = fopen(filename, "w+b");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file '%s' for reading and writing\n", filename);
        return 1;
    }

    struct R r1  = { 32, 0, 11, 21, 19, 0 };
    struct R r2  = { 32, 7, 11, 21, 19, 3 };

    test_r("r1", r1, fp);
    test_r("r2", r2, fp);

    fclose(fp);
    return 0;
}

static void test_r(const char *tag, struct R r, FILE *fp)
{
    char buffer[32];
    long offset = sizeof(struct R);
    fwrite(&r, sizeof(r), 1, fp);
    snprintf(buffer, sizeof(buffer), "%s - after write", tag);
    dump_R(buffer, r);
    fseek(fp, -offset, SEEK_CUR);
    fread(&r, sizeof(r), 1, fp);
    fseek(fp, 0, SEEK_CUR);             // Ready for reading or writing!
    snprintf(buffer, sizeof(buffer), "%s - after read", tag);
    dump_R(buffer, r);
}

static void dump_R(const char *tag, struct R r)
{
    printf("%s:\n", tag);
    dump_bytes("Binary", r);
    dump_bitfield(6, r.opcode, "opcode");
    dump_bitfield(5, r.rs,     "rs");
    dump_bitfield(5, r.rt,     "rt");
    dump_bitfield(5, r.rd,     "rd");
    dump_bitfield(5, r.shamt,  "shamt");
    dump_bitfield(6, r.funct,  "funct");
}

static void dump_bytes(const char *tag, struct R r)
{
    union X
    {
        struct R r;
        unsigned i;
    };
    union X x = { .r = r };
    char buffer[33];
    format_binary32(x.i, buffer);
    printf("%s: %s\n", tag, buffer);
    printf("%s:", tag);
    for (int i = 0; i < 4; i++)
        printf(" %.8s", &buffer[8 * i]);
    putchar('\n');
}

static void dump_bitfield(int nbits, unsigned value, const char *name)
{
    assert(nbits > 0 && nbits <= 32);
    char vbuffer[33];
    char nbuffer[8];
    snprintf(nbuffer, sizeof(nbuffer), "%s:", name);
    format_binary8v(value, nbits, vbuffer);
    printf(" - %-7s  %6s  (%u)\n", nbuffer, vbuffer, value);
}

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
