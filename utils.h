#ifndef UTILS_H
#define UTILS_H

/* Funcoes de leitura do teclado, usadas por todos os modulos */
void lerTexto(char *dest, int tamanho);
void lerDigitos(char *dest, int tamanho, int minimo, int maximo);
int lerInteiro(void);
float lerDecimal(void);

/* Controle da tela */
void limparTela(void);
void pausar(void);

#endif
