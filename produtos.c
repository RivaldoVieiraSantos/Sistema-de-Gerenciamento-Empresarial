#include <stdio.h>
#include "produtos.h"
#include "utils.h"

/* Armazenamento dos produtos */
static Produto produtos[MAX_PRODUTOS];
static int totalProdutos = 0;
static int proximoCodigo = 1;

/* Arquivo onde os produtos ficam salvos. Formato (texto, um produto por linha):
     1a linha: o proximo codigo a ser usado
     demais:   codigo;nome;categoria;preco;quantidade                          */
#define ARQUIVO_PRODUTOS "produtos.txt"

void salvarProdutos(void) {
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "w");

    if (arquivo == NULL) {
        printf("\nAtencao: nao foi possivel salvar em %s.\n", ARQUIVO_PRODUTOS);
        return;
    }

    fprintf(arquivo, "%d\n", proximoCodigo);

    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%d;%s;%s;%.2f;%d\n",
                produtos[i].codProduto,
                produtos[i].nomeProduto,
                produtos[i].categoriaProduto,
                produtos[i].precoProduto,
                produtos[i].quantidadeProduto);
    }

    fclose(arquivo);
}

/* Le os produtos do arquivo para a memoria. Chamada uma vez, quando o
   programa abre. Se o arquivo ainda nao existe, comeca sem produtos. */
void carregarProdutos(void) {
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    char linha[200];

    if (arquivo == NULL) {
        return;  /* primeira execucao: ainda nao ha arquivo */
    }

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d", &proximoCodigo);
    }

    totalProdutos = 0;
    while (totalProdutos < MAX_PRODUTOS && fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto *p = &produtos[totalProdutos];

        /* %49[^;] le ate 49 caracteres que nao sejam ';' (cabe no campo de 50) */
        int lidos = sscanf(linha, "%d;%49[^;];%49[^;];%f;%d",
                           &p->codProduto, p->nomeProduto, p->categoriaProduto,
                           &p->precoProduto, &p->quantidadeProduto);

        if (lidos == 5) {
            totalProdutos++;  /* so aceita linhas completas; ignora linhas quebradas */
        }
    }

    fclose(arquivo);
}

/* Le um texto do produto (nome, categoria). Troca ';' por ',' porque o
   ';' separa os campos no arquivo e quebraria a linha do produto. */
static void lerCampo(char *dest, int tamanho) {
    lerTexto(dest, tamanho);

    for (int i = 0; dest[i] != '\0'; i++) {
        if (dest[i] == ';') {
            dest[i] = ',';
        }
    }
}

/* Pede o preco ate vir um numero que nao seja negativo */
static float lerPreco(void) {
    while (1) {
        float preco = lerDecimal();

        if (preco >= 0) {
            return preco;
        }
        printf("Preco invalido. Digite um valor maior ou igual a zero: R$ ");
    }
}

/* Pede a quantidade ate vir um numero inteiro >= minimo */
static int lerQuantidade(int minimo) {
    while (1) {
        int quantidade = lerInteiro();

        if (quantidade >= minimo) {
            return quantidade;
        }
        printf("Quantidade invalida. Digite um numero maior ou igual a %d: ", minimo);
    }
}

/* Mostra os dados de um produto */
static void mostrarProduto(Produto p) {
    printf("Codigo:     %d\n", p.codProduto);
    printf("Nome:       %s\n", p.nomeProduto);
    printf("Categoria:  %s\n", p.categoriaProduto);
    printf("Preco:      R$ %.2f\n", p.precoProduto);
    printf("Estoque:    %d\n", p.quantidadeProduto);
}

/* Retorna a posicao do produto no vetor, ou -1 se nao existir */
static int procurarPorCodigo(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codProduto == codigo) {
            return i;
        }
    }
    return -1;
}

Produto *obterProduto(int codigo) {
    int i = procurarPorCodigo(codigo);

    if (i == -1) {
        return NULL;
    }
    return &produtos[i];
}

void cadastrarProduto(void) {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("\nLimite de %d produtos atingido.\n", MAX_PRODUTOS);
        return;
    }

    Produto novo;
    novo.codProduto = proximoCodigo;

    limparTela();
    printf("========================================\n");
    printf("      CADASTRAR PRODUTO (codigo %d)\n", novo.codProduto);
    printf("========================================\n");

    printf("Nome: ");
    lerCampo(novo.nomeProduto, sizeof(novo.nomeProduto));

    printf("Categoria: ");
    lerCampo(novo.categoriaProduto, sizeof(novo.categoriaProduto));

    printf("Preco: R$ ");
    novo.precoProduto = lerPreco();

    printf("Quantidade em estoque: ");
    novo.quantidadeProduto = lerQuantidade(1);

    produtos[totalProdutos] = novo;
    totalProdutos++;
    proximoCodigo++;
    salvarProdutos();

    printf("----------------------------------------\n");
    printf("Produto \"%s\" cadastrado com sucesso!\n", novo.nomeProduto);
    printf("----------------------------------------\n");
}

void listarProdutos(void) {
    limparTela();
    printf("========================================\n");
    printf("        LISTA DE PRODUTOS (%d)\n", totalProdutos);
    printf("========================================\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        if (i > 0) {
            printf("----------------------------------------\n");
        }
        mostrarProduto(produtos[i]);
    }

    printf("========================================\n");
}

void buscarProduto(void) {
    limparTela();
    printf("========================================\n");
    printf("            BUSCAR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("----------------------------------------\n");
    mostrarProduto(produtos[i]);
    printf("----------------------------------------\n");
}

void alterarProduto(void) {
    limparTela();
    printf("========================================\n");
    printf("            ALTERAR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    lerCampo(produtos[i].nomeProduto, sizeof(produtos[i].nomeProduto));

    printf("Nova categoria: ");
    lerCampo(produtos[i].categoriaProduto, sizeof(produtos[i].categoriaProduto));

    printf("Novo preco: R$ ");
    produtos[i].precoProduto = lerPreco();

    /* Aqui aceita 0: o estoque de um produto que ja existe pode ter acabado
       (no cadastro precisa ser pelo menos 1) */
    printf("Nova quantidade em estoque: ");
    produtos[i].quantidadeProduto = lerQuantidade(0);

    salvarProdutos();

    printf("----------------------------------------\n");
    printf("Produto alterado com sucesso!\n");
    printf("----------------------------------------\n");
}

void excluirProduto(void) {
    limparTela();
    printf("========================================\n");
    printf("            EXCLUIR PRODUTO\n");
    printf("========================================\n");

    printf("Digite o codigo do produto: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    /* Puxa os produtos seguintes uma posicao para tras */
    for (int j = i; j < totalProdutos - 1; j++) {
        produtos[j] = produtos[j + 1];
    }
    totalProdutos--;
    salvarProdutos();

    printf("----------------------------------------\n");
    printf("Produto excluido com sucesso!\n");
    printf("----------------------------------------\n");
}

/* Mostra uma linha da tabela de estoque */
static void mostrarLinhaEstoque(const Produto *p) {
    printf("%-6d %-24.24s %6d%s\n", p->codProduto, p->nomeProduto,
           p->quantidadeProduto,
           p->quantidadeProduto <= ESTOQUE_MINIMO ? "  (baixo)" : "");
}

void consultarEstoque(void) {
    limparTela();
    printf("========================================\n");
    printf("           CONSULTAR ESTOQUE\n");
    printf("========================================\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("%-6s %-24s %6s\n", "Codigo", "Produto", "Qtd");
    printf("----------------------------------------\n");

    for (int i = 0; i < totalProdutos; i++) {
        mostrarLinhaEstoque(&produtos[i]);
    }

    printf("========================================\n");
}

void listarEstoqueBaixo(void) {
    int encontrados = 0;

    limparTela();
    printf("========================================\n");
    printf("   PRODUTOS COM ESTOQUE BAIXO (<= %d)\n", ESTOQUE_MINIMO);
    printf("========================================\n");

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].quantidadeProduto <= ESTOQUE_MINIMO) {
            if (encontrados == 0) {
                printf("%-6s %-24s %6s\n", "Codigo", "Produto", "Qtd");
                printf("----------------------------------------\n");
            }
            mostrarLinhaEstoque(&produtos[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum produto com estoque baixo.\n");
    }

    printf("========================================\n");
}
