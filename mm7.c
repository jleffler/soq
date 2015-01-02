/* SO 27697228 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILEPATH "/tmp/mmapped.bin"
#define NUM_MEDS (1000)
#define FILESIZE (NUM_MEDS * sizeof(struct med))

struct med
{
    int key;
    char name[25];
    int quant_min;
    int quant;
};

static void print_med(const char *tag, const struct med *med)
{
    printf("%s: %4d: Q(%2d, min %2d): %s\n",
           tag, med->key, med->quant, med->quant_min, med->name);
}

static int med_in_map(const struct med *map, int num_meds, int key)
{
    for (int i = 0; i < num_meds; ++i)
    {
        if (key == map[i].key)
        {
            printf("Med %d already exists.\n", key);
            return 1;
        }
    }
    return 0;
}

static int get_new_key(const struct med *map, int num_meds, int *key)
{
    while (printf("Key of med: ") > 0 && scanf("%d", key) == 1)
    {
        if (med_in_map(map, num_meds, *key) == 0)
            return 0;
    }
    return EOF;
}

static int find_num_entries(const struct med *map, int max_meds)
{
    int i;
    for (i = 0; i < max_meds; i++)
    {
        if (map[i].key == 0)
            break;
    }
    return i;
}

int main(void)
{
    int fd;
    int result;
    struct med *map;

    fd = open(FILEPATH, O_RDWR | O_CREAT, (mode_t)0600);
    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    result = ftruncate(fd, FILESIZE);
    if (result == -1)
    {
        close(fd);
        perror("Error calling ftruncate() to 'set' the file size");
        exit(EXIT_FAILURE);
    }

    map = (struct med *)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    /* Input loop */
    int num_meds;
    for (num_meds = find_num_entries(map, NUM_MEDS); num_meds < NUM_MEDS; num_meds++)
    {
        struct med m;
        memset(&m, '\0', sizeof(m));

        if (get_new_key(map, num_meds, &m.key) == EOF)
            break;

        printf("Name of med: ");
        if (scanf("%s", m.name) != 1)
            break;
        printf("Quant. min. of med: ");
        if (scanf("%d", &m.quant_min) != 1)
            break;
        printf("Quant. of med: ");
        if (scanf("%d", &m.quant) != 1)
            break;

        map[num_meds] = m;

        printf("Med %d saved.\n", m.key);
    }

    /* Output loop */
    printf("\nRecorded meds:\n");
    for (int i = 0; i < num_meds; i++)
    {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "M%.4d", i);
        print_med(buffer, &map[i]);
    }

    /* Don't forget to free the mmapped memory */
    if (munmap(map, FILESIZE) == -1)
    {
        perror("Error un-mmapping the file");
        /* Decide here whether to close(fd) and exit() or not. Depends... */
    }

    /* Un-mmapping doesn't close the file, so we still need to do that.  */
    close(fd);
    return 0;
}
