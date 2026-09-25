# Sistema de Gerenciamento Empresarial

Trabalho da Disciplina Algoritmos e Programação II

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
| `produtos.h/c` | módulo de produtos (a fazer)                             |
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

- [ ] Cadastrar
- [ ] Listar
- [ ] Buscar por código
- [ ] Alterar
- [ ] Excluir

### Observações

- O código do cliente é gerado automaticamente (1, 2, 3...).
- Os dados ficam só na memória: somem quando o programa fecha.
- Limite de 100 clientes (`MAX_CLIENTES` em `clientes.h`).

## Compilar

```
gcc main.c clientes.c utils.c -o sistema
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
