#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;

// Protótipos
void cadastrarComponentes();
void exibirComponentes();
void bubbleSortNome();
void insertionSortTipo();
void selectionSortPrioridade();
void buscaBinariaNome();
void medirTempo(void (*algoritmo)(void), char *nomeAlgoritmo);

int main() {
    int op;

    srand(time(NULL));

    do {
        printf("\n--- TORRE DE RESGATE ---\n");
        printf("1. Cadastrar Componentes\n");
        printf("2. Exibir Componentes\n");
        printf("3. Ordenar por Nome (Bubble Sort)\n");
        printf("4. Ordenar por Tipo (Insertion Sort)\n");
        printf("5. Ordenar por Prioridade (Selection Sort)\n");
        printf("6. Buscar Componente (Busca Binária por Nome)\n");
        printf("7. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar(); // Limpa buffer

        switch (op) {
            case 1: cadastrarComponentes(); break;
            case 2: exibirComponentes(); break;
            case 3: medirTempo(bubbleSortNome, "Bubble Sort (Nome)"); break;
            case 4: medirTempo(insertionSortTipo, "Insertion Sort (Tipo)"); break;
            case 5: medirTempo(selectionSortPrioridade, "Selection Sort (Prioridade)"); break;
            case 6: buscaBinariaNome(); break;
            case 7: printf("Saindo... Boa sorte na ilha!\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (op != 7);

    return 0;
}

void cadastrarComponentes() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido!\n");
        return;
    }

    Componente c;
    printf("Nome: ");
    fgets(c.nome, MAX_NOME, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Tipo (controle/suporte/propulsao): ");
    fgets(c.tipo, MAX_TIPO, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = '\0';

    printf("Prioridade (1-10): ");
    scanf("%d", &c.prioridade);
    getchar();

    componentes[totalComponentes++] = c;
    printf("✅ Componente '%s' cadastrado!\n", c.nome);
}

void exibirComponentes() {
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado!\n");
        return;
    }

    printf("\n--- Componentes ---\n");
    for (int i = 0; i < totalComponentes; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

// --- BUBBLE SORT (Nome)
void bubbleSortNome() {
    int comparacoes = 0;
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    printf("✅ Bubble Sort (Nome) - Comparações: %d\n", comparacoes);
}

// --- INSERTION SORT (Tipo)
void insertionSortTipo() {
    int comparacoes = 0;
    for (int i = 1; i < totalComponentes; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else break;
        }
        componentes[j + 1] = chave;
    }
    printf("✅ Insertion Sort (Tipo) - Comparações: %d\n", comparacoes);
}

// --- SELECTION SORT (Prioridade)
void selectionSortPrioridade() {
    int comparacoes = 0;
    for (int i = 0; i < totalComponentes - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[minIdx].prioridade) {
                minIdx = j;
            }
        }
        Componente temp = componentes[i];
        componentes[i] = componentes[minIdx];
        componentes[minIdx] = temp;
    }
    printf("✅ Selection Sort (Prioridade) - Comparações: %d\n", comparacoes);
}

// --- BUSCA BINÁRIA (Nome)
void buscaBinariaNome() {
    if (totalComponentes == 0) {
        printf("Nenhum componente para buscar!\n");
        return;
    }

    // Ordena por nome primeiro (Bubble Sort)
    bubbleSortNome();

    char nomeBusca[MAX_NOME];
    printf("Nome do componente a buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int esq = 0, dir = totalComponentes - 1, comp = 0;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        comp++;
        int cmp = strcmp(componentes[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("✅ Componente encontrado!\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   componentes[meio].nome, componentes[meio].tipo, componentes[meio].prioridade);
            printf("Comparações: %d\n", comp);
            return;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    printf("❌ Componente '%s' não encontrado!\n", nomeBusca);
    printf("Comparações: %d\n", comp);
}

// --- MEDIR TEMPO
void medirTempo(void (*algoritmo)(void), char *nomeAlgoritmo) {
    clock_t inicio = clock();
    algoritmo();
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%s executado em %.6f segundos.\n", nomeAlgoritmo, tempo);
    exibirComponentes();
}