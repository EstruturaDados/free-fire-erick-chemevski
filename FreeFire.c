#include <stdio.h>
#include <string.h>

// Definições Constantes
#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

// 1. Definição da Struct (O "Blueprint" do Item)
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Variáveis Globais (Mochila e Contador)
Item mochila[MAX_ITENS];
int numItens = 0;

// Protótipos das Funções
void adicionarItem();
void removerItem();
void listarItens();
void limparBuffer();

int main() {
    int opcao;

    do {
        // Menu Interativo
        printf("\n=== MOCHILA DE SOBREVIVENCIA (FREE FIRE) ===\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item (Descarte)\n");
        printf("3. Listar Inventario\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o "enter" pendente

        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\nSaindo da ilha... Boa sorte, sobrevivente!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Função para adicionar itens (Loot)
void adicionarItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n[ERRO] A mochila esta cheia! Descarte algo antes.\n");
        return;
    }

    Item novoItem;

    printf("\n--- Novo Loot ---\n");
    printf("Nome do item: ");
    // Lê string com espaços (ex: "Kit Medico")
    scanf(" %[^\n]", novoItem.nome); 
    
    printf("Tipo (ex: Municao, Cura, Arma): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    // Salva na mochila na próxima posição livre
    mochila[numItens] = novoItem;
    numItens++;

    printf("\n[SUCESSO] %s adicionado a mochila!\n", novoItem.nome);
}

// Função para remover itens pelo nome
void removerItem() {
    if (numItens == 0) {
        printf("\n[AVISO] A mochila esta vazia.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n--- Descartar Item ---\n");
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;

    // Percorre o vetor procurando o item
    for (int i = 0; i < numItens; i++) {
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            
            // Remove o item deslocando os próximos para trás (Shift Left)
            // Ex: [A, B, C, D] -> Remove B -> [A, C, D]
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            numItens--; // Diminui o total de itens
            encontrado = 1;
            printf("\n[SUCESSO] Item '%s' removido.\n", nomeBusca);
            break; // Para o loop após encontrar
        }
    }

    if (!encontrado) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

// Função para listar todos os itens (Tabela)
void listarItens() {
    if (numItens == 0) {
        printf("\n[AVISO] Mochila vazia. Va buscar loot!\n");
        return;
    }

    printf("\n--- Conteudo da Mochila (%d/%d) ---\n", numItens, MAX_ITENS);
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QTD");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-20s | %-15s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------------------------\n");
}

// Utilitário para limpar buffer do teclado (evita pular inputs)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}