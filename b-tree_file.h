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
//

//global vars
    FILE *arqt, *arqb;

    char VAL[11];
    long int lt = 0;

    typedef struct {
        unsigned int num;
        long int pos;
        char chave[(Max+1)][11]; //chave in portuguese = key in english!
        short int folha; //folha in portuguese = leaf in english!
        long int c[(Max+2)];
    } Nod;

    Nod *raiz = NULL; //raiz in portuguese = root in english!
//

long int fSize (FILE *arq) { //return size of text file...

    fpos_t Pos;
    long int tam=0;

    fgetpos(arq,&Pos);
    rewind(arq);

    while(feof(arq) == 0) {
        if (fgetc(arq) == '\n') {tam++;}
    }

    fseek(arq,(-1),SEEK_END);
    if (fgetc(arq) != '\n') {tam++;}

    fsetpos(arq,&Pos);

    return tam;
}

void b_split(Nod *x, unsigned int i, Nod *y) { //B-TREE-SPLIT-CHILD //that function split a B-tree node
    Nod *z = NULL;
    unsigned int j=1;

    z = (Nod*)realloc(z,sizeof(Nod));

    fseek(arqb,0,SEEK_END);
    z->pos = ftell(arqb);

    z->folha = y->folha;
    z->num = Min;

    for(j=1;j<=Min;j++) {strcpy(z->chave[j],y->chave[j+T]);}

    if (y->folha == 0) {
        for(j=1;j<=T;j++) {z->c[j] = y->c[j+T];}

    }

    y->num = Min;

    for(j=(x->num + 1);j<=(i+1);j--) {x->c[(j+1)] = x->c[j];}

    x->c[(i+1)] = z->pos;

    for(j=x->num;j<=i;j--) { strcpy(x->chave[j+1],x->chave[j]); }

    strcpy(x->chave[i],y->chave[T]);

    x->num = x->num + 1;

    fseek(arqb,x->pos,SEEK_SET);
    fwrite(x,sizeof(Nod),1,arqb);

    fseek(arqb,y->pos,SEEK_SET);
    fwrite(y,sizeof(Nod),1,arqb);

    fseek(arqb,z->pos,SEEK_SET);
    fwrite(z,sizeof(Nod),1,arqb);

    //free(z);
    //free(y);
}

void b_ins(Nod *x, char *val) { //B-TREE-INSERT-NONFULL //insert a key in nonfull node
    unsigned int i=0;
    Nod *C = NULL;

    i = x->num;

    if (x->folha == 1) {
        while ( (i >= 1) && (strcmp(val,x->chave[i]) < 0) ) {
            strcpy(x->chave[(i+1)],x->chave[i]);
            i--;
        }
        strcpy(x->chave[(i+1)],val);
        x->num = x->num + 1;

        fseek(arqb,x->pos,SEEK_SET);
        fwrite(x,sizeof(Nod),1,arqb);

    }

    else {
        while ( (i >= 1) && (strcmp(val,x->chave[i]) < 0) ) {i--;}
        i++;

        C = (Nod*)realloc(C,sizeof(Nod));

        fseek(arqb,x->c[i],SEEK_SET);
        fread(C,sizeof(Nod),1,arqb);

        if (C->num == Max) {
            b_split(x,i,C);

            if ( strcmp(val,x->chave[i]) > 0 ) {i++;}

        }
        fseek(arqb,x->c[i],SEEK_SET);
        fread(C,sizeof(Nod),1,arqb);

        b_ins(C,val);

        //free(C);
    }

}

void insere_b(char *val) { //B-TREE-INSERT //i believe the problem is here!
    Nod *S = NULL,*R = NULL;

    R = (Nod*)realloc(R,sizeof(Nod));
    R = raiz;

    if (R->num == Max) {
        S = (Nod*)realloc(S,sizeof(Nod));

/*      fseek(arqb,0,SEEK_END);
        S->pos = ftell(arqb);
*/
        raiz = S;

        S->folha = 0;
        S->num = 0;
        S->c[1] = R->pos;

/*      fseek(arqb,S->pos,SEEK_SET);
        fwrite(S,sizeof(Nod),1,arqb);

*/
        b_split(S,1,R);
        b_ins(S,val);

        //free(S);
    }

    else {b_ins(R,val);}

    //free(R);
}

void busca_b(Nod *x, char *val) { //B-TREE-SEARCH //self explanatory
    unsigned int i=1;
    Nod *C = NULL;

    while( (i <= x->num) && ( strcmp(val, x->chave[i]) > 0 ) ) {i++;}

    if ( (i <= x->num) && ( strcmp(val, x->chave[i]) == 0 ) ) {printf ("\nValor encontrado!\n");}

    else {
        if (x->folha == 1) {printf ("\nValor NAO encontrado!\n");}

        else {
            C = (Nod*)realloc(C,sizeof(Nod));
            fseek(arqb,x->c[i],SEEK_SET);
            fread(C,sizeof(Nod),1,arqb);

            lt++;

            busca_b(C,val);
            //free(C);
        }

    }

}

void cria_b() { // cria arvore B //create the B-tree
    long int i = 0;
    char V[11];

    raiz->folha = 1;
    raiz->num = 0;
    raiz->pos = 0;
    for (i=1;i<=(Max+1);i++) {raiz->c[i] = -1;}

    fseek(arqb,raiz->pos,SEEK_SET);
    fwrite(raiz,sizeof(Nod),1,arqb);

    rewind(arqt);
    for (i=0;i<fSize(arqt);i++) {
        fscanf(arqt,"%s\n",V);
        insere_b(V);
    }
}

void insere_l(char *val) { //insert in text file
    fpos_t pos;

    fgetpos(arqt,&pos);
    fseek(arqt,0,SEEK_END);

    fprintf(arqt,"%s\n",val);

    fsetpos(arqt,&pos);

    printf ("\nInsercao teve sucesso!\n");
    system(PAUSA);
}

void busca_l(char *val) { //search in text file
    fpos_t pos;
    char tmp[11];
    long int leitura = 0;
    short int suces = 0;

    fgetpos(arqt,&pos);
    rewind(arqt);


    while (feof(arqt) == 0){
        fscanf(arqt,"%s\n",tmp);

        leitura++;

        if (strcmp(val,tmp) == 0) {
            printf ("\nValor encontrado!\n");
            suces = 1;
            break;
        }

    }
    if (suces == 0) {printf ("\nValor NAO encontrado!\n");}
    fsetpos(arqt,&pos);

    printf ("\nNumero de leituras no disco: %ld\n",leitura);

    system(PAUSA);

}

void busca(short int op) { //just call the search of B-tree or Text!
    if (op == 1) {busca_l(VAL);}
    else {
        lt = 0;
        busca_b(raiz, VAL);
        printf ("\nNumero de leituras no disco: %ld\n",lt);
        system(PAUSA);
    }
}

void insere(short int op) { //just call the insert of B-tree or Text!
    if (op == 1) {insere_l(VAL);}
    else {
        insere_b(VAL);
        printf ("\nInsercao teve sucesso!\n");
        system(PAUSA);
    }
}

void maiuscula (char *S, short int i) { //upper case function
    short int j=0;

    for (j=0;j<i;j++){
        S[j] = toupper(S[j]);
    }
}
