// Árvore red-black 
// Aluno: Gabriel Pàdua

#include <stdio.h>
#include <stdlib.h>

// Definição das cores dos nós
#define VERMELHO 0
#define PRETO 1

// Estrutura para representar cada nó da árvore Red-Black
struct NoRB {
    int valor;            // Valor armazenado no nó
    int cor;              // VERMELHO (0) ou PRETO (1)
    struct NoRB *esquerda, *direita, *pai;  // Ponteiros para os filhos e pai
};

typedef struct NoRB NoRB;

// Função para criar um novo nó
NoRB* criarNo(int valor) {
    NoRB* novoNo = (NoRB*)malloc(sizeof(NoRB));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;  // Todo novo nó é inicialmente vermelho
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

// Função para fazer a rotação à esquerda
void rotacaoEsquerda(NoRB** raiz, NoRB* x) {
    NoRB* y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != NULL)
        y->esquerda->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x;
    x->pai = y;
}

// Função para fazer a rotação à direita
void rotacaoDireita(NoRB** raiz, NoRB* x) {
    NoRB* y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != NULL)
        y->direita->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->direita)
        x->pai->direita = y;
    else
        x->pai->esquerda = y;
    y->direita = x;
    x->pai = y;
}

// Função para corrigir violações das propriedades Red-Black após a inserção
void corrigirViolacao(NoRB** raiz, NoRB* z) {
    while (z != *raiz && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esquerda) {  // Pai de 'z' é filho esquerdo
            NoRB* y = z->pai->pai->direita;  // 'y' é tio de 'z'
            if (y != NULL && y->cor == VERMELHO) {  // Caso 1: Tio vermelho
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;  // Sobe para o avô
            } else {  // Caso 2 e 3: Tio preto
                if (z == z->pai->direita) {  // Caso 2: 'z' é filho direito
                    z = z->pai;
                    rotacaoEsquerda(raiz, z);
                }
                // Caso 3: 'z' é filho esquerdo
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, z->pai->pai);
            }
        } else {  // Simétrico: o pai de 'z' é filho direito
            NoRB* y = z->pai->pai->esquerda;  // 'y' é tio de 'z'
            if (y != NULL && y->cor == VERMELHO) {  // Caso 1: Tio vermelho
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;  // Sobe para o avô
            } else {  // Caso 2 e 3: Tio preto
                if (z == z->pai->esquerda) {  // Caso 2: 'z' é filho esquerdo
                    z = z->pai;
                    rotacaoDireita(raiz, z);
                }
                // Caso 3: 'z' é filho direito
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;  // Garante que a raiz é preta após as rotações
}

// Função para inserir um novo nó na árvore Red-Black
void inserir(NoRB** raiz, int valor) {
    NoRB* z = criarNo(valor);
    NoRB* y = NULL;
    NoRB* x = *raiz;

    // Busca a posição correta para inserir o novo nó
    while (x != NULL) {
        y = x;
        if (z->valor < x->valor)
            x = x->esquerda;
        else
            x = x->direita;
    }
    z->pai = y;
    if (y == NULL)  // A árvore está vazia, 'z' é a nova raiz
        *raiz = z;
    else if (z->valor < y->valor)
        y->esquerda = z;
    else
        y->direita = z;

    corrigirViolacao(raiz, z);
    (*raiz)->cor = PRETO;  // Garante que a raiz é sempre preta após a inserção
}

// Função para imprimir a árvore Red-Black em ordem (in-order)
void imprimirEmOrdem(NoRB* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d (%s) ", raiz->valor, (raiz->cor == VERMELHO) ? "VERMELHO" : "PRETO");
        imprimirEmOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore Red-Black de forma visual
void imprimirArvoreVisual(NoRB* raiz, int espacos) {
    if (raiz != NULL) {
        imprimirArvoreVisual(raiz->direita, espacos + 5);

        for (int i = 0; i < espacos; i++)
            printf(" ");
        printf("%d (%s)\n", raiz->valor, (raiz->cor == VERMELHO) ? "VERMELHO" : "PRETO");

        imprimirArvoreVisual(raiz->esquerda, espacos + 5);
    }
}

// Função principal
int main() {
    NoRB* raiz = NULL;
    int vetor[] = {12, 31, 20, 17, 11, 8, 3, 24, 15, 33};  // Exemplo de valores a serem inseridos
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    // Inserção dos elementos na árvore Red-Black
    for (int i = 0; i < tamanho; i++)
        inserir(&raiz, vetor[i]);

    // Impressão em ordem
    printf("Árvore Red-Black em ordem:\n");
    imprimirEmOrdem(raiz);
    printf("\n\n");

    // Impressão visual
    printf("Árvore Red-Black visual:\n");
    imprimirArvoreVisual(raiz, 0);

    return 0;
}
