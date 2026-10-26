#include <stdio.h>
#include "structs.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "utils.h"


void menuClientes(void) {
    int opcao;

    do {
        limparTela();
        printf("========================================\n");
        printf("             MENU CLIENTES              \n");
        printf("========================================\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Buscar cliente\n");
        printf("4 - Alterar cliente\n");
        printf("5 - Excluir cliente\n");
        printf("0 - Voltar ao menu principal\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            case 1:
                cadastrarCliente();
                break;

            case 2:
                listarClientes();
                break;

            case 3:
                buscarCliente();
                break;

            case 4:
                alterarCliente();
                break;

            case 5:
                excluirCliente();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        /* Pausa para ler o resultado. O cadastro e a busca de cliente ja
           cuidam das proprias pausas, entao voltam direto para este menu. */
        if (opcao != 0 && opcao != 1 && opcao != 3) {
            pausar();
        }

    } while (opcao != 0);
}


void menuProdutos(void) {
    int opcao;

    do {
        limparTela();
        printf("========================================\n");
        printf("             MENU PRODUTOS              \n");
        printf("========================================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Alterar produto\n");
        printf("5 - Excluir produto\n");
        printf("0 - Voltar ao menu principal\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            case 1:
                cadastrarProduto();
                break;

            case 2:
                listarProdutos();
                break;

            case 3:
                buscarProduto();
                break;

            case 4:
                alterarProduto();
                break;

            case 5:
                excluirProduto();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);
}

void menuVendas(void) {
    int opcao;

    do {
        limparTela();
        printf("========================================\n");
        printf("              MENU VENDAS               \n");
        printf("========================================\n");
        printf("1 - Registrar venda\n");
        printf("2 - Listar vendas\n");
        printf("3 - Buscar venda\n");
        printf("0 - Voltar ao menu principal\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            case 1:
                registrarVenda();
                break;

            case 2:
                listarVendas();
                break;

            case 3:
                buscarVenda();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            pausar();
        }

    } while (opcao != 0);
}


void menuPrincipal(void) {
    int opcao;

    do {
        limparTela();
        printf("========================================\n");
        printf("    SISTEMA DE GERENCIAMENTO EMPRESARIAL\n");
        printf("========================================\n");
        printf("1 - Clientes\n");
        printf("2 - Produtos\n");
        printf("3 - Vendas\n");
        printf("4 - Estatisticas\n");
        printf("0 - Sair\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            case 1:
                menuClientes();
                break;

            case 2:
                menuProdutos();
                break;

            case 3:
                menuVendas();
                break;

            case 4:
                printf("\nModulo de estatisticas está em desenvolvimento.\n");
                pausar();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }

    } while (opcao != 0);
}


int main(void) {

    carregarClientes();
    carregarVendas();
    menuPrincipal();

    return 0;
}