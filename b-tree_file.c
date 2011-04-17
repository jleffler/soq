#include "b-tree_file.h"

int main(int argc, char *argv[]) {
//vars

    int op = 0,ch = 1;
//

    if (T < 2) { //T must be at least 2...requirement of B-tree algorithm
        printf ("ERRO interno: grau minimo menor que 2... o programa terminara!\n");
        return 0;
    }

    arqt = fopen("arq_5.txt","r+");
    if (arqt == NULL) {
        printf ("ERRO interno: houve um problema ao abrir o arquivo 'arq_5.txt'... o programa terminara!\n");
        return 0;
    }

    printf("Este programa permite incluir/buscar por strings de 10 caracteres usando\nduas estruturas: busca/insercao linear [1] ou via Arvore B [2].\nDigite sua escolha: ");
    scanf ("%d",&op);

    if ( (op != 1) && (op != 2) ) {
        printf("Opcao invalida! Programa sera encerrado...\n");
        system(PAUSA);
        return 0;
    }

    else {
        if (op == 2) {

            arqb = fopen("arq_5_b.dat","wb+");
            if (arqb == NULL) {
                printf ("ERRO interno: houve um problema ao abrir o arquivo 'arq_5.txt'... o programa terminara!\n");
                return 0;
            }

                printf("\n\nCriando Arvore B a partir de 'arq_5.txt'. O resultado sera o arquivo 'arq_5_b.dat'...\n");
                raiz = (Nod*)malloc(sizeof(Nod)); //alloc root
                cria_b(); //create the B-tree

        }

    }

    while ( (ch == 1) || (ch == 2) ) {
        system(CLRSCR);

        printf ("\nPara busca, digite 1; para inserir um registro, digite 2\n(caso digite outro valor que nao 1 ou 2, o programa terminara): ");
        scanf("%d",&ch);

        if (ch == 1) {
            printf ("\n\nBUSCA -> Entre com uma string de exatamente 10 caracteres para efetuar a busca: ");

            scanf("%s",VAL);
            maiuscula(VAL,11);

            busca(op);
        }

        else {
            if (ch == 2) {
                printf ("\n\nINSERCAO -> Entre com uma string de exatamente 10 caracteres para que esta seja inserida no arquivo: ");
                scanf("%s",VAL);
                maiuscula(VAL,11);

                insere(op);
            }

        }
    }

    fclose (arqt);
    if (op == 2) {fclose(arqb);free(raiz);}

    system(PAUSA);
	return 0;
}


