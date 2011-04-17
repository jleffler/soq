#ifndef B_TREE_FILE_H_INCLUDED
#define B_TREE_FILE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//defs of pre-compiler

#ifdef __linux
#define PAUSA "read p"
#define CLRSCR "clear"
#else
#define PAUSA "Pause"
#define CLRSCR "cls"
#endif

#define T 5 // minimum degree of B-tree
#define Min (T-1)
#define Max ((2*T)-1)

//global vars
extern FILE *arqt, *arqb;
extern char VAL[11];
extern long int lt;

typedef struct
{
    unsigned int num;
    long int pos;
    char chave[(Max+1)][11]; //chave in portuguese = key in english!
    short int folha; //folha in portuguese = leaf in english!
    long int c[(Max+2)];
} Nod;

extern Nod *raiz; //raiz in portuguese = root in english!

extern long int fSize(FILE *arq);
extern void b_split(Nod *x, unsigned int i, Nod *y);
void b_ins(Nod *x, char *val);
void insere_b(char *val);
void busca_b(Nod *x, char *val);
void cria_b(void);
void insere_l(char *val);
void busca_l(char *val);
void busca(short int op);
void insere(short int op);
void maiuscula (char *S, short int i);

#endif /* B_TREE_FILE_H_INCLUDED */
