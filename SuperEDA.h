#pragma once
#ifndef SUPEREDA_H
#define SUPEREDA_H

#include <iostream>
#include <string>
#include <locale>
#include <stdlib.h>
#include < time.h >
#include <fstream>
#include <sstream>
#include "FuncoesFicheiros.h"

using namespace std;

//******************** Criação das struct(s) ********************

struct produto {
	string nomeProduto;
	int preco;
	string area;
	string fornecedor;
	produto* seguinte;
};

struct vendido {
	string nome;
	int preco;
	vendido* esq;
	vendido* dir;
};

struct sector {
	int nSectores;
	struct sectores {
		char letra;
		string responsavel;
		int capacidade;
		int ocupacao;
		string area;
		produto* produtos;
		int produtosVendidos;
		vendido* vendidos;
		int duracao;
		int campanha;
		sectores* seguinte;
	};
	sectores* inicio;
};

struct armazem {
	int quantidade;
	produto* inicio;
};

struct RArea {
	string area[30];
	int tam;
};

//******************** Funções dos Sectores ********************

void criaSector(sector& s, char letra, string responsavel, int capacidade, string area, int nSectores);

void imprimeSectores(sector& s);

//******************** Funções do Armazem ********************

void insereProduto(int quantidade, string nome[100], int tamanho_N, string fornecedores[50], int tamanho_F, RArea* area, armazem& a);

void criaProduto(armazem& a, string nome, string fornecedor, string area, int preco);

void imprimeArmazem(armazem& a);

//******************** Funções Opção "s" ********************

void insereProdutoSector(produto* temp, sector& s);

void vendaProdutos(sector& s);

void insereProdutoVendido(produto* temp, sector& s, sector::sectores* iterator);

void removeProdutoSector(produto* temp, sector::sectores* iterator);

void atualiza(armazem& a, sector& s);

//******************** Funções do Gestor ********************

void menu(armazem& a, sector& s, RArea* areas);

void removerProduto(armazem& a, sector& s);

void atualizaPreco(armazem& a);

void campanha(sector& s, RArea* areas);

void gravaSupermercado(string caminho_sectores, string caminho_armazem, string caminho_registo, sector& s, armazem& a);

void travessiaPrefixa(vendido* no, string registo[500], int& i);

void carregarSupermercado(string caminho_sectores, string caminho_armazem, string caminho_registo, sector& s, armazem& a, RArea* areas);

void imprimeProdutos(sector& s, armazem& a);

void novaArea(RArea* areas);

void registoVendas(sector& s);

void travessiaInfixa(vendido* no);


#endif#pragma once