#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int codCliente;
    char nomeCliente[50];
    /* CPF e telefone como texto: um int vai so ate 2.147.483.647 (10
       digitos), e CPF tem 11; alem disso, numero perde o zero da frente. */
    char CPFCliente[12];       /* 11 digitos + '\0' */
    char telefoneCliente[16];  /* DDD + numero, com folga */
    char cidadeCliente[50];
    char emailCliente[80];

} Cliente;

typedef struct {
    int   codProduto;
    char  nomeProduto[50];
    char  categoriaProduto[50];
    float precoProduto;
    int   quantidadeProduto;

} Produto;

#define MAX_ITENS_VENDA 20

/* Um produto dentro de uma venda. Guarda nome e preco do momento da venda:
   se o produto for alterado ou excluido depois, a venda continua igual. */
typedef struct {
    int   codProduto;
    char  nomeProduto[50];
    int   quantidade;
    float precoUnitario;

} ItemVenda;

typedef struct {
    int       codVenda;
    int       codCliente;
    char      data[11];                  /* dd/mm/aaaa + '\0' */
    ItemVenda itens[MAX_ITENS_VENDA];
    int       totalItens;
    float     valorTotal;

} Venda;

#endif
