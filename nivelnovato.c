#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

int totalItens = 0;
Item mochila[MAX_ITENS];

// Protótipos
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
int menu();

int main() {
    int opcao;

    while ((opcao = menu()) != 5) {
        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            default: printf("Opção inválida!\n");
        }
    }
    printf("Saindo do inventário... Até a próxima!\n");
    return 0;
}

int menu() {
    int op;
    printf("\n--- INVENTÁRIO ---\n");
    printf("1. Inserir Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item\n");
    printf("5. Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    getchar(); // Limpa buffer
    return op;
}

void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma/munição/cura): ");
    fgets(novo.tipo, MAX_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[totalItens] = novo;
    totalItens++;
    printf("✅ Item '%s' adicionado!\n", novo.nome);
}

void removerItem() {
    char nomeBusca[MAX_NOME];
    printf("Nome do item a remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("✅ Item '%s' removido!\n", nomeBusca);
            return;
        }
    }
    printf("❌ Item '%s' não encontrado!\n", nomeBusca);
}

void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem() {
    char nomeBusca[MAX_NOME];
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("✅ Encontrado!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("❌ Item '%s' não encontrado!\n", nomeBusca);
}