#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "utils.h"

/* Armazenamento dos clientes */
static Cliente clientes[MAX_CLIENTES];
static int totalClientes = 0;
static int proximoCodigo = 1;

/* Mostra os dados de um cliente (recebe o endereco, sem copiar a struct) */
static void mostrarCliente(const Cliente *c) {
    printf("Codigo:   %d\n", c->codCliente);
    printf("Nome:     %s\n", c->nomeCliente);
    printf("CPF:      %s\n", c->CPFCliente);
    printf("Telefone: %s\n", c->telefoneCliente);
    printf("Cidade:   %s\n", c->cidadeCliente);
    printf("Email:    %s\n", c->emailCliente);
}

/* Retorna a posicao do cliente no vetor, ou -1 se nao existir */
static int procurarPorCodigo(int codigo) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].codCliente == codigo) {
            return i;
        }
    }
    return -1;
}

/* Retorna a posicao do cliente com esse CPF, ou -1 se nao existir */
static int procurarPorCPF(const char *cpf) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].CPFCliente, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

/* Le um CPF e repete a pergunta se ele ja for de outro cliente.
   'ignorar' e a posicao do cliente que esta sendo alterado (ele pode
   manter o proprio CPF); no cadastro passa -1. */
static void lerCPFSemDuplicar(char *dest, int tamanho, int ignorar) {
    while (1) {
        lerDigitos(dest, tamanho, 11, 11);

        int dono = procurarPorCPF(dest);
        if (dono == -1 || dono == ignorar) {
            return;
        }

        printf("CPF ja cadastrado para o cliente %d (%s). Digite outro CPF: ",
               clientes[dono].codCliente, clientes[dono].nomeCliente);
    }
}

/* Pede os novos dados do cliente que esta na posicao i do vetor.
   Usada pelo "Alterar cliente" e logo depois de um cadastro. */
static void editarCliente(int i) {
    /* Mostra os dados atuais para a pessoa saber o que esta alterando */
    printf("----------------------------------------\n");
    printf("Dados atuais:\n");
    mostrarCliente(&clientes[i]);
    printf("----------------------------------------\n");

    printf("Novo nome: ");
    lerTexto(clientes[i].nomeCliente, sizeof(clientes[i].nomeCliente));

    printf("Novo CPF (somente numeros): ");
    lerCPFSemDuplicar(clientes[i].CPFCliente, sizeof(clientes[i].CPFCliente), i);

    printf("Novo telefone com DDD (somente numeros): ");
    lerDigitos(clientes[i].telefoneCliente, sizeof(clientes[i].telefoneCliente), 10, 11);

    printf("Nova cidade: ");
    lerTexto(clientes[i].cidadeCliente, sizeof(clientes[i].cidadeCliente));

    printf("Novo email: ");
    lerTexto(clientes[i].emailCliente, sizeof(clientes[i].emailCliente));

    printf("----------------------------------------\n");
    printf("Cliente alterado com sucesso!\n");
    printf("----------------------------------------\n");
}

/* Mostra o cliente da posicao i, pede confirmacao e exclui.
   Retorna 1 se excluiu ou 0 se a pessoa cancelou.
   Usada pelo "Excluir cliente" e logo depois de um cadastro. */
static int excluirNaPosicao(int i) {
    printf("----------------------------------------\n");
    mostrarCliente(&clientes[i]);
    printf("----------------------------------------\n");
    printf("Confirma a exclusao deste cliente? (1 - Sim / 0 - Nao): ");

    if (lerInteiro() != 1) {
        printf("\nExclusao cancelada.\n");
        return 0;
    }

    /* Puxa os clientes seguintes uma posicao para tras */
    for (int j = i; j < totalClientes - 1; j++) {
        clientes[j] = clientes[j + 1];
    }
    totalClientes--;

    printf("----------------------------------------\n");
    printf("Cliente excluido com sucesso!\n");
    printf("----------------------------------------\n");

    return 1;
}

/* Cadastra clientes e, depois de cada um, mostra o que da pra fazer em seguida.
   Cuida das proprias pausas: ao voltar para o menu de clientes nao pede ENTER. */
void cadastrarCliente(void) {
    int cadastrarOutro;

    do {
        if (totalClientes >= MAX_CLIENTES) {
            printf("Limite de %d clientes atingido.\n", MAX_CLIENTES);
            pausar();
            return;
        }

        Cliente novo;
        cadastrarOutro = 0;
        novo.codCliente = proximoCodigo;

        limparTela();
        printf("========================================\n");
        printf("      CADASTRO DE CLIENTE (codigo %d)\n", novo.codCliente);
        printf("========================================\n");

        printf("Nome: ");
        lerTexto(novo.nomeCliente, sizeof(novo.nomeCliente));

        printf("CPF (somente numeros): ");
        lerCPFSemDuplicar(novo.CPFCliente, sizeof(novo.CPFCliente), -1);

        printf("Telefone com DDD (somente numeros): ");
        lerDigitos(novo.telefoneCliente, sizeof(novo.telefoneCliente), 10, 11);

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

        /* Fica neste menu ate a pessoa cadastrar outro, excluir o
           recem-cadastrado ou voltar ao menu de clientes */
        int ficarNoMenu = 1;

        while (ficarNoMenu) {
            printf("\nO que gostaria de fazer agora?\n");
            printf("1 - Editar o cliente cadastrado\n");
            printf("2 - Ver os clientes cadastrados\n");
            printf("3 - Cadastrar um novo cliente\n");
            printf("4 - Excluir o cliente cadastrado\n");
            printf("0 - Voltar ao menu de clientes\n");
            printf("Escolha uma opcao: ");

            switch (lerInteiro()) {

                case 1:
                    limparTela();
                    printf("========================================\n");
                    printf("      EDITAR CLIENTE (codigo %d)\n", novo.codCliente);
                    printf("========================================\n");
                    editarCliente(totalClientes - 1);  /* o recem-cadastrado e o ultimo */
                    break;

                case 2:
                    listarClientes();
                    break;

                case 3:
                    cadastrarOutro = 1;
                    ficarNoMenu = 0;
                    break;

                case 4:
                    limparTela();
                    printf("========================================\n");
                    printf("      EXCLUIR CLIENTE (codigo %d)\n", novo.codCliente);
                    printf("========================================\n");

                    /* Se excluiu, nao ha mais o que editar/excluir: mostra a
                       confirmacao e volta ao menu de clientes */
                    if (excluirNaPosicao(totalClientes - 1)) {
                        pausar();
                        ficarNoMenu = 0;
                    }
                    break;

                case 0:
                    ficarNoMenu = 0;
                    break;

                default:
                    printf("\nOpcao invalida! Tente novamente.\n");
            }
        }
    } while (cadastrarOutro);
}

void listarClientes(void) {
    if (totalClientes == 0) {
        limparTela();
        printf("----------------------------------------\n");
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

    limparTela();
    printf("========================================\n");
    printf("        LISTA DE CLIENTES (%d)\n", totalClientes);
    printf("========================================\n");

    for (int i = 0; i < totalClientes; i++) {
        if (i > 0) {
            printf("----------------------------------------\n");
        }
        mostrarCliente(&clientes[i]);
    }

    printf("========================================\n");
}

void alterarCliente(void) {
    limparTela();
    printf("========================================\n");
    printf("            ALTERAR CLIENTE\n");
    printf("========================================\n");

    printf("Digite o codigo do cliente: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nCliente nao encontrado.\n");
        return;
    }

    editarCliente(i);
}

void excluirCliente(void) {
    limparTela();
    printf("========================================\n");
    printf("            EXCLUIR CLIENTE\n");
    printf("========================================\n");

    printf("Digite o codigo do cliente: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nCliente nao encontrado.\n");
        return;
    }

    excluirNaPosicao(i);
}
