#include <stdio.h>
#include "clientes.h"
#include "utils.h"

/* Armazenamento dos clientes */
static Cliente clientes[MAX_CLIENTES];
static int totalClientes = 0;
static int proximoCodigo = 1;

void cadastrarCliente(void) {
    int continuar;

    do {
        if (totalClientes >= MAX_CLIENTES) {
            printf("Limite de %d clientes atingido.\n", MAX_CLIENTES);
            return;
        }

        Cliente novo;
        novo.codCliente = proximoCodigo;

        printf("\n");
        printf("========================================\n");
        printf("      CADASTRO DE CLIENTE (codigo %d)\n", novo.codCliente);
        printf("========================================\n");

        printf("Nome: ");
        lerTexto(novo.nomeCliente, sizeof(novo.nomeCliente));

        printf("CPF (somente numeros): ");
        novo.CPFCliente = lerInteiro();

        printf("Telefone: ");
        novo.telefoneCliente = lerInteiro();

        printf("Cidade: ");
        lerTexto(novo.cidadeCliente, sizeof(novo.cidadeCliente));

        printf("Email: ");
        lerTexto(novo.emailCliente, sizeof(novo.emailCliente));

        clientes[totalClientes] = novo;
        totalClientes++;
        proximoCodigo++;

        printf("----------------------------------------\n");
        printf("Cliente \"%s\" cadastrado com sucesso!\n", novo.nomeCliente);
        printf("----------------------------------------\n");

        do {
            printf("\nO que gostaria de fazer agora?\n");
            printf("1 - Cadastrar um novo cliente\n");
            printf("2 - Ver os clientes cadastrados\n");
            printf("0 - Sair\n");
            printf("Escolha uma opcao: ");
            continuar = lerInteiro();

            if (continuar == 2) {
                listarClientes();
            }
        } while (continuar == 2);
    } while (continuar == 1);

    printf("\n----------------------------------------\n");
    printf("Cadastro concluido. Total de clientes: %d\n", totalClientes);
    printf("----------------------------------------\n");
}

void listarClientes(void) {
    if (totalClientes == 0) {
        printf("\n----------------------------------------\n");
        printf("Nenhum cliente cadastrado.\n");
        printf("----------------------------------------\n");
        printf("Se desejar cadastrar um cliente digite 1, para sair digite 0: ");

        if (lerInteiro() == 1) {
            cadastrarCliente();
        }

        /* Se ainda nao tem cliente (digitou 0), sai sem listar */
        if (totalClientes == 0) {
            return;
        }
    }

    printf("\n");
    printf("========================================\n");
    printf("        LISTA DE CLIENTES (%d)\n", totalClientes);
    printf("========================================\n");

    for (int i = 0; i < totalClientes; i++) {
        if (i > 0) {
            printf("----------------------------------------\n");
        }
        printf("Codigo:   %d\n", clientes[i].codCliente);
        printf("Nome:     %s\n", clientes[i].nomeCliente);
        printf("CPF:      %d\n", clientes[i].CPFCliente);
        printf("Telefone: %d\n", clientes[i].telefoneCliente);
        printf("Cidade:   %s\n", clientes[i].cidadeCliente);
        printf("Email:    %s\n", clientes[i].emailCliente);
    }

    printf("========================================\n");
}
