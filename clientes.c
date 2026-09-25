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

        printf("\n--- Cadastro de Cliente (codigo %d) ---\n", novo.codCliente);

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

        printf("Cliente cadastrado com sucesso! Codigo: %d\n", novo.codCliente);

        do {
            printf("\nSe desejar cadastrar um novo cliente digite 1, para ver os clientes cadastrados digite 2, para sair digite 0: ");
            continuar = lerInteiro();

            if (continuar == 2) {
                listarClientes();
            }
        } while (continuar == 2);
    } while (continuar == 1);

    printf("Cadastro concluido. Total de clientes: %d\n", totalClientes);
}

void listarClientes(void) {
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        printf("Se desejar cadastrar um cliente digite 1, para sair digite 0: ");

        if (lerInteiro() == 1) {
            cadastrarCliente();
        }

        /* Se ainda nao tem cliente (digitou 0), sai sem listar */
        if (totalClientes == 0) {
            return;
        }
    }

    printf("\n--- Lista de Clientes (%d) ---\n", totalClientes);

    for (int i = 0; i < totalClientes; i++) {
        printf("\nCodigo:   %d\n", clientes[i].codCliente);
        printf("Nome:     %s\n", clientes[i].nomeCliente);
        printf("CPF:      %d\n", clientes[i].CPFCliente);
        printf("Telefone: %d\n", clientes[i].telefoneCliente);
        printf("Cidade:   %s\n", clientes[i].cidadeCliente);
        printf("Email:    %s\n", clientes[i].emailCliente);
    }
}
