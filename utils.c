#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

/* Lê uma linha de texto (aceita espaços) e remove o '\n' do final */
void lerTexto(char *dest, int tamanho) {
    scanf(" ");  /* pula o '\n' que sobra de um scanf anterior */
    fgets(dest, tamanho, stdin);

    /* Se nao veio o '\n', a linha era maior que o campo: o resto ficaria
       no teclado e seria lido pela proxima pergunta. Descarta. */
    if (strchr(dest, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    dest[strcspn(dest, "\n")] = '\0';
}

/* Lê uma linha que só pode ter digitos, com quantidade entre minimo e
   maximo; repete a pergunta ate vir certo. Usado em CPF e telefone. */
void lerDigitos(char *dest, int tamanho, int minimo, int maximo) {
    while (1) {
        char texto[50];
        int i, quantidade = 0, valido = 1;

        lerTexto(texto, sizeof(texto));

        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] < '0' || texto[i] > '9') {
                valido = 0;
                break;
            }
            quantidade++;
        }

        if (valido && quantidade >= minimo && quantidade <= maximo &&
            quantidade < tamanho) {
            strcpy(dest, texto);
            return;
        }

        if (minimo == maximo) {
            printf("Digite somente numeros, %d digitos: ", minimo);
        } else {
            printf("Digite somente numeros, de %d a %d digitos: ", minimo, maximo);
        }
    }
}

/* Metodo que faz a leitura do que foi digitado e descarta o que não é inteiro.
   Retorna -1 se não foi digitado um número (ex.: "abc"), para não ser
   confundido com a opção 0 dos menus */
int lerInteiro(void) {
    int valor;
    int c;
    if (scanf("%d", &valor) != 1) {
        valor = -1;
    }
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

/* Limpa o terminal. No Linux/Mac usa o codigo de controle do proprio
   terminal em vez de system("clear"): o "clear" depende da variavel TERM e
   nao funciona em todo lugar onde o programa roda. */
void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[2J\033[3J");
    fflush(stdout);
#endif
}

/* Espera o usuario apertar ENTER antes de seguir */
void pausar(void) {
    int c;
    printf("\nPressione ENTER para continuar...");
    while ((c = getchar()) != '\n' && c != EOF);
}
