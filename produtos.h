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

/* Usada pelo modulo de vendas: devolve o endereco do produto (para dar
   baixa no estoque direto nele), ou NULL se o codigo nao existir */
Produto *obterProduto(int codigo);

#endif
