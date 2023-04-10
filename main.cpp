#include <iostream>
#include <locale>
#include <stdlib.h>
#include < time.h >
#include <string>
#include <fstream>

#include "SuperEDA.h"
#include "FuncoesFicheiros.h"


using namespace std;


int main() {
	armazem a;
	a.inicio = NULL;
	a.quantidade = 0;
	RArea* RAreas = new RArea;
	RAreas->tam = 0;

	locale::global(locale(""));

	//******************** Leitura de Ficheiros ********************

		// leitura áreas (linha a linha)
	fstream vA;
	vA.open("areas.txt", ios::in);
	string area[30];
	string linha;
	int tamanho_A = LinhasFicheiro("areas.txt");
	for (int i = 0; i < tamanho_A; i++) {
		getline(vA, linha);
		area[i] = linha;
	}

	// leitura nome (linha a linha)
	fstream vN;
	vN.open("nome.txt", ios::in);
	string nome[100];
	string linhaNome;
	int tamanho_N = LinhasFicheiro("nome.txt");

	for (int i = 0; i < tamanho_N; i++) {
		getline(vN, linhaNome);
		nome[i] = linhaNome;
	}

	//leitura fornecedores (linha a linha)
	fstream vF;
	vF.open("fornecedores.txt", ios::in);
	string fornecedores[50];
	string linhaFornecedores;
	int tamanho_F = LinhasFicheiro("fornecedores.txt");

	for (int i = 0; i < tamanho_F; i++) {
		getline(vF, linhaFornecedores);
		fornecedores[i] = linhaFornecedores;
	}

	//******************** Criação dos Sectores ********************

	srand(time(nullptr));
	int nSectores = rand() % 5 + 8;
	cout << "Supermarket size: " << nSectores << endl;
	char letra[] = { "ABCDEFGHIJKL" };

	sector s;
	s.inicio = NULL;

	for (int i = 0; i < nSectores; i++) {
		char sect = { letra[i] };
		string responsavel;
		int capacidade = rand() % 6 + 5;
		cout << "Introduza o responsável pelo sector " << letra[i] << ":" << endl;
		getline(cin, responsavel);
		int A = rand() % tamanho_A + 0;
		criaSector(s, sect, responsavel, capacidade, area[A], nSectores);
		RAreas->area[i] = area[A];
		RAreas->tam++;
	}
	
	imprimeSectores(s);

	//******************** Criação do Armazem ********************

	insereProduto(50, nome, tamanho_N, fornecedores, tamanho_F, RAreas, a);
	imprimeArmazem(a);

	//*************************** menu ***************************

	char opcao;
	bool sair = false;
	do
	{
		cout << "(s)-seguinte ******************** (g)-gestão ******************** (0)-Sair" << endl;
		cout << "Escolha uma opção:\n";
		cin >> opcao;
		cout << endl;
		switch (opcao) {
		case 's':
			vendaProdutos(s);
			atualiza(a, s);
			insereProduto(10, nome, tamanho_N, fornecedores, tamanho_F, RAreas, a);
			imprimeArmazem(a);
			break;
		case 'g':
			cout << "***** Bem Vindo ao Gestor *****" << endl;
			menu(a, s, RAreas);
			break;
		case '0':
			cout << "Escolheu a opção Sair. Adeus!" << endl;
			sair = true;
			break;
		default:
			cout << "Escolha uma opção válida." << endl;
		}
	} while (!sair);


	cin.get();
	cin.ignore();


	return 0;
}