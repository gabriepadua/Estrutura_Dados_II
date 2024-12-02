// Aluno: Gabriel Pádua Almonfrey
// Turma: CC6N

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura básica de um nó na Treap - mistura de árvore binária de busca e heap
typedef struct NoTreap
{
    int chave;           // Valor que mantém a propriedade de árvore de busca
    int prioridade;      // Valor aleatório para manter a propriedade de heap
    struct NoTreap *esq; // Ponteiro para subárvore esquerda
    struct NoTreap *dir; // Ponteiro para subárvore direita
} NoTreap;

// Função para criar um novo nó - basicamente um "construtor" manual
NoTreap *criarNoTreap(int chave)
{
    // Aloca memória para o novo nó e inicializa suas propriedades
    NoTreap *novoNo = (NoTreap *)malloc(sizeof(NoTreap));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100; // Prioridade aleatória para "randomizar" a estrutura
    novoNo->esq = novoNo->dir = NULL;
    return novoNo;
}

// Rotação à direita - uma operação essencial para manter o balanceamento
NoTreap *rotacaoDireita(NoTreap *y)
{
    // Procedimento clássico de rotação em árvores binárias
    NoTreap *x = y->esq;
    NoTreap *T2 = x->dir;

    // Realiza a rotação
    x->dir = y;
    y->esq = T2;

    return x;
}

// Rotação à esquerda - simétrica à rotação à direita
NoTreap *rotacaoEsquerda(NoTreap *x)
{
    // Similar à rotação à direita, mas invertendo os ponteiros
    NoTreap *y = x->dir;
    NoTreap *T2 = y->esq;

    // Realiza a rotação
    y->esq = x;
    x->dir = T2;

    return y;
}

// Inserção na Treap - o coração da estrutura de dados
NoTreap *inserir(NoTreap *raiz, int chave)
{
    // Primeiro, inserção como em uma árvore de busca normal
    if (!raiz)
        return criarNoTreap(chave);

    if (chave < raiz->chave)
    {
        raiz->esq = inserir(raiz->esq, chave);

        // Depois, verifica a propriedade de heap - a parte "mágica" da Treap
        if (raiz->esq->prioridade > raiz->prioridade)
        {
            raiz = rotacaoDireita(raiz);
        }
    }
    else
    {
        raiz->dir = inserir(raiz->dir, chave);

        // Mesma lógica de verificação de heap para o lado direito
        if (raiz->dir->prioridade > raiz->prioridade)
        {
            raiz = rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

// Busca tradicional em árvore binária
NoTreap *buscar(NoTreap *raiz, int chave)
{
    // Recursão padrão de busca em árvore binária de busca
    if (!raiz || raiz->chave == chave)
    {
        return raiz;
    }

    if (chave < raiz->chave)
    {
        return buscar(raiz->esq, chave);
    }
    else
    {
        return buscar(raiz->dir, chave);
    }
}

// Remoção - a operação mais complexa em uma Treap
NoTreap *deletar(NoTreap *raiz, int chave)
{
    // Se a árvore estiver vazia, não há nada para remover
    if (!raiz)
        return raiz;

    // Navega para encontrar o nó a ser removido
    if (chave < raiz->chave)
    {
        raiz->esq = deletar(raiz->esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->dir = deletar(raiz->dir, chave);
    }
    else
    {
        // Nó encontrado - agora vem a parte interessante
        if (!raiz->esq)
        {
            // Nó com filho apenas à direita
            NoTreap *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (!raiz->dir)
        {
            // Nó com filho apenas à esquerda
            NoTreap *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos - usa prioridade para decidir rotação
        if (raiz->esq->prioridade < raiz->dir->prioridade)
        {
            raiz = rotacaoEsquerda(raiz);
            raiz->esq = deletar(raiz->esq, chave);
        }
        else
        {
            raiz = rotacaoDireita(raiz);
            raiz->dir = deletar(raiz->dir, chave);
        }
    }

    return raiz;
}

// Percorre a árvore em ordem simétrica - um clássico de árvores binárias
void percorrerInOrdem(NoTreap *raiz)
{
    if (raiz)
    {
        // Primeiro esquerda, depois raiz, depois direita
        percorrerInOrdem(raiz->esq);
        printf("Chave: %d | Prioridade: %d\n", raiz->chave, raiz->prioridade);
        percorrerInOrdem(raiz->dir);
    }
}

// Função principal para demonstrar as operações da Treap
int main()
{
    // Inicializa a semente para geração de números aleatórios
    srand(time(0));

    // Cria uma Treap vazia
    NoTreap *raiz = NULL;

    // Insere alguns valores para demonstração
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Percorrendo a Treap em ordem:\n");
    percorrerInOrdem(raiz);

    // Teste de busca na Treap
    int chave = 40;
    if (buscar(raiz, chave))
        printf("\nChave %d encontrada na Treap.\n", chave);
    else
        printf("\nChave %d não encontrada na Treap.\n", chave);

    // Teste de busca com chave não existente
    chave = 55;
    if (buscar(raiz, chave))
        printf("Chave %d encontrada na Treap.\n", chave);
    else
        printf("Chave %d não encontrada na Treap.\n", chave);

    // Demonstração de remoção
    printf("\nDeletando a chave 20\n");
    raiz = deletar(raiz, 20);
    printf("Percorrendo a Treap após deletar 20:\n");
    percorrerInOrdem(raiz);

    // Teste de busca após remoção
    chave = 20;
    if (buscar(raiz, chave))
        printf("\nChave %d encontrada na Treap.\n", chave);
    else
        printf("\nChave %d não encontrada na Treap.\n", chave);

    return 0;
}
