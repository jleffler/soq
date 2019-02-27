/* Code from deleted question SO 3611-6746 */


/*
** Full code AVL tree implementation of a list within a tree. 3 items in a
** node of the tree are required per keyword.  Searching algorithms to be
** used are EQUAL, OR and AND.
*/

/* header file avltree.h */

typedef struct keyword
{
    char *tree;
    char *i[30];
    struct list *items[50];
    struct keyword *left;
    struct keyword *right;
    int height;
} keyword;

typedef struct list
{
    char *items[50];
    struct list *next;
} list;

extern keyword *ins(char *e, keyword *t);

static keyword *singleright(keyword *k1);
static keyword *doubleright(keyword *k1);
static keyword *singleleft(keyword *k2);
static keyword *doubleleft(keyword *k3);
static int max(int l, int r);
static int height(keyword *n);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "avltree.h"

int main(void)
{
    keyword *base = NULL;
    keyword *key;
    // list *List;
    int x;

    key = (keyword *)malloc(sizeof(keyword));
    // List=(list *)malloc(sizeof(list));
    key->i[0] = "RTS";
    key->i[1] = "Simulation";
    key->i[2] = "Visual Novel";
    key->i[3] = "Anime";
    key->i[4] = "JRPG";
    key->i[5] = "RPG";
    key->i[6] = "Action";
    key->i[7] = "Third-person shooter";
    key->i[8] = "Historical";
    key->i[9] = "Platformer";
    key->i[10] = "Indie";
    key->i[11] = "Horror";
    key->i[12] = "8bit";
    key->i[13] = "Survival";
    key->i[14] = "Turn based";
    key->i[15] = "Building";
    key->i[16] = "Adventure";
    key->i[17] = "Sci-fi";
    key->i[18] = "Flash";
    key->i[19] = "MOBA";
    key->i[20] = "Singleplayer";
    key->i[21] = "Tactical";
    key->i[22] = "Crafting";
    key->i[23] = "Post-apocalyptic";
    key->i[24] = "Funny";
    key->i[25] = "Open World";
    key->i[26] = "Multiplayer";
    key->i[27] = "Underwater";
    key->i[28] = "FPS";
    key->i[29] = "Puzzles";

//    (*List).items[0]="Red Alert 2";
//    (*List).items[1]="Shower Simulator";
//    (*List).items[2]="Terraria";
//    (*List).items[3]="Super mario";
//    (*List).items[4]="bomberman";
//    (*List).items[5]="Payday 2";
//    (*List).items[6]="Goat Simulator";
//    (*List).items[7]="Dota 2";
//    (*List).items[8]="LoL";
//    (*List).items[9]="Heroes of the storm";
//    (*List).items[10]="Witcher 3: wild hunt";
//    (*List).items[11]="7 days to die";
//    (*List).items[12]="Left 4 dead";
//    (*List).items[13]="Plague.inc";
//    (*List).items[14]="Nekopara.vol1";
//    (*List).items[15]="Sakura angels";
//    (*List).items[16]="CSGO";
//    (*List).items[17]="Sid Meier's Civilization V";
//    (*List).items[18]="Besiege";
//    (*List).items[19]="Don't Starve";
//    (*List).items[20]="Don't Starve together";
//    (*List).items[21]="Hunie pop";
//    (*List).items[22]="Recettear";
//    (*List).items[23]="Dark Souls";
//    (*List).items[24]="Hustle Cat";
//    (*List).items[25]="ARK";
//    (*List).items[21]="Defy Gravity";
//    (*List).items[22]="XCOM2";
//    (*List).items[23]="Feelings Adrift";
//    (*List).items[24]="Layers of fear";
//    (*List).items[25]="Khanonline";
//    (*List).items[26]="Starwars Republic Commando";
//    (*List).items[27]="Tales of Zestiria";
//    (*List).items[28]="Sakura Spirit";
//    (*List).items[29]="Dysnasty warriors 8";
//    (*List).items[30]="Undertale";
//    (*List).items[31]="Portal";
//    (*List).items[32]="Insaniquarium";
//    (*List).items[33]="Feeding Frenzy";
//    (*List).items[34]="Mortal Kombat X";
//    (*List).items[35]="Tomb Runner";
//    (*List).items[36]="Whack your boss";
//    (*List).items[37]="Last of us";
//    (*List).items[38]="Garry's mod'";
//    (*List).items[39]="101 ways to die";
//    (*List).items[40]="Minecraft";
//    (*List).items[41]="The Forest";
//    (*List).items[42]="World End economica episode.02";
//    (*List).items[43]="Artifact Adventure";
//    (*List).items[44]="Akiba's Trip:Undead & Undressed";
//    (*List).items[45]="Sakura Fantasy Chapter 1";
//    (*List).items[46]="Machina of the Planet";
//    (*List).items[47]="Love at First Sight";
//    (*List).items[48]="Corpse Party";
//    (*List).items[49]="Half-minute Hero";

    for (x = 0; x < 30; ++x)
    {
        base = ins(key->i[x], base);
    }

    return 0;
}

/*tree.c*/

keyword *ins(char *e, keyword *t)
{
    if (t == NULL)
    {
        t = (keyword *)malloc(sizeof(keyword));
        if (t == NULL)
        {
            printf("Out of memory!!!(insert)\n");
            exit(1);
        }
        else
        {
            t->tree = e;
            t->height = 0;
            t->right = t->left = NULL;
        }
    }
    else if (strcmp(e, t->tree) < 0)
    {
        t->left = ins(e, t->left);
        if (height(t->left) - height(t->right) == 2)
            t = singleleft(t);
        else
            t = doubleleft(t);
    }
    else if (strcmp(e, t->tree) > 0)
    {
        t->right = ins(e, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (strcmp(e, t->right->tree) > 0)
                t = singleright(t);
            else
                t = doubleright(t);
        }
    }
    else
        printf("Duplicate entry! (%s) vs (%s)\n", e, t->tree);
    t->height = max(height(t->left), height(t->right)) + 1;
    printf("[%s]\n", t->tree);
    return t;
}

static keyword *doubleleft(keyword *k3)
{
    /* Rotate between k1 and k2 */
    k3->left = singleright(k3->left);
    /* Rotate between K3 and k2 */
    return singleleft(k3);
}

static keyword *singleleft(keyword *k2)
{
    keyword *k1 = NULL;
    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    return k1; /* new root */
}

static keyword *singleright(keyword *k1)
{
    keyword *k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;

    return k2;  /* New root */
}

static keyword *doubleright(keyword *k1)
{
    /* rotate between K3 and k2 */
    k1->right = singleleft(k1->right);

    /* rotate between k1 and k2 */
    return singleright(k1);
}

static int max(int l, int r)
{
    return l > r ? l : r;
}

static int height(keyword *n)
{
    if (n == NULL)
        return -1;
    else
        return n->height;
}
