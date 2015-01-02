/* SO 27697228 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILEPATH "/tmp/mmapped.bin"
#define NUMINTS (1000)
#define FILESIZE (NUMINTS * sizeof(struct med))

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

int main(void)
{
    int fd;
    int result;
    struct med *map;  /* mmapped array of structs */

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmapping.
     */
    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    /* NB: ftruncate(fd, FILESIZE); is simpler */
    /* Stretch the file size to the size of the (mmapped) array of structs */
    result = lseek(fd, FILESIZE - 1, SEEK_SET);
    if (result == -1)
    {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    /* Something needs to be written at the end of the file to
     * have the file actually have the new size.
     * Just writing an empty string at the current file position will do.
     *
     * Note:
     *  - The current position in the file is at the end of the stretched
     *    file due to the call to lseek().
     *  - An empty string is actually a single '\0' character, so a zero-byte
     *    will be written at the last byte of the file.
     */
    result = write(fd, "", 1);
    if (result != 1)
    {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    /* Now the file is ready to be mmapped.  */
    map = (struct med *)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }

    /* Input loop */
    int num_meds;
    for (num_meds = 0; num_meds < NUMINTS; num_meds++)
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

    /* Remove file? */
    /* unlink(FILEPATH); */
}
