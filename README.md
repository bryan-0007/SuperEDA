# SuperEDA
Este é um sistema de gerenciamento de armazém e setores para um supermercado. Com ele, é possível criar, gerenciar e imprimir informações sobre setores, armazém e produtos.

## Funções do Setor
- `sector criaSector(char letra, string responsavel, int capacidade, string area)`: cria um setor com a letra especificada, nome do responsável, capacidade e área.
- `void imprimeSectores(sector* s)`: imprime informações sobre todos os setores, incluindo a letra, responsável, capacidade, ocupação, área e produtos.
Funções do Armazém
- `void insereProduto(int quantidade, string nome[100], int tamanho_N, string fornecedores[50], int tamanho_F, RArea* area, armazem*Armazem)`: insere uma quantidade específica de produtos aleatórios no armazém.
- `produto criaProduto(string nome, string fornecedor, string area, int preco)`: cria um produto com o nome, fornecedor, área e preço especificados.
- `void insereArmazem(armazem* armazem, produto p)`: insere um produto no armazém.
- `void imprimeArmazem(armazem* A)`: imprime informações sobre todos os produtos no armazém, incluindo o nome, fornecedor, área e preço.
## Menu opção "s"
- `void vendaProdutos(sector* sectores)`: simula a venda de produtos em setores aleatórios com uma probabilidade específica.
## Menu opção "g"
- `void menu(armazem* a, sector* s, RArea* areas)`: exibe um menu com as opções de gerenciamento do sistema, incluindo remover produto, atualizar preço, iniciar campanha, gravar supermercado, carregar supermercado, imprimir produtos, criar nova área, mostrar registo de vendas e alterar área.