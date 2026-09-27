#include <stdio.h>
#include "produtos.h"
#include "utils.h"

/* Armazenamento dos produtos */
static Produto produtos[MAX_PRODUTOS];
static int totalProdutos = 0;
static int proximoCodigo = 1;

/* Mostra os dados de um produto */
static void mostrarProduto(Produto p) {
    printf("Codigo:     %d\n", p.codProduto);
    printf("Nome:       %s\n", p.nomeProduto);
    printf("Categoria:  %s\n", p.categoriaProduto);
    printf("Preco:      R$ %.2f\n", p.precoProduto);
    printf("Estoque:    %d\n", p.quantidadeProduto);
}

/* Retorna a posicao do produto no vetor, ou -1 se nao existir */
static int procurarPorCodigo(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codProduto == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(void) {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\nLimite de %d produtos atingido.\n", MAX_PRODUTOS);
        return;
    }

    Produto novo;
    novo.codProduto = proximoCodigo;

    printf("\n");
    printf("========================================\n");
    printf("      CADASTRAR PRODUTO (codigo %d)\n", novo.codProduto);
    printf("========================================\n");

    printf("Nome: ");
    lerTexto(novo.nomeProduto, sizeof(novo.nomeProduto));

    printf("Categoria: ");
    lerTexto(novo.categoriaProduto, sizeof(novo.categoriaProduto));

    printf("Preco: R$ ");
    novo.precoProduto = lerDecimal();

    printf("Quantidade em estoque: ");
    novo.quantidadeProduto = lerInteiro();

    produtos[totalProdutos] = novo;
    totalProdutos++;
    proximoCodigo++;

    printf("----------------------------------------\n");
    printf("Produto \"%s\" cadastrado com sucesso!\n", novo.nomeProduto);
    printf("----------------------------------------\n");
}

void listarProdutos(void) {
    printf("\n");
    printf("========================================\n");
    printf("        LISTA DE PRODUTOS (%d)\n", totalProdutos);
    printf("========================================\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        if (i > 0) {
            printf("----------------------------------------\n");
        }
        mostrarProduto(produtos[i]);
    }

    printf("========================================\n");
}

void buscarProduto(void) {
    printf("\n");
    printf("========================================\n");
    printf("            BUSCAR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("----------------------------------------\n");
    mostrarProduto(produtos[i]);
    printf("----------------------------------------\n");
}

void alterarProduto(void) {
    printf("\n");
    printf("========================================\n");
    printf("            ALTERAR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    lerTexto(produtos[i].nomeProduto, sizeof(produtos[i].nomeProduto));

    printf("Nova categoria: ");
    lerTexto(produtos[i].categoriaProduto, sizeof(produtos[i].categoriaProduto));

    printf("Novo preco: R$ ");
    produtos[i].precoProduto = lerDecimal();

    printf("Nova quantidade em estoque: ");
    produtos[i].quantidadeProduto = lerInteiro();

    printf("----------------------------------------\n");
    printf("Produto alterado com sucesso!\n");
    printf("----------------------------------------\n");
}

void excluirProduto(void) {
    printf("\n");
    printf("========================================\n");
    printf("            EXCLUIR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    /* Puxa os produtos seguintes uma posicao para tras */
    for (int j = i; j < totalProdutos - 1; j++) {
        produtos[j] = produtos[j + 1];
    }
    totalProdutos--;

    printf("----------------------------------------\n");
    printf("Produto excluido com sucesso!\n");
    printf("----------------------------------------\n");
}
