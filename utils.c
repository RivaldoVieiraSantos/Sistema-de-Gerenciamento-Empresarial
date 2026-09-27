#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

/* Lê uma linha de texto (aceita espaços) e remove o '\n' do final */
void lerTexto(char *dest, int tamanho) {
    scanf(" ");  /* pula o '\n' que sobra de um scanf anterior */
    fgets(dest, tamanho, stdin);
    dest[strcspn(dest, "\n")] = '\0';
}

/* Metodo que faz a leitura do que foi digitado e descarta o que não é inteiro */
int lerInteiro(void) {
    int valor = 0;
    int c;
    scanf("%d", &valor);
    while ((c = getchar()) != '\n' && c != EOF);
    return valor;
}

/* Le um numero com casas decimais (ex.: preco).
   Aceita virgula ou ponto: 3,50 ou 3.50 */
float lerDecimal(void) {
    char texto[50];

    lerTexto(texto, sizeof(texto));

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }

    return atof(texto);
}
