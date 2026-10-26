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

### Vendas

- codVenda
- codCliente
- data
- itens (até 20 produtos: codProduto, nomeProduto, quantidade, precoUnitario)
- totalItens
- valorTotal

### Estatísticas

- ( será entregue na próxima etapa do trabalho )

## Organização dos arquivos

| Arquivo        | Responsabilidade                                         |
| -------------- | -------------------------------------------------------- |
| `structs.h`    | structs compartilhadas (Cliente, Produto, ItemVenda, Venda) |
| `clientes.h/c` | módulo de clientes (cadastro, listagem, busca, alteração e exclusão) |
| `produtos.h/c` | módulo de produtos (cadastro, listagem, busca, alteração, exclusão e controle de estoque) |
| `vendas.h/c`   | módulo de vendas (registro, listagem e busca) |
| `utils.h/c`    | funções compartilhadas: leitura (lerTexto, lerInteiro, lerDecimal) e tela (limparTela, pausar) |
| `clientes.txt` | dados dos clientes: 1ª linha é o próximo código; depois `codigo;nome;cpf;telefone;cidade;email` |
| `produtos.txt` | dados dos produtos: 1ª linha é o próximo código; depois `codigo;nome;categoria;preco;quantidade` |
| `vendas.txt`   | dados das vendas: 1ª linha é o próximo código; cada venda é uma linha `codigo;codCliente;data;totalItens;valorTotal` seguida de uma linha por item `codProduto;quantidade;precoUnitario;nome` |
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
- [x] Consultar estoque — `consultarEstoque()`
- [x] Produtos com estoque baixo — `listarEstoqueBaixo()` (5 unidades ou menos: `ESTOQUE_MINIMO` em `produtos.h`)

### Vendas

- [x] Registrar — `registrarVenda()` (vários produtos por venda; confere se cliente e produto existem, não deixa vender mais que o estoque e dá baixa no estoque ao confirmar)
- [x] Listar — `listarVendas()`
- [x] Buscar por código — `buscarVenda()`
- O valor total é calculado de forma recursiva — `somarItens()` em `vendas.c`

### Observações

- O código do cliente e do produto é gerado automaticamente (1, 2, 3...).
- Não é permitido cadastrar dois clientes com o mesmo CPF.
- O preço aceita vírgula ou ponto (ex.: `3,50` ou `3.50`) e não pode ser negativo.
- A quantidade em estoque precisa ser pelo menos 1 no cadastro; na alteração aceita 0 (estoque acabou).
- Os clientes ficam salvos em `clientes.txt` (na pasta onde o programa roda) e são carregados ao abrir. Os produtos ficam em `produtos.txt` e as vendas em `vendas.txt`, do mesmo jeito.
- O repositório já traz 5 clientes fictícios em `clientes.txt` para testes. Para começar do zero, é só apagar o arquivo.
- Limite de 100 clientes (`MAX_CLIENTES` em `clientes.h`) e 100 produtos (`MAX_PRODUTOS` em `produtos.h`).

## Compilar

Linux/Mac:

```
gcc main.c clientes.c produtos.c vendas.c utils.c -o sistema
```

Windows:

```
gcc main.c clientes.c produtos.c vendas.c utils.c -o sistema.exe
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
