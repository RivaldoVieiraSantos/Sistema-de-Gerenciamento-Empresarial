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
| `clientes.h/c` | módulo de clientes (cadastro, listagem, busca, alteração e exclusão) |
| `produtos.h/c` | módulo de produtos (cadastro, listagem, busca, alteração e exclusão) |
| `utils.h/c`    | funções compartilhadas: leitura (lerTexto, lerInteiro, lerDecimal) e tela (limparTela, pausar) |
| `clientes.txt` | dados dos clientes: 1ª linha é o próximo código; depois `codigo;nome;cpf;telefone;cidade;email` |
| `main.c`       | menus (só chama as funções dos módulos)                  |

## Funcionalidades

### Clientes

- [x] Cadastrar — `cadastrarCliente()`
- [x] Listar — `listarClientes()`
- [x] Buscar por código, nome ou CPF — `buscarCliente()` (nome aceita só uma parte, sem diferenciar maiúsculas)
- [x] Alterar — `alterarCliente()`
- [x] Excluir — `excluirCliente()` (pede confirmação)

### Produtos

- [x] Cadastrar — `cadastrarProduto()`
- [x] Listar — `listarProdutos()`
- [x] Buscar por código — `buscarProduto()`
- [x] Alterar — `alterarProduto()`
- [x] Excluir — `excluirProduto()`

### Observações

- O código do cliente e do produto é gerado automaticamente (1, 2, 3...).
- Não é permitido cadastrar dois clientes com o mesmo CPF.
- O preço aceita vírgula ou ponto (ex.: `3,50` ou `3.50`).
- Os clientes ficam salvos em `clientes.txt` (na pasta onde o programa roda) e são carregados ao abrir. Os produtos ainda ficam só na memória.
- O repositório já traz 5 clientes fictícios em `clientes.txt` para testes. Para começar do zero, é só apagar o arquivo.
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
