#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo; // informação dentro dos no
    struct no *esq, *dir; //os ponteiros apontarão para um estrutura no
} No;

typedef struct {
    No *raiz;
} Arvore;

No* criarNo(int valor) {
    No *novo = (No*)malloc(sizeof(No)); //aloca memoria dinamicamente
    if (novo == NULL) { // valida se a alocação foi bem sucedida
        printf("Erro ao alocar memória\n");
        exit(1); // encerra o programa em caso de erro
    }
    novo->conteudo = valor; // no novo nó, o conteudo recebe o valor passado
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void addEsq(No *no, int valor) {
    if (no->esq == NULL) { // verifica se o no a esquerda é null, se for, vai adicionar lá
        no->esq = criarNo(valor);
    } else {
        if (valor < no->esq->conteudo) {
            addEsq(no->esq, valor);
        } else {
            addDir(no->esq, valor);
        }
    }
}

void addDir(No *no, int valor) {
    if (no->dir == NULL) {
        no->dir = criarNo(valor); // no novo nó, o conteudo recebe o valor passado
    } else {
        if (valor > no->dir->conteudo) {
            addDir(no->dir, valor);
        } else {
            addEsq(no->dir, valor);
        }
    }
}

void add(Arvore *arv, int valor) {
    if (arv->raiz == NULL) { // valida se a árvore existe
        arv->raiz = criarNo(valor); // agora, esse no que acabamos de criar, será a raiz da arvore, uma vez que a raiz era null (estamos dentro do if)
    } else { // entramos no else caso a raiz seja diferente de NULL, ou seja, se já existe
        if (valor < arv->raiz->conteudo) { // verifica se o valor é menor que a arvore, se for, adiciona na esquerda
            addEsq(arv->raiz, valor);
        } else { // se for maior, adiciona à direita
            addDir(arv->raiz, valor);
        }
    }
}

void imprimir(No *raiz) {
    if (raiz != NULL) { // no momento que a raiz for nula, irá parar de printar
        imprimir(raiz->esq);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->dir);
    }
}

void liberarArvore(No *raiz) {
    if (raiz != NULL) { // percorre a árvore para liberar a memória
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->conteudo); // visita o nó raiz
        preOrdem(raiz->esq); // percorre a subárvore esquerda
        preOrdem(raiz->dir); // percorre a subárvore direita
    }
}

void posOrdem(No *raiz) {
    if (raiz != NULL) { 
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->conteudo);
    }
}

void emOrdem(No *raiz) {
    if (raiz != NULL) { 
        emOrdem(raiz->esq);
        printf("%d ", raiz->conteudo);
        emOrdem(raiz->dir);
    }
}

int main() {
    int op, valor;
    Arvore arv; // objeto arv do tipo Arvore, criamos na linha 8 o tipo Arvore
    arv.raiz = NULL; // estou manipulando o proprio objeto arv denominado na linha de cima
    
     do {
        printf("\n0- Sair\n1- Inserir\n2- Imprimir In-Order\n3- Imprimir Pre-Order\n4- Imprimir Post-Order\n");
        scanf("%d", &op);
        switch(op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("Digite um valor: ");
                scanf("%d", &valor);
                add(&arv, valor);
                break;
            case 2:
                printf("\nImpressão em Ordem (In-Order):\n");
                emOrdem(arv.raiz);
                break;
            case 3:
                printf("\nImpressão em Pré-Ordem:\n");
                preOrdem(arv.raiz);
                break;
            case 4:
                printf("\nImpressão em Pós-Ordem:\n");
                posOrdem(arv.raiz);
                break;
            default:
                printf("\nOpção inválida\n");
        }
    } while(op != 0);

    liberarArvore(arv.raiz); // libera a memoria
    return 0;
}
