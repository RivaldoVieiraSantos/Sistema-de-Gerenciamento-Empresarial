#include <stdio.h>
#include <time.h>
#include "vendas.h"
#include "clientes.h"
#include "produtos.h"
#include "utils.h"

/* Armazenamento das vendas */
static Venda vendas[MAX_VENDAS];
static int totalVendas = 0;
static int proximoCodigo = 1;

/* Arquivo onde as vendas ficam salvas. Formato (texto):
     1a linha: o proximo codigo a ser usado
     para cada venda, uma linha:  codigo;codCliente;data;totalItens;valorTotal
     e logo abaixo, uma por item: codProduto;quantidade;precoUnitario;nome     */
#define ARQUIVO_VENDAS "vendas.txt"

/* Grava todas as vendas no arquivo (reescreve o arquivo inteiro).
   E chamada depois de cada venda registrada. */
static void salvarVendas(void) {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "w");

    if (arquivo == NULL) {
        printf("\nAtencao: nao foi possivel salvar em %s.\n", ARQUIVO_VENDAS);
        return;
    }

    fprintf(arquivo, "%d\n", proximoCodigo);

    for (int i = 0; i < totalVendas; i++) {
        const Venda *v = &vendas[i];

        fprintf(arquivo, "%d;%d;%s;%d;%.2f\n",
                v->codVenda, v->codCliente, v->data, v->totalItens, v->valorTotal);

        for (int j = 0; j < v->totalItens; j++) {
            fprintf(arquivo, "%d;%d;%.2f;%s\n",
                    v->itens[j].codProduto,
                    v->itens[j].quantidade,
                    v->itens[j].precoUnitario,
                    v->itens[j].nomeProduto);
        }
    }

    fclose(arquivo);
}

/* Le as vendas do arquivo para a memoria. Chamada uma vez, quando o
   programa abre. Se o arquivo ainda nao existe, comeca sem vendas. */
void carregarVendas(void) {
    FILE *arquivo = fopen(ARQUIVO_VENDAS, "r");
    char linha[200];

    if (arquivo == NULL) {
        return;  /* primeira execucao: ainda nao ha arquivo */
    }

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d", &proximoCodigo);
    }

    totalVendas = 0;
    while (totalVendas < MAX_VENDAS && fgets(linha, sizeof(linha), arquivo) != NULL) {
        Venda *v = &vendas[totalVendas];

        int lidos = sscanf(linha, "%d;%d;%10[^;];%d;%f",
                           &v->codVenda, &v->codCliente, v->data,
                           &v->totalItens, &v->valorTotal);

        if (lidos != 5 || v->totalItens < 1 || v->totalItens > MAX_ITENS_VENDA) {
            continue;  /* linha quebrada: ignora */
        }

        /* Os itens vem nas linhas logo abaixo. O nome fica por ultimo e vai
           ate o fim da linha (\r aparece se o arquivo veio do Windows). */
        int completa = 1;
        for (int j = 0; j < v->totalItens; j++) {
            ItemVenda *item = &v->itens[j];

            if (fgets(linha, sizeof(linha), arquivo) == NULL ||
                sscanf(linha, "%d;%d;%f;%49[^\r\n]", &item->codProduto,
                       &item->quantidade, &item->precoUnitario, item->nomeProduto) != 4) {
                completa = 0;
                break;
            }
        }

        if (completa) {
            totalVendas++;  /* so aceita vendas com todos os itens */
        }
    }

    fclose(arquivo);
}

/* Soma o valor dos itens de forma recursiva: o total de n itens e o valor
   do ultimo item mais o total dos n-1 anteriores. Caso base: 0 itens = 0. */
static float somarItens(const ItemVenda *itens, int n) {
    if (n == 0) {
        return 0;
    }
    return itens[n - 1].quantidade * itens[n - 1].precoUnitario + somarItens(itens, n - 1);
}

/* Coloca a data de hoje em dest no formato dd/mm/aaaa */
static void dataDeHoje(char *dest, int tamanho) {
    time_t agora = time(NULL);
    strftime(dest, tamanho, "%d/%m/%Y", localtime(&agora));
}

/* Copia o nome do produto para o item. Troca ';' por ',' porque o ';'
   separa os campos no arquivo e quebraria a linha do item. */
static void copiarNome(char *dest, const char *origem, int tamanho) {
    int i;

    for (i = 0; i < tamanho - 1 && origem[i] != '\0'; i++) {
        dest[i] = (origem[i] == ';') ? ',' : origem[i];
    }
    dest[i] = '\0';
}

/* Mostra os dados de uma venda (recebe o endereco, sem copiar a struct) */
static void mostrarVenda(const Venda *v) {
    const Cliente *cliente = obterCliente(v->codCliente);

    printf("Venda:    %d\n", v->codVenda);
    printf("Data:     %s\n", v->data);
    printf("Cliente:  %d - %s\n", v->codCliente,
           cliente != NULL ? cliente->nomeCliente : "(cliente excluido)");
    printf("Itens:\n");

    for (int i = 0; i < v->totalItens; i++) {
        const ItemVenda *item = &v->itens[i];
        printf("  %d x %s (R$ %.2f cada) = R$ %.2f\n",
               item->quantidade, item->nomeProduto, item->precoUnitario,
               item->quantidade * item->precoUnitario);
    }

    printf("Total:    R$ %.2f\n", v->valorTotal);
}

int totalDeVendas(void) {
    return totalVendas;
}

const Venda *obterVendaPorPosicao(int i) {
    if (i < 0 || i >= totalVendas) {
        return NULL;
    }
    return &vendas[i];
}

/* Retorna a posicao da venda no vetor, ou -1 se nao existir */
static int procurarPorCodigo(int codigo) {
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codVenda == codigo) {
            return i;
        }
    }
    return -1;
}

/* Retorna a posicao do produto entre os itens da venda, ou -1 se ainda
   nao foi adicionado */
static int procurarItem(const Venda *v, int codProduto) {
    for (int i = 0; i < v->totalItens; i++) {
        if (v->itens[i].codProduto == codProduto) {
            return i;
        }
    }
    return -1;
}

/* Pede o codigo do cliente ate vir um que exista.
   Retorna o endereco do cliente, ou NULL se a pessoa digitou 0 (cancelar). */
static const Cliente *escolherCliente(void) {
    while (1) {
        printf("Codigo do cliente (0 para cancelar): ");
        int codigo = lerInteiro();

        if (codigo == 0) {
            return NULL;
        }

        const Cliente *cliente = obterCliente(codigo);
        if (cliente != NULL) {
            printf("Cliente: %s\n", cliente->nomeCliente);
            return cliente;
        }

        printf("Cliente nao encontrado. Tente novamente.\n");
    }
}

/* Adiciona produtos na venda ate a pessoa digitar 0.
   O estoque ainda nao muda aqui: so quando a venda for confirmada. */
static void adicionarItens(Venda *v) {
    while (1) {
        printf("\nCodigo do produto (0 para finalizar): ");
        int codigo = lerInteiro();

        if (codigo == 0) {
            return;
        }

        const Produto *produto = obterProduto(codigo);
        if (produto == NULL) {
            printf("Produto nao encontrado.\n");
            continue;
        }

        /* Se o produto ja esta na venda, desconta o que ja foi pedido */
        int i = procurarItem(v, codigo);
        int jaNaVenda = (i == -1) ? 0 : v->itens[i].quantidade;
        int disponivel = produto->quantidadeProduto - jaNaVenda;

        printf("Produto: %s | R$ %.2f | Disponivel: %d\n",
               produto->nomeProduto, produto->precoProduto, disponivel);

        if (disponivel <= 0) {
            printf("Sem estoque disponivel para este produto.\n");
            continue;
        }

        if (i == -1 && v->totalItens >= MAX_ITENS_VENDA) {
            printf("Limite de %d produtos diferentes por venda.\n", MAX_ITENS_VENDA);
            continue;
        }

        printf("Quantidade: ");
        int quantidade = lerInteiro();

        if (quantidade <= 0) {
            printf("A quantidade deve ser maior que zero.\n");
            continue;
        }

        if (quantidade > disponivel) {
            printf("Estoque insuficiente: so ha %d unidade(s) disponivel(is).\n", disponivel);
            continue;
        }

        if (i == -1) {
            i = v->totalItens;
            v->itens[i].codProduto = codigo;
            copiarNome(v->itens[i].nomeProduto, produto->nomeProduto,
                       sizeof(v->itens[i].nomeProduto));
            v->itens[i].quantidade = 0;
            v->itens[i].precoUnitario = produto->precoProduto;
            v->totalItens++;
        }
        v->itens[i].quantidade += quantidade;

        printf("Adicionado: %d x %s = R$ %.2f\n", quantidade, produto->nomeProduto,
               quantidade * produto->precoProduto);
    }
}

void registrarVenda(void) {
    if (totalVendas >= MAX_VENDAS) {
        printf("\nLimite de %d vendas atingido.\n", MAX_VENDAS);
        return;
    }

    Venda nova;
    nova.codVenda = proximoCodigo;
    nova.totalItens = 0;

    limparTela();
    printf("========================================\n");
    printf("       REGISTRAR VENDA (codigo %d)\n", nova.codVenda);
    printf("========================================\n");

    const Cliente *cliente = escolherCliente();
    if (cliente == NULL) {
        printf("\nVenda cancelada.\n");
        return;
    }
    nova.codCliente = cliente->codCliente;
    dataDeHoje(nova.data, sizeof(nova.data));

    adicionarItens(&nova);

    if (nova.totalItens == 0) {
        printf("\nVenda cancelada: nenhum produto foi adicionado.\n");
        return;
    }

    nova.valorTotal = somarItens(nova.itens, nova.totalItens);

    printf("\n========================================\n");
    printf("             RESUMO DA VENDA\n");
    printf("========================================\n");
    mostrarVenda(&nova);
    printf("----------------------------------------\n");
    printf("Confirma a venda? (1 - Sim / 0 - Nao): ");

    if (lerInteiro() != 1) {
        printf("\nVenda cancelada.\n");
        return;
    }

    /* Da baixa no estoque direto no produto, pelo endereco */
    for (int i = 0; i < nova.totalItens; i++) {
        Produto *produto = obterProduto(nova.itens[i].codProduto);
        produto->quantidadeProduto -= nova.itens[i].quantidade;
    }
    salvarProdutos();

    vendas[totalVendas] = nova;
    totalVendas++;
    proximoCodigo++;
    salvarVendas();

    printf("----------------------------------------\n");
    printf("Venda %d registrada com sucesso!\n", nova.codVenda);
    printf("----------------------------------------\n");
}

void listarVendas(void) {
    limparTela();
    printf("========================================\n");
    printf("         LISTA DE VENDAS (%d)\n", totalVendas);
    printf("========================================\n");

    if (totalVendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    for (int i = 0; i < totalVendas; i++) {
        if (i > 0) {
            printf("----------------------------------------\n");
        }
        mostrarVenda(&vendas[i]);
    }

    printf("========================================\n");
}

void buscarVenda(void) {
    limparTela();
    printf("========================================\n");
    printf("             BUSCAR VENDA\n");
    printf("========================================\n");

    printf("Digite o codigo da venda: ");
    int i = procurarPorCodigo(lerInteiro());

    if (i == -1) {
        printf("\nVenda nao encontrada.\n");
        return;
    }

    printf("----------------------------------------\n");
    mostrarVenda(&vendas[i]);
    printf("----------------------------------------\n");
}
