// Aluno: Gabriel Pádua Almonfrey
// Turma: CC6N

#include <stdio.h>
#include <stdlib.h>

// Define a ordem (grau) mínimo da árvore B
// Determina o número mínimo e máximo de chaves que um nó pode conter
#define ORDEM 3 

// Estrutura do Nó da Árvore B
// Representa um único nó na estrutura de dados da árvore B
typedef struct NoB {
    int numChaves;         // Número atual de chaves no nó
    int chaves[2 * ORDEM - 1]; // Array para armazenar chaves (máximo é 2t-1)
    struct NoB* filhos[2 * ORDEM]; // Ponteiros para nós filhos (máximo é 2t)
    int folha;             // Indicador booleano: 1 se for nó folha, 0 se for nó interno
} NoB;

// Função para criar um novo nó da Árvore B
// Inicializa um nó sem chaves e define se é folha ou nó interno
NoB* criarNo(int folha) {
    // Aloca memória para o novo nó
    NoB* novoNo = (NoB*)malloc(sizeof(NoB));
    
    novoNo->folha = folha;  // Define se é um nó folha
    novoNo->numChaves = 0;  // Inicializa com zero chaves

    // Inicializa todos os ponteiros de filhos como NULL
    for (int i = 0; i < 2 * ORDEM; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Função para dividir um nó filho que está cheio
// Essencial para manter a propriedade de balanceamento da Árvore B
void dividirFilho(NoB* pai, int i, NoB* cheio) {
    // Cria um novo nó com o mesmo tipo (folha ou interno) do nó cheio
    NoB* novoNo = criarNo(cheio->folha);
    novoNo->numChaves = ORDEM - 1;

    // Copia as chaves maiores para o novo nó
    for (int j = 0; j < ORDEM - 1; j++)
        novoNo->chaves[j] = cheio->chaves[j + ORDEM];

    // Se não for um nó folha, também copia os ponteiros dos filhos
    if (!cheio->folha) {
        for (int j = 0; j < ORDEM; j++)
            novoNo->filhos[j] = cheio->filhos[j + ORDEM];
    }

    // Reduz o número de chaves do nó original
    cheio->numChaves = ORDEM - 1;

    // Ajusta os ponteiros dos filhos do nó pai
    for (int j = pai->numChaves; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];

    // Insere o novo nó como filho do nó pai
    pai->filhos[i + 1] = novoNo;

    // Desloca as chaves do nó pai para fazer espaço para a nova chave
    for (int j = pai->numChaves - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];

    // Move a chave do meio para o nó pai
    pai->chaves[i] = cheio->chaves[ORDEM - 1];
    pai->numChaves++;
}

// Função para inserir uma chave em um nó que não está cheio
void inserirNaoCheio(NoB* no, int chave) {
    int i = no->numChaves - 1;

    // Se for um nó folha, insere a chave na posição correta
    if (no->folha) {
        // Move as chaves maiores para abrir espaço para a nova chave
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        // Se for um nó interno, encontra o filho apropriado para inserção
        while (i >= 0 && no->chaves[i] > chave)
            i--;

        // Verifica se o filho está cheio e precisa ser dividido
        if (no->filhos[i + 1]->numChaves == 2 * ORDEM - 1) {
            dividirFilho(no, i + 1, no->filhos[i + 1]);

            // Ajusta o índice se necessário após a divisão
            if (no->chaves[i + 1] < chave)
                i++;
        }
        // Insere recursivamente no filho apropriado
        inserirNaoCheio(no->filhos[i + 1], chave);
    }
}

// Função principal para inserir uma chave na Árvore B
NoB* inserir(NoB* raiz, int chave) {
    // Se a árvore estiver vazia, cria um novo nó raiz
    if (raiz == NULL) {
        raiz = criarNo(1);
        raiz->chaves[0] = chave;
        raiz->numChaves = 1;
    } else {
        // Se a raiz estiver cheia, precisa dividir
        if (raiz->numChaves == 2 * ORDEM - 1) {
            NoB* novaRaiz = criarNo(0);
            novaRaiz->filhos[0] = raiz;

            // Divide a raiz atual
            dividirFilho(novaRaiz, 0, raiz);

            // Decide em qual filho inserir a nova chave
            int i = 0;
            if (novaRaiz->chaves[0] < chave)
                i++;
            inserirNaoCheio(novaRaiz->filhos[i], chave);

            raiz = novaRaiz;
        } else {
            // Insere normalmente se a raiz não estiver cheia
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

        int chaves[] = {42, 15, 73, 8, 25, 61, 99, 33};
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
