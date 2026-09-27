#ifndef PRODUTOS_H
#define PRODUTOS_H

#include "structs.h"

#define MAX_PRODUTOS 100

/* Cadastro, listagem, busca, alteracao e exclusao de produtos */
void cadastrarProduto(void);
void listarProdutos(void);
void buscarProduto(void);
void alterarProduto(void);
void excluirProduto(void);

#endif
