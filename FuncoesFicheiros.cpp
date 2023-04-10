#include <iostream>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "FuncoesFicheiros.h"
#include "SuperEDA.h"

using namespace std;

int LinhasFicheiro(string Ficheiro) {
	int numLinhas = 0;
	ifstream in(Ficheiro);
	string linha;
	while (getline(in, linha)) {
		++numLinhas;
	}
	return numLinhas;
}