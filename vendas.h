#ifndef VENDAS_H
#define VENDAS_H

#include "structs.h"

#define MAX_VENDAS 100

/* Le as vendas salvas em arquivo (chamar ao abrir o programa) */
void carregarVendas(void);

/* Registro, listagem e busca de vendas */
void registrarVenda(void);
void listarVendas(void);
void buscarVenda(void);

/* Usadas pelos relatorios: quantas vendas existem e o endereco da venda
   na posicao i (de 0 a totalDeVendas() - 1), ou NULL se i for invalido */
int totalDeVendas(void);
const Venda *obterVendaPorPosicao(int i);

#endif
