#include "SuperEDA.h"

using namespace std;

//*************************************** Funções Sector ***************************************

void criaSector(sector& s,char letra, string responsavel, int capacidade, string area, int nSectores) {
	s.nSectores = nSectores;
	sector::sectores* novo = new sector::sectores();
	novo->letra = letra;
	novo->responsavel = responsavel;
	novo->capacidade = capacidade;
	novo->area = area;
	novo->ocupacao = 0;
	novo->campanha = 0;
	novo->duracao = 0;
	novo->produtosVendidos = 0;
	novo->produtos = NULL;
	novo->vendidos = NULL;
	novo->seguinte = NULL;
	if (s.inicio == NULL) {
		s.inicio = novo;
	}
	else {
		sector::sectores* iterator = s.inicio;
		while(iterator->seguinte != 0){
			iterator = iterator->seguinte;
		}
		iterator->seguinte = novo;
	}
}

void imprimeSectores(sector& s) {
	sector::sectores* iterator = s.inicio;
	while(iterator != 0){
		cout << "Sector: " << iterator->letra << "  ||  " << "Responsável: " << iterator->responsavel << "  ||  " << "Capacidade: " << iterator->capacidade << "  ||  " << "Ocupação: " << iterator->ocupacao << "  ||  " << "Área: " << iterator->area << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		produto* iteratorP = iterator->produtos;
		while (iteratorP != 0) {
			cout << "Produto: " << iteratorP->nomeProduto << "  ||  " << "Fornecedor: " << iteratorP->fornecedor << "  ||  " << "Área: " << iteratorP->area << "  ||  " << "Preço: " << iteratorP->preco - iteratorP->preco * iterator->campanha / 100 << endl;
			iteratorP = iteratorP->seguinte;
		}
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		iterator = iterator->seguinte;
	}
	cout << endl;
}

//*************************************** Funções Armazem ***************************************

void insereProduto(int quantidade, string nome[100], int tamanho_N, string fornecedores[50], int tamanho_F, RArea* area, armazem& a) {
	for (int j = 0; j < quantidade; j++) {
		int N = rand() % tamanho_N + 0;
		int F = rand() % tamanho_F + 0;
		int A = rand() % area->tam + 0;
		int preco = 1;
		while (preco % 2 != 0) {
			preco = rand() % 80 + 1;
		}
		criaProduto(a, nome[N], fornecedores[F], area->area[A], preco);
	}
}

void criaProduto(armazem& a, string nome, string fornecedor, string area, int preco) {
	produto* novo = new produto();
	novo->nomeProduto = nome;
	novo->fornecedor = fornecedor;
	novo->area = area;
	novo->preco = preco;
	novo->seguinte = NULL;
	if (a.inicio == NULL) {
		a.inicio = novo;
		a.quantidade++;
	}
	else {
		produto* iterator = a.inicio;
		while (iterator->seguinte != 0) {
			iterator = iterator->seguinte;
		}
		iterator->seguinte = novo;
		a.quantidade++;
	}
}


void imprimeArmazem(armazem& a) {
	produto* iterator = a.inicio;
	cout << "O armazém contém: " << a.quantidade << " produtos" << endl;
	while (iterator != 0) {
		cout << "Produto: " << iterator->nomeProduto << "  ||  " << "Fornecedor: " << iterator->fornecedor << "  ||  " << "Área: " << iterator->area << "  ||  " << "Preço: " << iterator->preco << endl;
		iterator = iterator->seguinte;
	}
	cout << endl;
}

//*************************************** Menu opção "s" ***************************************

void vendaProdutos(sector& s) {

	sector::sectores* iterator = s.inicio;
	while (iterator != 0) {
		if (iterator->duracao == 0) {
			iterator->campanha = 0;
		}
		if (iterator->duracao > 0) {
			iterator->duracao--;
		}
		iterator = iterator->seguinte;
	}

	iterator = s.inicio;

	cout << "Produtos vendidos:" << endl;
	while (iterator != 0) {
		produto* iteratorP = iterator->produtos;
		bool segundoP = false;
		while (iteratorP != 0 && segundoP == false) {
			int probalidade = rand() % 101;
			if (probalidade < 26) {
				if (iteratorP->seguinte == 0) {
					produto* temp = iteratorP;
					iteratorP = NULL;
					temp->seguinte = NULL;
					iterator->produtos = iteratorP;
					insereProdutoVendido(temp, s, iterator);
					removeProdutoSector(temp, iterator);
					iterator->produtosVendidos++;
					iterator->ocupacao--;
				}
				else {
					produto* temp = iteratorP;
					iteratorP = temp->seguinte;
					temp->seguinte = NULL;
					iterator->produtos = iteratorP;
					insereProdutoVendido(temp, s, iterator);
					removeProdutoSector(temp, iterator);
					iterator->produtosVendidos++;
					iterator->ocupacao--;
				}
			}
			else {
				segundoP = true;
			}
		}
		iteratorP = iterator->produtos;
		while (segundoP == true && iteratorP->seguinte != 0) {
			int probalidade = rand() % 101;
			if (probalidade < 26) {
				if (iteratorP->seguinte->seguinte == 0) {
					produto* temp = iteratorP->seguinte;
					iteratorP->seguinte = NULL;
					temp->seguinte = NULL;
					insereProdutoVendido(temp, s, iterator);
					removeProdutoSector(temp, iterator);
					iterator->produtosVendidos++;
					iterator->ocupacao--;
				}
				else {
					produto* temp = iteratorP->seguinte;
					iteratorP->seguinte = temp->seguinte;
					temp->seguinte = NULL;
					insereProdutoVendido(temp, s, iterator);
					removeProdutoSector(temp, iterator);
					iterator->produtosVendidos++;
					iterator->ocupacao--;
				}
			}
			if (iteratorP->seguinte != 0) {
				iteratorP = iteratorP->seguinte;
			}
			else {
				segundoP = false;
			}
		}
		iterator = iterator->seguinte;
	}
	cout << endl << endl;
}

void insereProdutoVendido(produto* temp, sector& s, sector::sectores* iterator) {
	sector::sectores* iteratorS = s.inicio;
	iteratorS = iterator;
	vendido* iteratorV = iteratorS->vendidos;
	bool colocado = false;
	vendido* novo = new vendido();
	novo->nome = temp->nomeProduto;
	novo->preco = temp->preco;
	novo->dir = NULL;
	novo->esq = NULL;
	while (colocado == false) {
		if (iteratorV == 0){
			iteratorV = novo;
			colocado = true;
			iteratorS->vendidos = iteratorV;
		}
		else if (iteratorV->preco < temp->preco) {
			if (iteratorV->dir == NULL) {
				iteratorV->dir = novo;
				colocado = true;
			}
			else {
				iteratorV = iteratorV->dir;
			}
		}
		else if (iteratorV->preco >= temp->preco) {
			if (iteratorV->esq == NULL) {
				iteratorV->esq = novo;
				colocado = true;
			}
			else {
				iteratorV = iteratorV->esq;
			}
		}
	}

}

void removeProdutoSector(produto* temp, sector::sectores* iterator) {
	cout << "O produto " << temp->nomeProduto << " foi vendido por " << temp->preco - temp->preco * iterator->campanha / 100 << "." << endl;
}



void atualiza(armazem& a, sector& s) {
	int quantidade = 0;
	bool prioridade = false;
	produto* iterator = a.inicio;
	
	
	while (quantidade < 10 && iterator->seguinte != 0) {
		bool produtoInserido = false;
		if (prioridade == false) {
			sector::sectores* iteratorS = s.inicio;
			while (iteratorS != 0 && produtoInserido == false) {
				if (iteratorS->area == iterator->area) {
					if (iteratorS->ocupacao < iteratorS->capacidade) {
						produto* temp = iterator;
						iterator = temp->seguinte;
						temp->seguinte = NULL;
						a.inicio = iterator;
						quantidade++;
						insereProdutoSector(temp, s);
						a.quantidade--;
						produtoInserido = true;
					}
				}
				iteratorS = iteratorS->seguinte;
			}
		}
		if (produtoInserido == false) {
			prioridade = true;
		}
		if (prioridade == true) {
			sector::sectores* iteratorS = s.inicio;
			produto* temp = iterator->seguinte;
			while (iteratorS != 0 && produtoInserido == false) {
				if (iteratorS->area == temp->area) {
					if (iteratorS->ocupacao < iteratorS->capacidade) {
						iterator->seguinte = temp->seguinte;
						temp->seguinte = NULL;
						quantidade++;
						insereProdutoSector(temp, s);
						a.quantidade--;
						produtoInserido = true;
					}
				}
				iteratorS = iteratorS->seguinte;
			}
		}
		if (produtoInserido == false) {
			iterator = iterator->seguinte;
		}
	}

	imprimeSectores(s);
}

void insereProdutoSector(produto* temp, sector& s) {
	sector::sectores* iterator = s.inicio;
	bool produtoInserido = false;
	while(iterator != 0 && produtoInserido == false){
		if (iterator->area == temp->area) {
			if (iterator->ocupacao < iterator->capacidade) {
				temp->seguinte = iterator->produtos;
				iterator->produtos = temp;
				iterator->ocupacao++;
				produtoInserido = true;
			}
		}
		iterator = iterator->seguinte;
	}

}


//*************************************** Menu opção "g" ***************************************
//******************** Gestor ********************

void menu(armazem& a, sector& s, RArea* areas) {
	bool sair = false;
	char opcao;
	do
	{
		cout << "\nEscolha uma opção:\n";
		cout << "1 - Remover Produto" << endl;
		cout << "2 - Atualizar Preço" << endl;
		cout << "3 - Iniciar Campanha" << endl;
		cout << "4 - Gravar Supermercado" << endl;
		cout << "5 - Carregar Supermercado" << endl;
		cout << "6 - Imprimir Produtos" << endl;
		cout << "7 - Criar nova área" << endl;
		cout << "8 - Mostrar Registo de Vendas" << endl;
		cout << "0 - voltar" << endl;
		cin >> opcao;
		cout << endl;
		switch (opcao) {
		case '1':
			cout << "Escolheu a opção Remover Produto" << endl;
			removerProduto(a, s);
			break;
		case '2':
			cout << "Escolheu a opção Atualizar Preço" << endl;
			atualizaPreco(a);
			break;
		case '3':
			cout << "Escolheu a opção Iniciar Campanha" << endl;
			campanha(s, areas);
			break;
		case '4':
			cout << "Escolheu a opção Gravar Supermercado" << endl;
			gravaSupermercado("sectores.txt", "armazem.txt", "registo.txt", s, a);
			break;
		case '5':
			cout << "Carregar Supermercado" << endl;
			carregarSupermercado("sectores.txt", "armazem.txt", "registo.txt", s, a, areas);
			break;
		case '6':
			cout << "Escolheu a opção Imprimir Produtos" << endl;
			imprimeProdutos(s, a);
			break;
		case '7':
			cout << "Escolheu a opção Criar nova área" << endl;
			novaArea(areas);
			break;
		case '8':
			cout << "Escolheu a opção Mostrar Registo de Vendas" << endl;
			registoVendas(s);
			break;
		case '0':
			cout << "Escolheu a opção voltar" << endl;
			sair = true;
			break;
		default:
			cout << "Escolha uma opção válida." << endl;
		}
	} while (!sair);
}

	//******************************* Opção Gestor *******************************

//************************** 1 **************************

	void removerProduto(armazem& a, sector& s) {
		string prod;
		cout << "Escreva o nome do produto a ser removido: " << endl;
		cin.get();
		getline(cin, prod);
		cout << endl;
		sector::sectores* iterator = s.inicio;
		while (iterator != 0) {
			produto* iteratorP = iterator->produtos;
			bool segundoP = false;
			while (iteratorP != 0 && segundoP == false) {
				if (iteratorP->nomeProduto == prod) {
					if (iteratorP->seguinte == 0) {
						iteratorP = NULL;
						iterator->produtos = iteratorP;
						iterator->ocupacao--;
					}
					else {
						produto* temp = iteratorP;
						iteratorP = temp->seguinte;
						temp->seguinte = NULL;
						iterator->produtos = iteratorP;
						iterator->ocupacao--;
					}
				}
				else {
					segundoP = true;
				}
			}
			iteratorP = iterator->produtos;
			while (segundoP == true && iteratorP->seguinte != 0) {
				if (iteratorP->seguinte->nomeProduto == prod) {
					if (iteratorP->seguinte->seguinte == 0) {
						iteratorP->seguinte = NULL;
						iterator->ocupacao--;
					}
					else {
						produto* temp = iteratorP->seguinte;
						iteratorP->seguinte = temp->seguinte;
						temp->seguinte = NULL;
						iterator->ocupacao--;
					}
				}
				if (iteratorP->seguinte != 0) {
					iteratorP = iteratorP->seguinte;
				}
				else {
					segundoP = false;
				}
			}
			iterator = iterator->seguinte;
		}

		bool primeiro = true;
		produto* iteratorA = a.inicio;

		while (iteratorA->seguinte != 0) {
			bool produtoRemovido = false;
			if (primeiro == true) {
				if (iteratorA->nomeProduto == prod) {
					produto* temp = iteratorA;
					iteratorA = temp->seguinte;
					temp->seguinte = NULL;
					a.inicio = iteratorA;
					a.quantidade--;
					produtoRemovido = true;
				}
			}
			if (produtoRemovido == false) {
				primeiro = false;
			}
			if (primeiro == false) {
				produto* temp = iteratorA->seguinte;
				if (temp->nomeProduto == prod) {
					iteratorA->seguinte = temp->seguinte;
					temp->seguinte = NULL;
					a.quantidade--;
					produtoRemovido = true;
				}
			}
			if (produtoRemovido == false) {
				iteratorA = iteratorA->seguinte;
			}
		}

		cout << endl << endl;
		imprimeSectores(s);
		imprimeArmazem(a);
		cout << endl << "produto " << prod << " removido!!" << endl << endl;
	}

	//************************** 2 **************************

	void atualizaPreco(armazem& a) {
		string prod;
		int novoPreco;
		cout << "Escreva o nome do produto a alterar preço: " << endl;
		cin.get();
		getline(cin, prod);
		cout << "Escreva o novo preço: " << endl;
		cin >> novoPreco;

		produto* iteratorA = a.inicio;
		while (iteratorA != 0) {	
			if (iteratorA->nomeProduto == prod) {
				iteratorA->preco = novoPreco;
			}
			iteratorA = iteratorA->seguinte;
		}

		imprimeArmazem(a);
		cout << endl << "Foi atualizado o preço do produto " << prod << "." << endl << endl;
	}

	//************************** 3 **************************

	void campanha(sector& s, RArea* areas) {
		string area;
		int desconto;
		int duracao;
		cout << "Escreva a área para efetuar a campanha: " << endl;
		cin.get();
		getline(cin, area);
		bool existe = false;
		for (int i = 0; i < areas->tam; i++) {
			if (areas->area[i] == area) {
				existe = true;
			}
		}
		if (existe == true) {
			cout << "Indique a percentagem de desconto (0 - 100): " << endl;
			cin >> desconto;
			while (desconto > 100 || desconto < 0) {
				cout << "Indique novamente a percentagem de desconto entre 0 à 100: " << endl;
				cin >> desconto;
			}
			cout << "Escreva a duração da campanha (ciclos): " << endl;
			cin >> duracao;

			sector::sectores* iterator = s.inicio;
			while (iterator !=0 ) {
				if (iterator->area == area) {
					iterator->campanha = desconto;
					iterator->duracao = duracao;
				}
				iterator = iterator->seguinte;
			}
			imprimeSectores(s);
			cout << endl << "Campanha iniciada" << endl << endl;
		}
		else {
			cout << endl << "Não existe sector com o nome de área " << area << "." << endl;
		}
	}

	//************************** 4 **************************

	void gravaSupermercado(string caminho_sectores, string caminho_armazem, string caminho_registo, sector& s, armazem& a) {
		sector::sectores* iterator = s.inicio;
		fstream fs;
		fs.open(caminho_sectores, ifstream::out);
		fs << s.nSectores << endl;

		while (iterator != 0) {
			fs << iterator->letra << endl;
			fs << iterator->responsavel << endl;
			fs << iterator->capacidade << endl;
			fs << iterator->ocupacao << endl;
			fs << iterator->area << endl;
			fs << iterator->campanha << endl;
			fs << iterator->duracao << endl;
			fs << iterator->produtosVendidos << endl;
			produto* iteratorP = iterator->produtos;
			while (iteratorP != 0) {
				fs << iteratorP->area << endl;
				fs << iteratorP->fornecedor << endl;
				fs << iteratorP->nomeProduto << endl;
				fs << iteratorP->preco << endl;
				iteratorP = iteratorP->seguinte;
			}
			iterator = iterator->seguinte;
		}
		
		fs.close();

		produto* iteratorA = a.inicio;
		fstream fa;
		fa.open(caminho_armazem, ifstream::out);
		fa << a.quantidade << endl;
		while (iteratorA != 0) {
			fa << iteratorA->area << endl;
			fa << iteratorA->fornecedor << endl;
			fa << iteratorA->nomeProduto << endl;
			fa << iteratorA->preco << endl;
			iteratorA = iteratorA->seguinte;
		}
		fa.close();

		string* registo = new string[500];
		fstream fr;
		fr.open(caminho_registo, ifstream::out);
		iterator = s.inicio;
		while (iterator != 0) {
			int i = 0;
			vendido* iteratorV = iterator->vendidos;
			travessiaPrefixa(iteratorV, registo, i);
			iterator = iterator->seguinte;
			for (int j = 0; j < i; j++){
				fr << registo[j] << endl;
			}
		}
		fr.close();

		cout << endl << "Supermercado gravado com sucesso!!" << endl;
	}
	void travessiaPrefixa(vendido* no, string registo[500], int& i) {
		if (no == NULL) {
			return;
		}
		registo[i] = no->nome;
		i++;
		registo[i] = to_string(no->preco);
		i++;
		cout << "produto: " << no->nome << " || preço: " << no->preco << endl;
		travessiaPrefixa(no->esq, registo, i);
		travessiaPrefixa(no->dir, registo, i);
	}

	//************************** 5 **************************

	void carregarSupermercado(string caminho_sectores, string caminho_armazem, string caminho_registo, sector& s, armazem& a, RArea* areas) {
		fstream fs;
		fs.open(caminho_sectores, ios::in);
		string linha;
		string sectores[500];
		int tamanho = LinhasFicheiro(caminho_sectores);
		for (int i = 0; i < tamanho; i++) {
			getline(fs, linha);
			sectores[i] = linha;
		}
		int tamSectores;
		stringstream t(sectores[0]);
		t >> tamSectores;
		s.nSectores = tamSectores;
		cout << "Sectores: " << tamSectores << endl;
		areas->tam = 0;
		int pos = 1;

		s.inicio = NULL;
		for (int i = 0; i < tamSectores; i++) {
			sector::sectores* novo = new sector::sectores();
			char c_string = sectores[pos].at(0); // conversão para tipo char
			novo->letra = c_string;
			pos++;
			novo->responsavel = sectores[pos];
			pos++;
			stringstream cap(sectores[pos]); // conversão para tipo inteiro
			cap >> novo->capacidade;
			pos++;
			stringstream ocp(sectores[pos]); // conversão para tipo inteiro
			ocp >> novo->ocupacao;
			pos++;
			novo->area = sectores[pos];
			areas->area[areas->tam] = sectores[pos];
			areas->tam++;
			pos++;
			stringstream camp(sectores[pos]); // conversão para tipo inteiro
			camp >> novo->campanha;
			pos++;
			stringstream duracao(sectores[pos]); // conversão para tipo inteiro
			duracao >> novo->duracao;
			pos++;
			stringstream prodVend(sectores[pos]); // conversão para tipo inteiro
			prodVend >> novo->produtosVendidos;
			pos++;
			novo->produtos = NULL;
			for (int i = 0; i < novo->ocupacao; i++) {
				produto* iteratorP = new produto();
				iteratorP->area = sectores[pos];
				pos++;
				iteratorP->fornecedor = sectores[pos];
				pos++;
				iteratorP->nomeProduto = sectores[pos];
				pos++;
				stringstream preco(sectores[pos]); // conversão para tipo inteiro
				preco >> iteratorP->preco;
				pos++;
				iteratorP->seguinte == NULL;
				if (novo->produtos == NULL) {
					novo->produtos = iteratorP;
				}
				else {
					produto* temp = novo->produtos;
					while (temp->seguinte != NULL) {
						temp = temp->seguinte;
					}
					temp->seguinte = iteratorP;
				}
			}	
			novo->vendidos = NULL;
			novo->seguinte = NULL;
			if (s.inicio == NULL) {
				s.inicio = novo;
			}
			else {
				sector::sectores* iterator = s.inicio;
				while (iterator->seguinte != 0) {
					iterator = iterator->seguinte;
				}
				iterator->seguinte = novo;
			}
		}


		fs.close();

		fstream fa;
		fa.open(caminho_armazem, ios::in);
		string armazem[500];
		int tamanhoA = LinhasFicheiro(caminho_armazem);
		for (int i = 0; i < tamanhoA; i++) {
			getline(fa, linha);
			armazem[i] = linha;
		}
		int tamArmazem;
		stringstream ca(armazem[0]);
		ca >> tamArmazem;
		pos = 1;
		a.quantidade = tamArmazem;
		a.inicio = NULL;
		for (int i = 0; i < a.quantidade; i++) {
			produto* novo = new produto();
			novo->area = armazem[pos];
			pos++;
			novo->fornecedor = armazem[pos];
			pos++;
			novo->nomeProduto = armazem[pos];
			pos++;
			stringstream preco(armazem[pos]); // conversão para tipo inteiro
			preco >> novo->preco;
			pos++;
			if (a.inicio == NULL) {
				a.inicio = novo;
			}
			else {
				produto* iterator = a.inicio;
				while (iterator->seguinte != 0) {
					iterator = iterator->seguinte;
				}
				iterator->seguinte = novo;
			}
		}
		fa.close();


		fstream fr;
		fr.open(caminho_registo, ios::in);
		string registo[500];
		int tamanhoR = LinhasFicheiro(caminho_registo);
		for (int i = 0; i < tamanhoR; i++) {
			getline(fr, linha);
			registo[i] = linha;
		}
		pos = 0;

		sector::sectores* iterator = s.inicio;
		while (iterator != 0) {
			for (int i = 0; i < iterator->produtosVendidos; i++) {
				vendido* novo = new vendido();
				novo->nome = registo[pos];
				pos++;
				stringstream pVendidos(registo[pos]); // conversão para tipo inteiro
				pVendidos >> novo->preco;
				pos++;
				novo->dir = NULL;
				novo->esq = NULL;
				vendido* iteratorV = iterator->vendidos;
				bool colocado = false;
				while (colocado == false) {
					if (iteratorV == 0) {
						iteratorV = novo;
						colocado = true;
						iterator->vendidos = iteratorV;
					}
					else if (iteratorV->preco < novo->preco) {
						if (iteratorV->dir == NULL) {
							iteratorV->dir = novo;
							colocado = true;
						}
						else {
							iteratorV = iteratorV->dir;
						}
					}
					else if (iteratorV->preco >= novo->preco) {
						if (iteratorV->esq == NULL) {
							iteratorV->esq = novo;
							colocado = true;
						}
						else {
							iteratorV = iteratorV->esq;
						}
					}
				}
			}
			iterator = iterator->seguinte;
		}
		fr.close();

		imprimeSectores(s);
		imprimeArmazem(a);

		cout << endl << "Supermercado carregado com sucesso!!" << endl;
	}

	//************************** 6 **************************
	
	void imprimeProdutos(sector& s, armazem& a) {
		cout << "Produtos presentes no supermercado: " << endl;
		sector::sectores* iterator = s.inicio;
		while (iterator != 0) {
			produto* iteratorP = iterator->produtos;
			while (iteratorP != 0) {
				cout << iteratorP->nomeProduto << endl;
				iteratorP = iteratorP->seguinte;
			}
			iterator = iterator->seguinte;
		}
		produto* iteratorA = a.inicio;
		while (iteratorA != 0) {
			cout << iteratorA->nomeProduto << endl;
			iteratorA = iteratorA->seguinte;
		}
		cout << endl;

	}
	//************************** 7 **************************

	void novaArea(RArea* areas) {
		string novaArea;
		cout << endl << "Escreva o nome da nova área que pretende criar: " << endl;
		cin.get();
		getline(cin, novaArea);
		areas->area[areas->tam] = novaArea;
		areas->tam++;
		cout << endl << "Nova área criada!!" << endl << endl;
	}

	//************************** 8 **************************

	void registoVendas(sector& s) {
		sector::sectores* iterator = s.inicio;
		string nome;
		cout << "Escreva o nome do responsável do sector para aceder ao seu registo de vendas: " << endl;
		cin.get();
		getline(cin, nome);
		bool existe = false;
		while (iterator != 0) {
			if (iterator->responsavel == nome) {
				cout << "O sector reponsável por " << nome << " vendeu " << iterator->produtosVendidos << " produtos." << endl;
				vendido* iteratorV = iterator->vendidos;
				travessiaInfixa(iteratorV);
				existe = true;
			}
			iterator = iterator->seguinte;
		}
		if (existe == false) {
			cout << "Não existe nenhum responsável de sector com o nome: " << nome << endl;
		}
		cout << endl;
	}

	void travessiaInfixa(vendido* no) {
		if (no == NULL) {
			return;
		}
		travessiaInfixa(no->esq);
		cout << "produto: " << no->nome << " || preço: " << no->preco << endl;
		travessiaInfixa(no->dir);
	}