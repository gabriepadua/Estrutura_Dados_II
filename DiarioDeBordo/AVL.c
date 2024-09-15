// Aluno: Gabriel Pàdua
// Turma: CC6N - Estrutura de Dados 2

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
struct NodoAVL {
    int chave;
    struct NodoAVL *esq;
    struct NodoAVL *dir;
    int nivel;
};


// Função auxiliar para encontrar o valor mínimo na árvore
struct NodoAVL *obterMinimo(struct NodoAVL *raiz) {
    struct NodoAVL *atual = raiz;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}
// Função auxiliar para encontrar o valor máximo na árvore
struct NodoAVL *obterMaximo(struct NodoAVL *raiz) {
    struct NodoAVL *atual = raiz;
    while (atual->dir != NULL) { // Navega até o nó mais à direita
        atual = atual->dir;
    }
    return atual; // Retorna o nó com o maior valor
}

// Função auxiliar para exibir a árvore em PRE-ORDER
void exibirPreOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        printf("%i ", raiz->chave); // Exibe o valor do nó atual
        exibirPreOrdem(raiz->esq); // Exibe a subárvore esquerda
        exibirPreOrdem(raiz->dir); // Exibe a subárvore direita
    }
}

// Função auxiliar para exibir a árvore em IN-ORDER
void exibirEmOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esq); // Exibe a subárvore esquerda
        printf("%i ", raiz->chave); // Exibe o valor do nó atual
        exibirEmOrdem(raiz->dir); // Exibe a subárvore direita
    }
}

// Função auxiliar para exibir a árvore em POS-ORDER
void exibirPosOrdem(struct NodoAVL *raiz) {
    if (raiz != NULL) {
        exibirPosOrdem(raiz->esq); // Exibe a subárvore esquerda
        exibirPosOrdem(raiz->dir); // Exibe a subárvore direita
        printf("%i ", raiz->chave); // Exibe o valor do nó atual
    }
}

// Função para validar a entrada do usuário
int validarEntrada() {
    int entradaValida, chave;
    while (1) {
        entradaValida = scanf("%i", &chave); // Lê a entrada do usuário
        if (entradaValida == 1) {
            if (chave < 0) { // Não permite valores negativos
                printf("\nValor inválido.\nTente novamente: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            } else {
                break; // Entrada válida
            }
        } else {
            printf("\nEntrada inválida.\nTente novamente: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
    return chave; // Retorna o valor válido
}

// Função para calcular o fator de balanceamento
int obterFatorBalanceamento(struct NodoAVL *nodo) {
    if (nodo == NULL) {
        return 0; // Fator de balanceamento para nó nulo é 0
    }
    int altEsq = nodo->esq ? nodo->esq->nivel : -1; // Altura da subárvore esquerda
    int altDir = nodo->dir ? nodo->dir->nivel : -1; // Altura da subárvore direita
    return altEsq - altDir; // Fator de balanceamento
}

// Função para atualizar o nível (altura) do nó
void atualizarNivel(struct NodoAVL *nodo) {
    int altEsq = nodo->esq ? nodo->esq->nivel : -1; // Altura da subárvore esquerda
    int altDir = nodo->dir ? nodo->dir->nivel : -1; // Altura da subárvore direita
    nodo->nivel = (altEsq > altDir ? altEsq : altDir) + 1; // Atualiza o nível do nó
}


// Função para criar um novo nodo
struct NodoAVL *criarNodo(int chave) {
    struct NodoAVL *novoNodo = (struct NodoAVL *)malloc(sizeof(struct NodoAVL));
    if (novoNodo == NULL) {
        // Erro ao alocar memória
        printf("Erro ao alocar memória para o Nodo\n");
        exit(-1);
    }
    novoNodo->chave = chave;
    novoNodo->esq = NULL;
    novoNodo->dir = NULL;
    novoNodo->nivel = 0; // Inicializa o nível do nodo
    return novoNodo; // Retorna o novo nodo criado
}

// Função para realizar a rotação à direita
struct NodoAVL *rotacionarDireita(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->esq;
    struct NodoAVL *subArvDir = novaRaiz->dir;

    // Realiza a rotação à direita
    novaRaiz->dir = nodo;
    nodo->esq = subArvDir;

    // Atualiza os níveis dos nos afetados
    atualizarNivel(nodo);
    atualizarNivel(novaRaiz);

    return novaRaiz; // Retorna a nova raiz da subárvore
}


// Função para realizar a rotação à esquerda
struct NodoAVL *rotacionarEsquerda(struct NodoAVL *nodo) {
    struct NodoAVL *novaRaiz = nodo->dir;
    struct NodoAVL *subArvEsq = novaRaiz->esq;

    // Realiza a rotação à esquerda
    novaRaiz->esq = nodo;
    nodo->dir = subArvEsq;

    // Atualiza os níveis (alturas) dos nodos afetados
    atualizarNivel(nodo);
    atualizarNivel(novaRaiz);

    return novaRaiz; // Retorna a nova raiz da subárvore
}

// Função para balancear a árvore AVL
struct NodoAVL *balancear(struct NodoAVL *raiz, int chave) {
    // Atualiza o nível (altura) do nó atual
    atualizarNivel(raiz);

    // Calcula o fator de balanceamento do nó atual
    int balanceamento = obterFatorBalanceamento(raiz);

    // Caso de desbalanceamento à esquerda-esquerda (LL)
    if (balanceamento > 1 && chave < raiz->esq->chave) {
        return rotacionarDireita(raiz);
    }

    // Caso de desbalanceamento à direita-direita (RR)
    if (balanceamento < -1 && chave > raiz->dir->chave) {
        return rotacionarEsquerda(raiz);
    }

    // Caso de desbalanceamento à esquerda-direita (LR)
    if (balanceamento > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacionarEsquerda(raiz->esq);
        return rotacionarDireita(raiz);
    }

    // Caso de desbalanceamento à direita-esquerda (RL)
    if (balanceamento < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacionarDireita(raiz->dir);
        return rotacionarEsquerda(raiz);
    }

    return raiz; // Retorna a raiz da árvore (ou subárvore) balanceada
}

// Função para inserir um nodo na árvore AVL
struct NodoAVL *inserir(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        // Se a raiz é NULL, cria um novo nodo
        return criarNodo(chave);
    }

    if (chave < raiz->chave) {
        // Insere na subárvore esquerda
        raiz->esq = inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        // Insere na subárvore direita
        raiz->dir = inserir(raiz->dir, chave);
    } else {
        // Se a chave já existe, não faz nada (não permite duplicatas)
        return raiz;
    }

    // Balanceia a árvore após a inserção
    return balancear(raiz, chave);
}

// Função para procurar um nodo na árvore AVL
void procurar(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        // Caso base: valor não encontrado na árvore
        printf("Valor %d não encontrado.\n", chave);
        return;
    }

    if (chave == raiz->chave) {
        // Valor encontrado
        printf("Valor %d encontrado!\n", chave);
    } else if (chave < raiz->chave) {
        // Busca na subárvore esquerda
        procurar(raiz->esq, chave);
    } else {
        // Busca na subárvore direita
        procurar(raiz->dir, chave);
    }
}


// Função para remover um Nodo da árvore AVL
struct NodoAVL *remover(struct NodoAVL *raiz, int chave) {
    if (raiz == NULL) {
        // Se o nodo não for encontrado, retorna a raiz original
        printf("Valor %d não encontrado.\n", chave);
        return raiz;
    }

    // Busca o nodo a ser removido na subárvore esquerda ou direita
    if (chave < raiz->chave) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        // Caso 1: Nodo com um filho ou sem filhos
        if (raiz->esq == NULL) {
            struct NodoAVL *temp = raiz->dir;
            free(raiz);
            printf("Valor %d removido.\n", chave);
            return temp;
        } else if (raiz->dir == NULL) {
            struct NodoAVL *temp = raiz->esq;
            free(raiz);
            printf("Valor %d removido.\n", chave);
            return temp;
        }

        // Caso 2: Nodo com dois filhos
        struct NodoAVL *temp = obterMinimo(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = remover(raiz->dir, temp->chave);
    }

    // Balanceia a árvore após a remoção
    return balancear(raiz, chave);
}

// Função para calcular a altura da árvore
int altura(struct NodoAVL *raiz) {
    // Se o nó for NULL, retorna -1 (altura de uma árvore vazia)
    if (raiz == NULL) {
        return -1;
    }
    
    // Calcula a altura das subárvores esquerda e direita recursivamente
    int altEsq = altura(raiz->esq) + 1;
    int altDir = altura(raiz->dir) + 1;

    // Retorna a maior altura entre as duas subárvores
    return (altEsq > altDir ? altEsq : altDir);
}


#include <stdio.h>
#include <stdlib.h>

// Funções já declaradas previamente (inserir, procurar, remover, altura, etc.)
// ... (coloque aqui as funções declaradas no seu código AVL) ...

int main() {
    struct NodoAVL *raiz = NULL; // Alocando espaço para a raiz/árvore

    int opcao, valor;

    do {
        printf("\n-=-=-=-=-=- MENU -=-=-=-=-=-=-");
        printf("\n\n[1] Inserir um elemento");
        printf("\n[2] Procurar um elemento");
        printf("\n[3] Excluir um elemento");
        printf("\n[4] Calcular a altura");
        printf("\n[5] Exibir a árvore");
        printf("\n[0] Sair do programa");
        printf("\n\nDigite a sua opção: ");

        opcao = validarEntrada();  // Valida a opção do menu

        switch (opcao) {
        case 1:
            printf("\nINSERIR NÓ");
            int n = 0;
            printf("\nDigite a quantidade de nós a serem adicionados: ");
            n = validarEntrada();  // Valida o número de nós a serem adicionados

            while (n > 0) {
                int num = 0;
                printf("\nDigite um valor: ");
                num = validarEntrada();  // Valida o valor a ser inserido
                raiz = inserir(raiz, num);  // Insere o valor na árvore
                n--;
            }
            break;

        case 2:
            printf("\nPROCURAR NÓ");
            printf("\nDigite um valor para procurar: ");
            valor = validarEntrada();  // Valida o valor a ser procurado
            procurar(raiz, valor);  // Procura o valor na árvore
            break;

        case 3:
            printf("\nEXCLUIR NÓ");
            printf("\nDigite um valor para ser excluido: ");
            valor = validarEntrada();  // Valida o valor a ser excluído
            raiz = remover(raiz, valor);  // Remove o valor da árvore
            break;

        case 4:
            printf("\nALTURA DA ÁRVORE");
            int alturaAtual = altura(raiz);  // Calcula a altura da árvore
            printf("\nA altura da árvore é: %i\n", alturaAtual); // Vale lembrar que a raiz sempre eh 0
            break; 

        case 5:
            printf("\nEXIBIR ÁRVORE \n");
            printf("\nPRE-ORDER: ");
            exibirPreOrdem(raiz);  // Exibe a árvore em pré-ordem

            printf("\nIN-ORDER: ");
            exibirEmOrdem(raiz);  // Exibe a árvore em ordem

            printf("\nPOS-ORDER: ");
            exibirPosOrdem(raiz);  // Exibe a árvore em pós-ordem
            printf("\n");
            break;

        case 0:
            printf("\nSAIR DO PROGRAMA");
            free(raiz);  // Libera a memória alocada para a árvore
            break;

        default:
            printf("\nOpção Inválida.");
            break;
        }
    } while (opcao != 0);

    return 0;
}
