// Aluno: Gabriel Pádua Almonfrey
// Turma: CC6N

#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3 // Grau mínimo da árvore B (t)

// Estrutura do nó da árvore B
typedef struct NoB {
    int numChaves;         // Número de chaves atualmente no nó
    int chaves[2 * ORDEM - 1]; // Array de chaves
    struct NoB* filhos[2 * ORDEM]; // Ponteiros para os filhos
    int folha;             // Booleano para indicar se o nó é folha (1) ou não (0)
} NoB;

// Função para criar um novo nó
NoB* criarNo(int folha) {
    NoB* novoNo = (NoB*)malloc(sizeof(NoB));
    novoNo->folha = folha;  // Define se o nó é folha ou não
    novoNo->numChaves = 0;  // Inicializa com zero chaves
    for (int i = 0; i < 2 * ORDEM; i++) {
        novoNo->filhos[i] = NULL; // Inicializa todos os filhos como NULL
    }
    return novoNo;
}

// Função para dividir o filho `i` do nó `pai` quando ele está cheio
void dividirFilho(NoB* pai, int i, NoB* cheio) {
    NoB* novoNo = criarNo(cheio->folha); // Cria um novo nó para chaves maiores
    novoNo->numChaves = ORDEM - 1;

    for (int j = 0; j < ORDEM - 1; j++)
        novoNo->chaves[j] = cheio->chaves[j + ORDEM];

    if (!cheio->folha) {
        for (int j = 0; j < ORDEM; j++)
            novoNo->filhos[j] = cheio->filhos[j + ORDEM];
    }

    cheio->numChaves = ORDEM - 1;

    for (int j = pai->numChaves; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];

    pai->filhos[i + 1] = novoNo;

    for (int j = pai->numChaves - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];

    pai->chaves[i] = cheio->chaves[ORDEM - 1];
    pai->numChaves++;
}

// Função para inserir uma chave em um nó que não está cheio
void inserirNaoCheio(NoB* no, int chave) {
    int i = no->numChaves - 1;

    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && no->chaves[i] > chave)
            i--;

        if (no->filhos[i + 1]->numChaves == 2 * ORDEM - 1) {
            dividirFilho(no, i + 1, no->filhos[i + 1]);

            if (no->chaves[i + 1] < chave)
                i++;
        }
        inserirNaoCheio(no->filhos[i + 1], chave);
    }
}

// Função para inserir uma chave na árvore B
NoB* inserir(NoB* raiz, int chave) {
    if (raiz == NULL) {
        raiz = criarNo(1);
        raiz->chaves[0] = chave;
        raiz->numChaves = 1;
    } else {
        if (raiz->numChaves == 2 * ORDEM - 1) {
            NoB* novaRaiz = criarNo(0);
            novaRaiz->filhos[0] = raiz;

            dividirFilho(novaRaiz, 0, raiz);

            int i = 0;
            if (novaRaiz->chaves[0] < chave)
                i++;
            inserirNaoCheio(novaRaiz->filhos[i], chave);

            raiz = novaRaiz;
        } else {
            inserirNaoCheio(raiz, chave);
        }
    }
    return raiz;
}

// Percurso in-ordem (ordem crescente)
void percorrerInOrdem(NoB* no) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->numChaves; i++) {
            if (!no->folha)
                percorrerInOrdem(no->filhos[i]);
            printf("%d ", no->chaves[i]);
        }
        if (!no->folha)
            percorrerInOrdem(no->filhos[i]);
    }
}

// Percurso pré-ordem (raiz, esquerda, direita)
void percorrerPreOrdem(NoB* no) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->numChaves; i++) {
            printf("%d ", no->chaves[i]); // Imprime a chave na raiz primeiro
            if (!no->folha)
                percorrerPreOrdem(no->filhos[i]);
        }
        if (!no->folha)
            percorrerPreOrdem(no->filhos[i]);
    }
}

// Percurso pós-ordem (esquerda, direita, raiz)
void percorrerPosOrdem(NoB* no) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->numChaves; i++) {
            if (!no->folha)
                percorrerPosOrdem(no->filhos[i]);
        }
        if (!no->folha)
            percorrerPosOrdem(no->filhos[no->numChaves]);

        // Imprime todas as chaves do nó após visitar os filhos
        for (i = 0; i < no->numChaves; i++)
            printf("%d ", no->chaves[i]);
    }
}

// Função principal para testar a árvore B
int main() {
    NoB* raiz = NULL; // Inicializa a raiz da árvore como vazia

    int chaves[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, chaves[i]);

    printf("Percorrendo a árvore B em pré-ordem:\n");
    percorrerPreOrdem(raiz);
    printf("\n");

    printf("Percorrendo a árvore B em in-ordem:\n");
    percorrerInOrdem(raiz);
    printf("\n");

    printf("Percorrendo a árvore B em pós-ordem:\n");
    percorrerPosOrdem(raiz);
    printf("\n");

    return 0;
}
