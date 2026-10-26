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

#endif
