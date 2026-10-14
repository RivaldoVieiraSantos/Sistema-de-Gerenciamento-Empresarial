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

#endif
