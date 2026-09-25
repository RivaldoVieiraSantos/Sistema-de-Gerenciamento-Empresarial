# Sistema-de-Gerenciamento-Empresarial
Trabalho da Disciplina Algoritmos e Programação II

# Estrutura 
Clientes    
    - codCliente
    - nomeCliente
    - telefoneCliente
    - CPFCliente
    - cidadeCliente
    - emailCliente

Produtos
    - nomeProduto
    - codProduto
    - precoProduto
    - quantidadeProduto
    - categoriaProduto

Estatísticas 
    -
# Organização dos arquivos
    structs.h    -> structs compartilhadas (Cliente, Produto)
    clientes.h/c -> cadastro de clientes
    produtos.h/c -> CRUD de produtos
    utils.h/c    -> funcoes de leitura compartilhadas (lerTexto, lerInteiro)
    main.c       -> menu principal (só chama as funções dos módulos)

# Compilar
    gcc main.c clientes.c utils.c -o sistema
