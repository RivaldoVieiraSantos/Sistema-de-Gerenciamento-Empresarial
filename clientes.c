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

        printf("\nSe desejar cadastrar um novo cliente digite 1, para sair digite 0: ");
        continuar = lerInteiro();
    } while (continuar == 1);

    printf("Cadastro concluido. Total de clientes: %d\n", totalClientes);
}
