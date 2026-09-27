# Sistema de Gerenciamento Empresarial

Trabalho da Disciplina Algoritmos e Programação II

Repositório: https://github.com/RivaldoVieiraSantos/Sistema-de-Gerenciamento-Empresarial

## Estrutura

### Clientes

- codCliente
- nomeCliente
- telefoneCliente
- CPFCliente
- cidadeCliente
- emailCliente

### Produtos

- nomeProduto
- codProduto
- precoProduto
- quantidadeProduto
- categoriaProduto

### Estatísticas

- ( será entregue na próxima etapa do trabalho )

## Organização dos arquivos

| Arquivo        | Responsabilidade                                         |
| -------------- | -------------------------------------------------------- |
| `structs.h`    | structs compartilhadas (Cliente, Produto)                |
| `clientes.h/c` | módulo de clientes (cadastro e listagem)                 |
| `produtos.h/c` | módulo de produtos (cadastro, listagem, busca, alteração e exclusão) |
| `utils.h/c`    | funções de leitura compartilhadas (lerTexto, lerInteiro) |
| `main.c`       | menus (só chama as funções dos módulos)                  |

## Funcionalidades

### Clientes

- [x] Cadastrar — `cadastrarCliente()`
- [x] Listar — `listarClientes()`
- [ ] Buscar por código
- [ ] Alterar
- [ ] Excluir

### Produtos

- [x] Cadastrar — `cadastrarProduto()`
- [x] Listar — `listarProdutos()`
- [x] Buscar por código — `buscarProduto()`
- [x] Alterar — `alterarProduto()`
- [x] Excluir — `excluirProduto()`

### Observações

- O código do cliente e do produto é gerado automaticamente (1, 2, 3...).
- O preço aceita vírgula ou ponto (ex.: `3,50` ou `3.50`).
- Os dados ficam só na memória: somem quando o programa fecha.
- Limite de 100 clientes (`MAX_CLIENTES` em `clientes.h`) e 100 produtos (`MAX_PRODUTOS` em `produtos.h`).

## Compilar

Linux/Mac:

```
gcc main.c clientes.c produtos.c utils.c -o sistema
```

Windows:

```
gcc main.c clientes.c produtos.c utils.c -o sistema.exe
```

## Executar

Linux/Mac:

```
./sistema
```

Windows:

```
sistema.exe
```
