# SuperEDA
Este � um sistema de gerenciamento de armaz�m e setores para um supermercado. Com ele, � poss�vel criar, gerenciar e imprimir informa��es sobre setores, armaz�m e produtos.

## Fun��es do Setor
- `sector criaSector(char letra, string responsavel, int capacidade, string area)`: cria um setor com a letra especificada, nome do respons�vel, capacidade e �rea.
- `void imprimeSectores(sector* s)`: imprime informa��es sobre todos os setores, incluindo a letra, respons�vel, capacidade, ocupa��o, �rea e produtos.
Fun��es do Armaz�m
- `void insereProduto(int quantidade, string nome[100], int tamanho_N, string fornecedores[50], int tamanho_F, RArea* area, armazem*Armazem)`: insere uma quantidade espec�fica de produtos aleat�rios no armaz�m.
- `produto criaProduto(string nome, string fornecedor, string area, int preco)`: cria um produto com o nome, fornecedor, �rea e pre�o especificados.
- `void insereArmazem(armazem* armazem, produto p)`: insere um produto no armaz�m.
- `void imprimeArmazem(armazem* A)`: imprime informa��es sobre todos os produtos no armaz�m, incluindo o nome, fornecedor, �rea e pre�o.
## Menu op��o "s"
- `void vendaProdutos(sector* sectores)`: simula a venda de produtos em setores aleat�rios com uma probabilidade espec�fica.
## Menu op��o "g"
- `void menu(armazem* a, sector* s, RArea* areas)`: exibe um menu com as op��es de gerenciamento do sistema, incluindo remover produto, atualizar pre�o, iniciar campanha, gravar supermercado, carregar supermercado, imprimir produtos, criar nova �rea, mostrar registo de vendas e alterar �rea.