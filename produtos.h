#ifndef PRODUTOS_H
#define PRODUTOS_H

#include "structs.h"

#define MAX_PRODUTOS 100

/* Produto com esta quantidade ou menos e considerado com estoque baixo */
#define ESTOQUE_MINIMO 5

/* Le os produtos salvos em arquivo (chamar ao abrir o programa) */
void carregarProdutos(void);

/* Grava todos os produtos no arquivo. Chamada pelo proprio modulo depois de
   cada cadastro, alteracao ou exclusao, e pelas vendas depois da baixa no estoque */
void salvarProdutos(void);

/* Cadastro, listagem, busca, alteracao e exclusao de produtos */
void cadastrarProduto(void);
void listarProdutos(void);
void buscarProduto(void);
void alterarProduto(void);
void excluirProduto(void);

/* Controle de estoque */
void consultarEstoque(void);
void listarEstoqueBaixo(void);

/* Usada pelo modulo de vendas: devolve o endereco do produto (para dar
   baixa no estoque direto nele), ou NULL se o codigo nao existir */
Produto *obterProduto(int codigo);

#endif
