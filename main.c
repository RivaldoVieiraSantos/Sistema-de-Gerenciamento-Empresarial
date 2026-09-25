#include <stdio.h>
#include "structs.h"
#include "clientes.h"
#include "utils.h"


void menuClientes(void) {
    int opcao;

    do {
        printf("\n");
        printf("========================================\n");
        printf("             MENU CLIENTES              \n");
        printf("========================================\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Buscar cliente\n");
        printf("4 - Alterar cliente\n");
        printf("5 - Excluir cliente\n");
        printf("0 - Voltar\n");
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
                printf("\nFuncao de buscar cliente está em desenvolvimento.\n");
                break;

            case 4:
                printf("\nFuncao de alterar cliente está em desenvolvimento.\n");
                break;

            case 5:
                printf("\nFuncao de excluir cliente está em desenvolvimento.\n");
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}


void menuPrincipal(void) {
    int opcao;

    do {
        printf("\n");
        printf("========================================\n");
        printf("    SISTEMA DE GERENCIAMENTO EMPRESARIAL\n");
        printf("========================================\n");
        printf("1 - Clientes\n");
        printf("2 - Produtos\n");
        printf("3 - Estatisticas\n");
        printf("0 - Sair\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            case 1:
                menuClientes();
                break;

            case 2:
                printf("\nModulo de produtos está em desenvolvimento.\n");
                break;

            case 3:
                printf("\nModulo de estatisticas está em desenvolvimento.\n");
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}


int main(void) {

    menuPrincipal();

    return 0;
}