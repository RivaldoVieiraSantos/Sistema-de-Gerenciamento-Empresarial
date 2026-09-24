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
    char nomeProduto[20];
    int  codProduto;
    int  precoProduto;
    int  quantidadeProduto;
    char categoriaProduto;

} Produto;

#endif
