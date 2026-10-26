#include <stdio.h>
#include "relatorios.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "utils.h"

/* Soma o valor de todas as vendas */
static float valorTotalVendido(void) {
    float total = 0;

    for (int i = 0; i < totalDeVendas(); i++) {
        total += obterVendaPorPosicao(i)->valorTotal;
    }
    return total;
}

/* Soma quantas unidades do produto foram vendidas, somando todas as vendas */
static int unidadesVendidas(int codProduto) {
    int unidades = 0;

    for (int i = 0; i < totalDeVendas(); i++) {
        const Venda *v = obterVendaPorPosicao(i);

        for (int j = 0; j < v->totalItens; j++) {
            if (v->itens[j].codProduto == codProduto) {
                unidades += v->itens[j].quantidade;
            }
        }
    }
    return unidades;
}

/* Soma quanto o cliente gastou em todas as vendas. A quantidade de compras
   volta por referencia, em *compras (a funcao "devolve" dois valores). */
static float totalCompradoPor(int codCliente, int *compras) {
    float total = 0;
    *compras = 0;

    for (int i = 0; i < totalDeVendas(); i++) {
        const Venda *v = obterVendaPorPosicao(i);

        if (v->codCliente == codCliente) {
            total += v->valorTotal;
            (*compras)++;
        }
    }
    return total;
}

void resumoGeral(void) {
    limparTela();
    printf("========================================\n");
    printf("             RESUMO GERAL\n");
    printf("========================================\n");
    printf("Clientes cadastrados:  %d\n", totalDeClientes());
    printf("Produtos cadastrados:  %d\n", totalDeProdutos());
    printf("Valor do estoque:      R$ %.2f\n", valorDoEstoque());
    printf("Vendas realizadas:     %d\n", totalDeVendas());
    printf("Valor total vendido:   R$ %.2f\n", valorTotalVendido());
    printf("========================================\n");
}

void produtoMaisVendido(void) {
    const ItemVenda *maisVendido = NULL;
    int maiorQuantidade = 0;

    limparTela();
    printf("========================================\n");
    printf("          PRODUTO MAIS VENDIDO\n");
    printf("========================================\n");

    /* Passa por todos os itens vendidos e guarda o produto com mais
       unidades. O nome vem do item, entao funciona mesmo se o produto
       ja tiver sido excluido. */
    for (int i = 0; i < totalDeVendas(); i++) {
        const Venda *v = obterVendaPorPosicao(i);

        for (int j = 0; j < v->totalItens; j++) {
            int unidades = unidadesVendidas(v->itens[j].codProduto);

            if (unidades > maiorQuantidade) {
                maiorQuantidade = unidades;
                maisVendido = &v->itens[j];
            }
        }
    }

    if (maisVendido == NULL) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("Codigo:            %d\n", maisVendido->codProduto);
    printf("Nome:              %s\n", maisVendido->nomeProduto);
    printf("Unidades vendidas: %d\n", maiorQuantidade);
    printf("========================================\n");
}

void clienteQueMaisComprou(void) {
    int melhorCliente = 0;
    int melhorCompras = 0;
    float maiorValor = 0;

    limparTela();
    printf("========================================\n");
    printf("     CLIENTE COM MAIOR VOLUME DE COMPRAS\n");
    printf("========================================\n");

    if (totalDeVendas() == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    /* Para o cliente de cada venda, soma tudo o que ele comprou e guarda
       o que gastou mais (o volume e medido em reais) */
    for (int i = 0; i < totalDeVendas(); i++) {
        int codCliente = obterVendaPorPosicao(i)->codCliente;
        int compras;
        float valor = totalCompradoPor(codCliente, &compras);

        if (melhorCliente == 0 || valor > maiorValor) {
            melhorCliente = codCliente;
            melhorCompras = compras;
            maiorValor = valor;
        }
    }

    const Cliente *cliente = obterCliente(melhorCliente);

    printf("Codigo:            %d\n", melhorCliente);
    printf("Nome:              %s\n",
           cliente != NULL ? cliente->nomeCliente : "(cliente excluido)");
    printf("Compras feitas:    %d\n", melhorCompras);
    printf("Total comprado:    R$ %.2f\n", maiorValor);
    printf("========================================\n");
}
