#include "b-tree_file.h"
#include <stdarg.h>

long int lt = 0;
FILE *arqt, *arqb;
char VAL[11];
Nod *raiz = NULL; //raiz in portuguese = root in english!

static void err_exit(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

int main(void)
{
    int op = 0, ch = 1;

    //T must be at least 2...requirement of B-tree algorithm
    if (T < 2)
        err_exit("ERRO interno: grau minimo menor que 2... o programa terminara!\n");

    arqt = fopen("arq_5.txt", "r+");
    if (arqt == NULL)
        err_exit("ERRO interno: houve um problema ao abrir o arquivo 'arq_5.txt'... o programa terminara!\n");

    printf("Este programa permite incluir/buscar por strings de 10 caracteres usando\nduas estruturas: busca/insercao linear [1] ou via Arvore B [2].\nDigite sua escolha: ");
    if (scanf("%d", &op) != 1)
        err_exit("Failed to read an integer\n");

    if (op != 1 && op != 2)
        err_exit("Opcao invalida! Programa sera encerrado...\n");
    else if (op == 2)
    {
        arqb = fopen("arq_5_b.dat", "wb+");
        if (arqb == NULL)
            err_exit("ERRO interno: houve um problema ao abrir o arquivo 'arq_5.txt'... o programa terminara!\n");
        printf("\n\nCriando Arvore B a partir de 'arq_5.txt'. O resultado sera o arquivo 'arq_5_b.dat'...\n");
        raiz = (Nod*)malloc(sizeof(Nod)); //alloc root
        if (raiz == 0)
            err_exit("Memory allocation failed (%s():%d)\n", __func__, __LINE__);
        cria_b(); //create the B-tree
    }

    while (ch == 1 || ch == 2)
    {
        //system(CLRSCR);
        printf("\nPara busca, digite 1; para inserir um registro, digite 2\n(caso digite outro valor que nao 1 ou 2, o programa terminara): ");
        if (scanf("%d", &ch) != 1)
            err_exit("Failed to read an integer\n");

        if (ch == 1)
        {
            printf("\n\nBUSCA -> Entre com uma string de exatamente 10 caracteres para efetuar a busca: ");
            scanf("%s", VAL);
            maiuscula(VAL, 11);
            busca(op);
        }
        else if (ch == 2)
        {
            printf("\n\nINSERCAO -> Entre com uma string de exatamente 10 caracteres para que esta seja inserida no arquivo: ");
            scanf("%s", VAL);
            maiuscula(VAL, 11);
            insere(op);
        }
        else
            err_exit("Invalid input %d - exiting\n", ch);
    }

    fclose(arqt);
    fclose(arqb);
    if (op == 2)
        free(raiz);

    //system(PAUSA);
    return 0;
}

//Count number of lines in text file...
long int fSize(FILE *arq)
{
    fpos_t Pos;
    long tam=0;
    int c;

    fgetpos(arq, &Pos);
    rewind(arq);

    while ((c = fgetc(arq)) != EOF)
    {
        if (c == '\n')
            tam++;
    }

    fseek(arq, (-1), SEEK_END);
    if (fgetc(arq) != '\n')
        tam++;

    fsetpos(arq, &Pos);
    return tam;
}

//B-TREE-SPLIT-CHILD //that function split a B-tree node
void b_split(Nod *x, unsigned int i, Nod *y)
{
    Nod *z = NULL;
    unsigned int j=1;

    z = (Nod*)realloc(z, sizeof(Nod));
    if (z == 0)
        err_exit("Memory allocation failed (%s():%d)\n", __func__, __LINE__);

    fseek(arqb, 0, SEEK_END);
    z->pos = ftell(arqb);

    z->folha = y->folha;
    z->num = Min;

    for (j=1; j<=Min; j++)
    {
        strcpy(z->chave[j], y->chave[j+T]);
    }

    if (y->folha == 0)
    {
        for (j=1; j<=T; j++)
        {
            z->c[j] = y->c[j+T];
        }
    }

    y->num = Min;

    for (j=(x->num + 1); j<=(i+1); j--)
    {
        x->c[(j+1)] = x->c[j];
    }

    x->c[(i+1)] = z->pos;

    for (j=x->num; j<=i; j--)
    {
        strcpy(x->chave[j+1], x->chave[j]);
    }

    strcpy(x->chave[i], y->chave[T]);

    x->num = x->num + 1;

    fseek(arqb, x->pos, SEEK_SET);
    fwrite(x, sizeof(Nod), 1, arqb);

    fseek(arqb, y->pos, SEEK_SET);
    fwrite(y, sizeof(Nod), 1, arqb);

    fseek(arqb, z->pos, SEEK_SET);
    fwrite(z, sizeof(Nod), 1, arqb);
    fflush(arqb);

    //free(z);
    //free(y);
}

//B-TREE-INSERT-NONFULL //insert a key in nonfull node
void b_ins(Nod *x, char *val)
{
    unsigned int i=0;
    Nod *C = NULL;

    i = x->num;

    if (x->folha == 1)
    {
        while ( (i >= 1) && (strcmp(val, x->chave[i]) < 0) )
        {
            strcpy(x->chave[(i+1)], x->chave[i]);
            i--;
        }
        strcpy(x->chave[(i+1)], val);
        x->num = x->num + 1;

        fseek(arqb, x->pos, SEEK_SET);
        fwrite(x, sizeof(Nod), 1, arqb);
        fflush(arqb);
    }
    else
    {
        while ( (i >= 1) && (strcmp(val, x->chave[i]) < 0) )
            i--;
        i++;

        C = (Nod*)realloc(C, sizeof(Nod));
        if (C == 0)
            err_exit("Memory allocation failed (%s():%d)\n", __func__, __LINE__);

        fseek(arqb, x->c[i], SEEK_SET);
        fread(C, sizeof(Nod), 1, arqb);

        if (C->num == Max)
        {
            b_split(x, i, C);

            if ( strcmp(val, x->chave[i]) > 0 )
            {
                i++;
            }
        }
        fseek(arqb, x->c[i], SEEK_SET);
        fread(C, sizeof(Nod), 1, arqb);

        b_ins(C, val);

        //free(C);
    }
}

//B-TREE-INSERT //i believe the problem is here!
void insere_b(char *val)
{
    //Nod *R = NULL;
    //R = (Nod*)realloc(R, sizeof(Nod));
    Nod *R = raiz;

    if (R->num == Max)
    {
        /* Need to split the node -- ??? */
        Nod *S = (Nod*)realloc(S, sizeof(Nod));
        if (S == 0)
            err_exit("Memory allocation failed (%s():%d)\n", __func__, __LINE__);
        raiz = S;
        S->folha = 0;
        S->num = 0;
        S->c[1] = R->pos;
        b_split(S, 1, R);
        b_ins(S, val);
    }
    else
    {
        b_ins(R, val);
    }

    //free(R);
}

//B-TREE-SEARCH //self explanatory
void busca_b(Nod *x, char *val)
{
    unsigned int i=1;
    Nod *C = NULL;

    while( (i <= x->num) && ( strcmp(val, x->chave[i]) > 0 ) )
    {
        i++;
    }

    if ( (i <= x->num) && ( strcmp(val, x->chave[i]) == 0 ) )
    {
        printf("\nValor encontrado!\n");
    }
    else if (x->folha == 1)
    {
        printf("\nValor NAO encontrado!\n");
    }
    else
    {
        C = (Nod*)realloc(C, sizeof(Nod));
        if (C == 0)
            err_exit("Memory allocation failed (%s():%d)\n", __func__, __LINE__);
        fseek(arqb, x->c[i], SEEK_SET);
        fread(C, sizeof(Nod), 1, arqb);
        lt++;
        busca_b(C, val);
        //free(C);
    }
}

// cria arvore B //create the B-tree
void cria_b(void)
{
    long int i = 0;
    char V[11];
    int lines = fSize(arqt);

    /* Initialize the root node */
    raiz->folha = 1;
    raiz->num = 0;
    raiz->pos = 0;
    for (i = 0; i < (Max+2); i++)
    {
        raiz->c[i] = -1;
    }
    memset(raiz->chave, '\0', sizeof(raiz->chave));

    fseek(arqb, raiz->pos, SEEK_SET);
    fwrite(raiz, sizeof(Nod), 1, arqb);
    fflush(arqb);

    rewind(arqt);
    for (i = 0; i < lines; i++)
    {
        fscanf(arqt, "%s\n", V);
printf("-->%s<--\n", V);
        insere_b(V);
    }
}

//insert in text file
void insere_l(char *val)
{
    fpos_t pos;

    fgetpos(arqt, &pos);
    fseek(arqt, 0, SEEK_END);

    fprintf(arqt, "%s\n", val);

    fsetpos(arqt, &pos);

    printf("\nInsercao teve sucesso!\n");
    //system(PAUSA);
}

//search in text file
void busca_l(char *val)
{
    fpos_t pos;
    char tmp[11];
    long int leitura = 0;
    short int suces = 0;

    fgetpos(arqt, &pos);
    rewind(arqt);

    while (feof(arqt) == 0)
    {
        fscanf(arqt, "%s\n", tmp);

        leitura++;

        if (strcmp(val, tmp) == 0)
        {
            printf("\nValor encontrado!\n");
            suces = 1;
            break;
        }
    }
    if (suces == 0)
    {
        printf("\nValor NAO encontrado!\n");
    }
    fsetpos(arqt, &pos);

    printf("\nNumero de leituras no disco: %ld\n", leitura);

    //system(PAUSA);
}

//just call the search of B-tree or Text!
void busca(short int op)
{
    if (op == 1)
    {
        busca_l(VAL);
    }
    else
    {
        lt = 0;
        busca_b(raiz, VAL);
        printf("\nNumero de leituras no disco: %ld\n", lt);
        //system(PAUSA);
    }
}

//just call the insert of B-tree or Text!
void insere(short int op)
{
    if (op == 1)
    {
        insere_l(VAL);
    }
    else
    {
        insere_b(VAL);
        printf("\nInsercao teve sucesso!\n");
        //system(PAUSA);
    }
}

//upper case function
void maiuscula(char *S, short i)
{
    short j;

    for (j = 0; j < i; j++)
        S[j] = toupper(S[j]);
}
