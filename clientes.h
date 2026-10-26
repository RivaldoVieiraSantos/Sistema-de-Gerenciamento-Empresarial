#ifndef CLIENTES_H
#define CLIENTES_H

#include "structs.h"

#define MAX_CLIENTES 100

/* Le os clientes salvos em arquivo (chamar ao abrir o programa) */
void carregarClientes(void);

/* Cadastro, listagem, busca, alteracao e exclusao de clientes */
void cadastrarCliente(void);
void listarClientes(void);
void buscarCliente(void);
void alterarCliente(void);
void excluirCliente(void);

#endif
