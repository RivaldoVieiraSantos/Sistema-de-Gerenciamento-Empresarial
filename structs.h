#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int codCliente;
    char nomeCliente[20];
    int CPFCliente;
    int telefoneCliente;
    char cidadeCliente[20];
    char emailCliente[20];

} Cliente;

typedef struct {
    int   codProduto;
    char  nomeProduto[50];
    char  categoriaProduto[50];
    float precoProduto;
    int   quantidadeProduto;

} Produto;

#endif
