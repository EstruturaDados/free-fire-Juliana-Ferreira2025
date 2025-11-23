#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// --- STRUCTS ---
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Vetor
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

No* cabecaLista = NULL;
int totalLista = 0;

// Contadores de comparações
int compSequencial = 0;
int compBinaria = 0;

// Protótipos VETOR
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// Protótipos LISTA
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();

// Menu
int menuPrincipal();
int menuEstrutura();

int main() {
    int op, estrutura;

    srand(time(NULL));

    while ((estrutura = menuEstrutura()) != 3) {
        switch (estrutura) {
            case 1:
                while ((op = menuPrincipal()) != 5) {
                    switch (op) {
                        case 1: inserirItemVetor(); break;
                        case 2: removerItemVetor(); break;
                        case 3: listarItensVetor(); break;
                        case 4: 
                            printf("1. Busca Sequencial | 2. Busca Binária: ");
                            int tipoBusca;
                            scanf("%d", &tipoBusca);
                            getchar();
                            if (tipoBusca == 1) buscarSequencialVetor();
                            else buscarBinariaVetor();
                            break;
                    }
                }
                break;

            case 2:
                while ((op = menuPrincipal()) != 5) {
                    switch (op) {
                        case 1: inserirItemLista(); break;
                        case 2: removerItemLista(); break;
                        case 3: listarItensLista(); break;
                        case 4: buscarSequencialLista(); break;
                    }
                }
                break;
        }
    }

    printf("Saindo... Até mais!\n");
    return 0;
}

int menuEstrutura() {
    int op;
    printf("\n--- Escolha a Estrutura ---\n");
    printf("1. Vetor (Lista Sequencial)\n");
    printf("2. Lista Encadeada\n");
    printf("3. Sair\n");
    printf("Opção: ");
    scanf("%d", &op);
    getchar();
    return op;
}

int menuPrincipal() {
    int op;
    printf("\n--- MENU ---\n");
    printf("1. Inserir Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item\n");
    printf("5. Voltar\n");
    printf("Opção: ");
    scanf("%d", &op);
    getchar();
    return op;
}

// --- VETOR ---
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma/munição/cura): ");
    fgets(novo.tipo, MAX_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochilaVetor[totalVetor] = novo;
    totalVetor++;
    printf("✅ Item '%s' adicionado ao vetor!\n", novo.nome);
}

void removerItemVetor() {
    char nome[MAX_NOME];
    printf("Nome do item a remover: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("✅ Item '%s' removido do vetor!\n", nome);
            return;
        }
    }
    printf("❌ Item não encontrado no vetor!\n");
}

void listarItensVetor() {
    if (totalVetor == 0) {
        printf("Mochila (vetor) vazia!\n");
        return;
    }
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void buscarSequencialVetor() {
    char nome[MAX_NOME];
    printf("Nome do item a buscar (sequencial): ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    compSequencial = 0;
    for (int i = 0; i < totalVetor; i++) {
        compSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("✅ Encontrado (sequencial)! Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", compSequencial);
            return;
        }
    }
    printf("❌ Item não encontrado (sequencial)!\n");
    printf("Comparações: %d\n", compSequencial);
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
    printf("✅ Vetor ordenado por nome!\n");
}

void buscarBinariaVetor() {
    if (totalVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    ordenarVetor();

    char nome[MAX_NOME];
    printf("Nome do item a buscar (binária): ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    compBinaria = 0;
    int esq = 0, dir = totalVetor - 1, meio;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        compBinaria++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("✅ Encontrado (binária)! Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", compBinaria);
            return;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    printf("❌ Item não encontrado (binária)!\n");
    printf("Comparações: %d\n", compBinaria);
}

// --- LISTA ENCADEADA ---
void inserirItemLista() {
    if (totalLista >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (!novoNo) {
        printf("Erro de alocação!\n");
        exit(1);
    }

    printf("Nome: ");
    fgets(novoNo->dados.nome, MAX_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';

    printf("Tipo (arma/munição/cura): ");
    fgets(novoNo->dados.tipo,MAX_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    getchar();

    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;
    totalLista++;

    printf("✅ Item '%s' adicionado à lista!\n", novoNo->dados.nome);
}

void removerItemLista() {
    char nome[MAX_NOME];
    printf("Nome do item a remover: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = cabecaLista;
    No* anterior = NULL;
    compSequencial = 0;

    while (atual) {
        compSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                cabecaLista = atual->proximo;
            }
            free(atual);
            totalLista--;
            printf("✅ Item '%s' removido da lista!\n", nome);
            printf("Comparações: %d\n", compSequencial);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("❌ Item '%s' não encontrado na lista!\n", nome);
    printf("Comparações: %d\n", compSequencial);
}

void listarItensLista() {
    if (!cabecaLista) {
        printf("Mochila (lista) vazia!\n");
        return;
    }

    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = cabecaLista;
    while (atual) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    char nome[MAX_NOME];
    printf("Nome do item a buscar (sequencial lista): ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = cabecaLista;
    compSequencial = 0;

    while (atual) {
        compSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("✅ Encontrado (sequencial lista)! Nome: %s | Tipo: %s | Qtd: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações: %d\n", compSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("❌ Item '%s' não encontrado na lista!\n", nome);
    printf("Comparações: %d\n", compSequencial);
}

void liberarLista() {
    No* atual = cabecaLista;
    while (atual) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    cabecaLista = NULL;
    totalLista = 0;
    printf("✅ Memória da lista liberada!\n");
}

