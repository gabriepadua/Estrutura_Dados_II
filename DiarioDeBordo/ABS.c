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

typedef struct Pilha {
    No* no; // aponta para um nó da árvore
    struct Pilha* prox; // próximo elemento da pilha
} Pilha;

// Função para empilhar um nó na pilha
void empilhar(Pilha** topo, No* no) {
    Pilha* novo = (Pilha*)malloc(sizeof(Pilha)); // aloca memória para um novo elemento da pilha
    if (novo == NULL) { // verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1); // encerra o programa em caso de erro
    }
    novo->no = no; // o nó atual é armazenado no novo elemento da pilha
    novo->prox = *topo; // o próximo elemento da pilha será o atual topo
    *topo = novo; // o novo elemento se torna o topo da pilha
}

// Função para desempilhar um nó da pilha
No* desempilhar(Pilha** topo) {
    if (*topo == NULL) { // se a pilha estiver vazia, retorna NULL
        return NULL;
    }
    Pilha* temp = *topo; // armazena o elemento do topo para liberar a memória depois
    No* no = temp->no; // obtém o nó armazenado no topo
    *topo = (*topo)->prox; // o topo da pilha agora aponta para o próximo elemento
    free(temp); // libera a memória do antigo topo
    return no; // retorna o nó desempilhado
}

// Função para verificar se a pilha está vazia
int pilhaVazia(Pilha* topo) {
    return topo == NULL; // retorna 1 se a pilha estiver vazia, 0 caso contrário
}

// Percurso Pré-Ordem Iterativo
void preOrdemIterativa(No* raiz) {
    if (raiz == NULL) return; // se a árvore estiver vazia, não faz nada

    Pilha* pilha = NULL; // inicializa a pilha como vazia
    empilhar(&pilha, raiz); // empilha a raiz

    while (!pilhaVazia(pilha)) { // enquanto a pilha não estiver vazia
        No* no = desempilhar(&pilha); // desempilha o próximo nó
        printf("%d ", no->conteudo); // imprime o conteúdo do nó

        // Empilha o nó direito primeiro para garantir que o nó esquerdo seja processado primeiro
        if (no->dir != NULL) {
            empilhar(&pilha, no->dir);
        }
        if (no->esq != NULL) {
            empilhar(&pilha, no->esq);
        }
    }
    
    void emOrdemIterativa(No* raiz) {
    Pilha* pilha = NULL; // inicializa a pilha como vazia
    No* atual = raiz; // começa pela raiz da árvore

    while (atual != NULL || !pilhaVazia(pilha)) { // enquanto houver nós para processar
        while (atual != NULL) { // percorre até o nó mais à esquerda
            empilhar(&pilha, atual); // empilha todos os nós à esquerda
            atual = atual->esq;
        }
        atual = desempilhar(&pilha); // desempilha o nó mais à esquerda
        printf("%d ", atual->conteudo); // imprime o conteúdo do nó
        atual = atual->dir; // muda para a subárvore direita
    }
}

void posOrdemIterativa(No* raiz) {
    if (raiz == NULL) return; // se a árvore estiver vazia, não faz nada

    Pilha* pilha1 = NULL; // primeira pilha para armazenar a ordem dos nós
    Pilha* pilha2 = NULL; // segunda pilha para armazenar os nós em ordem pós-ordem

    empilhar(&pilha1, raiz); // empilha a raiz na primeira pilha
    while (!pilhaVazia(pilha1)) { // enquanto a primeira pilha não estiver vazia
        No* no = desempilhar(&pilha1); // desempilha o próximo nó
        empilhar(&pilha2, no); // empilha o nó na segunda pilha

        // Empilha os filhos do nó na primeira pilha
        if (no->esq != NULL) {
            empilhar(&pilha1, no->esq);
        }
        if (no->dir != NULL) {
            empilhar(&pilha1, no->dir);
        }
    }

    // A segunda pilha agora contém os nós em ordem pós-ordem
    while (!pilhaVazia(pilha2)) {
        No* no = desempilhar(&pilha2); // desempilha e imprime os nós
        printf("%d ", no->conteudo);
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
                emOrdemIterativa(arv.raiz);
                break;
            case 3:
                printf("\nImpressão em Pré-Ordem:\n");
                preOrdemIterativa(arv.raiz);
                break;
            case 4:
                printf("\nImpressão em Pós-Ordem:\n");
                posOrdemIterativa(arv.raiz);
                break;
            default:
                printf("\nOpção inválida\n");
        }
    } while(op != 0);

    liberarArvore(arv.raiz); // libera a memória
    return 0;
}
