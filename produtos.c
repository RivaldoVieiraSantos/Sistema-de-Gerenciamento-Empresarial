#include <stdio.h>
#include "produtos.h"
#include "utils.h"

/* Armazenamento dos pdo */
static Produto produtos[MAX_PRODUTOS];
static int totalProdutos = 0;
static int proximoCodigo = 1;

void cadastrarProdutos(void) {
    int continuar;

    do {
        if (totalProdutos >= MAX_PRODUTOS) {
            printf("Limite de %d produtos atingido.\n", MAX_PRODUTOS);
            return;
        }

        Produto novo;
        novo.codProduto = proximoCodigo;

        printf("\n--- Cadastro do Produto (codigo %d) ---\n", novo.codProduto);

        printf("Nome: ");
        lerTexto(novo.nomeProduto, sizeof(novo.nomeProduto));

        printf("codigo do Produto (somente numeros): ");
        novo.codProduto = lerInteiro();

        printf("Preço: ");
        novo.precoProduto = lerInteiro();

        printf("Quantidade: ");
        lerTexto(novo.quantidadeProduto, sizeof(novo.quantidadeProduto));

        printf("Categoria: ");
        lerTexto(novo.categoriaProduto, sizeof(novo.categoriaProduto));

        produtos[totalProdutos] = novo;
        totalProdutos++;
        proximoCodigo++;

        printf("Produto cadastrado com sucesso! Codigo: %d\n", novo.codProduto);

        do {
            printf("\nSe desejar cadastrar um novo produto digite 1, para ver os produtos cadastrados digite 2, para sair digite 0: ");
            continuar = lerInteiro();

            if (continuar == 2) {
                listarProduto();
            }
        } while (continuar == 2);
    } while (continuar == 1);

    printf("Cadastro concluido. Total de produtos: %d\n", totalProdutos);
}

void listarProduto(void) {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        printf("Se desejar cadastrar um produto digite 1, para sair digite 0: ");

        if (lerInteiro() == 1) {
            cadastrarProduto();
        }

        /* Se ainda nao tem produto (digitou 0), sai sem listar */
        if (totalProdutos == 0) {
            return;
        }
    }

    printf("\n--- Lista de Produtos (%d) ---\n", totalProdutos);

    for (int i = 0; i < totalProdutos; i++) {
        
        printf("Nome:     %s\n", produtos[i].nomeProduto);
        printf("\nCodigo:   %d\n", produtos[i].codProduto);
        printf("Preço:      %d\n", produtos[i].precoProduto);
        printf("Quantidade: %d\n", produtos[i].quantidadeProduto);
        printf("Categoria:   %s\n", produtos[i].categoriaProduto);
        
    }
}
