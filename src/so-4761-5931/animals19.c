/* SO 4761-5931 */
#include <stdio.h>

static void choice3(FILE *infile, int id)
{
    int animalID = -37;
    char animalName[20];
    char animalType[20];
    char animalSize;
    int animalAge;
    while (fscanf(infile, "%d , %19[^,] , %19[^,] , %c , %d",
                  &animalID, animalName, animalType, &animalSize, &animalAge) == 5)
    {
        printf("Read: %d: %s, %s, %c, %d\n",
               animalID, animalName, animalType, animalSize, animalAge);
        if (animalID == id)
        {
            printf("Animal Found: %d: %s, %s, %c, %d\n",
                   animalID, animalName, animalType, animalSize, animalAge);
        }
    }
    if (feof(infile))
        printf("EOF\n");
    else
        printf("Format error\n");
}

int main(void)
{
    choice3(stdin, 3);
    return 0;
}
