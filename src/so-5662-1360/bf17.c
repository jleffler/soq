#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct R
{
    unsigned int opcode : 6;
    unsigned int rs     : 5;
    unsigned int rt     : 5;
    unsigned int rd     : 5;
    unsigned int shamt  : 5;
    unsigned int funct  : 6;
};

static void test_u(const char *tag, unsigned u, FILE *fp);
static void run_xxd(const char *file);

int main(void)
{
    char filename[] = "filename.bin";
    FILE *fp = fopen(filename, "w+b");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open file '%s' for reading and writing\n", filename);
        return 1;
    }

    unsigned int u[] = { 0x46554E21, 0x214E5546 };
    enum { NUM_U = sizeof(u) / sizeof(u[0]) };

    for (int i = 0; i < NUM_U; i++)
    {
        char name[16];
        snprintf(name, sizeof(name), "u%d", i+1);
        test_u(name, u[i], fp);
    }

    fclose(fp);

    run_xxd(filename);

    return 0;
}

static void run_one_xxd(const char *command, const char *filename)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "%s %s", command, filename);
    printf("\nCommand: %s\n", cmd);
    system(cmd);
    putchar('\n');
}

static void run_xxd(const char *filename)
{
    run_one_xxd("xxd -c 4 -b     ", filename);
    run_one_xxd("xxd -c 4 -g 1 -u", filename);
}

static void format_binary8v(unsigned char x, int n, char buffer[static 9]);
static void format_binary32(unsigned x, char buffer[static 33]);
static void dump_bitfield(int nbits, unsigned value, const char *name);
static void dump_bytes(const char *tag, struct R r);
static void dump_U(const char *tag, unsigned u);

static void test_u(const char *tag, unsigned u, FILE *fp)
{
    char buffer[32];
    long offset = sizeof(unsigned);
    putchar('\n');
    fwrite(&u, sizeof(u), 1, fp);
    snprintf(buffer, sizeof(buffer), "%s - after write", tag);
    dump_U(buffer, u);
    fseek(fp, -offset, SEEK_CUR);
    unsigned v;
    fread(&v, sizeof(v), 1, fp);
    fseek(fp, 0, SEEK_CUR);             // Ready for reading or writing!
    snprintf(buffer, sizeof(buffer), "%s - after read", tag);
    dump_U(buffer, v);
    assert(u == v);
}

static void dump_U(const char *tag, unsigned u)
{
    printf("%s:\n", tag);
    union X
    {
        struct R r;
        unsigned u;
    };
    union X x = { .u = u };
    printf("%s: 0x%.8X (%.4s)\n", tag, u, (char *)&u);
    dump_bytes("Binary", x.r);
    dump_bitfield(6, x.r.opcode, "opcode");
    dump_bitfield(5, x.r.rs,     "rs");
    dump_bitfield(5, x.r.rt,     "rt");
    dump_bitfield(5, x.r.rd,     "rd");
    dump_bitfield(5, x.r.shamt,  "shamt");
    dump_bitfield(6, x.r.funct,  "funct");
}

static void dump_bytes(const char *tag, struct R r)
{
    union X
    {
        struct R r;
        unsigned u;
    };
    union X x = { .r = r };
    char buffer[33];
    format_binary32(x.u, buffer);
    printf("%s: MSB", tag);
    for (int i = 0; i < 4; i++)
        printf(" %.8s", &buffer[8 * i]);
    puts(" LSB (big-endian)");
    printf("%s: LSB", tag);
    for (int i = 0; i < 4; i++)
        printf(" %.8s", &buffer[8 * (3 - i)]);
    puts(" MSB (little-endian)");
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
