// Aluno: Gabriel Pádua Almonfrey
// Turma: CC6N

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da Treap
typedef struct NoTreap {
    int chave;       // Chave do nó
    int prioridade;  // Prioridade do nó
    struct NoTreap *esquerda, *direita; // Ponteiros para os filhos esquerdo e direito
} NoTreap;

// Função para criar um novo nó da Treap
NoTreap* criarNo(int chave) {
    // Aloca memória para um novo nó
    NoTreap* no = (NoTreap*)malloc(sizeof(NoTreap));
    no->chave = chave;              // Define a chave do nó
    no->prioridade = rand() % 100;  // Gera uma prioridade aleatória para o nó
    no->esquerda = no->direita = NULL; // Inicializa filhos como NULL, pois ainda não existem
    return no; // Retorna o ponteiro para o novo nó criado
}

// Função para realizar uma rotação à direita em relação ao nó `y`
NoTreap* rotacaoDireita(NoTreap* y) {
    NoTreap* x = y->esquerda; // `x` será o novo nó raiz após a rotação
    NoTreap* T2 = x->direita; // Armazena a subárvore à direita de `x`, que ficará como filho esquerdo de `y`

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Retorna o novo nó raiz (`x`) após a rotação
    return x;
}

// Função para realizar uma rotação à esquerda em relação ao nó `x`
NoTreap* rotacaoEsquerda(NoTreap* x) {
    NoTreap* y = x->direita; // `y` será o novo nó raiz após a rotação
    NoTreap* T2 = y->esquerda; // Armazena a subárvore à esquerda de `y`, que ficará como filho direito de `x`

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Retorna o novo nó raiz (`y`) após a rotação
    return y;
}

// Função de inserção na Treap
NoTreap* inserir(NoTreap* raiz, int chave) {
    // Caso base: se a árvore está vazia, cria um novo nó com a chave dada
    if (raiz == NULL)
        return criarNo(chave);

    // Inserção baseada na propriedade de árvore binária de busca
    if (chave < raiz->chave) { 
        // Se a chave a ser inserida é menor, insere na subárvore esquerda
        raiz->esquerda = inserir(raiz->esquerda, chave);

        // Após a inserção, verifica se a propriedade de heap está mantida
        if (raiz->esquerda->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz); // Rotaciona para a direita se a prioridade do filho esquerdo é maior
    }
    else if (chave > raiz->chave) {
        // Se a chave a ser inserida é maior, insere na subárvore direita
        raiz->direita = inserir(raiz->direita, chave);

        // Após a inserção, verifica a propriedade de heap novamente
        if (raiz->direita->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz); // Rotaciona para a esquerda se a prioridade do filho direito é maior
    }

    // Retorna a raiz após as possíveis rotações
    return raiz;
}

// Função de busca na Treap
NoTreap* buscar(NoTreap* raiz, int chave) {
    // Caso base: o nó atual é NULL (não encontrado) ou contém a chave procurada
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    // Realiza uma busca recursiva semelhante a uma árvore binária de busca
    if (chave < raiz->chave)
        return buscar(raiz->esquerda, chave); // Busca na subárvore esquerda se a chave for menor
    else
        return buscar(raiz->direita, chave); // Busca na subárvore direita se a chave for maior
}

// Função para percorrer a Treap em ordem (in-order traversal) e imprimir os nós
void emOrdem(NoTreap* raiz) {
    if (raiz) {
        emOrdem(raiz->esquerda); // Percorre a subárvore esquerda primeiro
        // Imprime a chave e prioridade do nó atual
        printf("Chave: %d | Prioridade: %d\n", raiz->chave, raiz->prioridade);
        emOrdem(raiz->direita); // Percorre a subárvore direita
    }
}

// Função principal
int main() {
    srand(time(0)); // Inicializa a semente para gerar números aleatórios para prioridade

    NoTreap* raiz = NULL;

    // Inserção de chaves na Treap
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    // Impressão da Treap usando percurso em ordem
    printf("Percorrendo a Treap em ordem:\n");
    emOrdem(raiz);

    // Teste de busca na Treap
    int chave = 40;
    if (buscar(raiz, chave))
        printf("\nChave %d encontrada na Treap.\n", chave);
    else
        printf("\nChave %d não encontrada na Treap.\n", chave);

    return 0;
}
