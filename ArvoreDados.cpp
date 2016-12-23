// ArvoreDados.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
 
using namespace std;

struct Dia {
	vector <int> data;
	vector <float> dado;
};
struct Info {
	int ID;
	int valor;
	Info() {}
	Info(int i, int v) { ID = i; valor = v; }
};
struct Noh {
	int label;
	std::vector<struct Info *>info;
	std::vector <struct Noh *> noh;
	Noh() {}
	Noh(std::vector<Info*> i, std::vector < Noh *> n, int l) :info(i), noh(n), label(l) {  }
};
Noh * preencheArvore(Dia *dia, int tamanho);
Noh * preencheMes(std::vector<Info*> info, Info *inf, int mes, int ncol);
Noh * preenche_ano(std::vector <struct Noh *> filhos_mes, std::vector<Info*> info, int ano, int ncol);
Noh * noh_vazio();
std::vector<Info*>  preencheDia(std::vector<Info*> info, int id, int value);
Noh * inicializa(std::vector<Info*> info, std::vector <struct Noh *> noh, int label);
vector <int> numCol(char * arq);
Dia * Dados(char * arq, int c);
int main()
{


	char * arq = "arv.dat";
	vector <int> n = numCol(arq);
	Dia * dados = Dados(arq, n.size());
	//este nó guarda a estrutura com valores  de dias/mes/ano estabelecidos no codigo;
	// é possivel visualizar a estrutura montada em modo debug com breakpoint  na variavel arvore abaixo:
	Noh * arvore = preencheArvore(dados, n.size());
	return 0;
}

Noh * noh_vazio() {
	return NULL;
}

Noh * inicializa(std::vector<Info*> i, std::vector <struct Noh *> n, int l) {
	Noh * p = new Noh(i, n, l);
	return p;
}

std::vector<Info*>  preencheDia(std::vector<Info*> info, int id, int value) {
	Info* inf;
	for (int i = 0; i <= id; i++) {//cria um conjunto de infos para o dia;
		inf = new Info(i + 1, value + i);
		info.push_back(inf);
	}
	return info;
}

Noh * preencheMes(std::vector<Info*> info, Info *inf, int mes, int ncol) {
	std::vector <struct Noh *> filhos_mes;
	std::vector <struct Noh *> filhos_null;

	int soma = 0;
	for (int k = 0; k < 4; k++) {//4 dias
		info = preencheDia(info, ncol, 200 + k);
		Noh * noh_dia = inicializa(info, filhos_null, 12 + k);
		info.clear();
		//filhos.clear();//already empty;
		filhos_mes.push_back(noh_dia);//filho do mes
	}
	

	for (int i = 0; i <= ncol; i++) { //
		for (int j = 0; j < (int)filhos_mes.size(); j++) {
			soma += filhos_mes.at(j)->info.at(i)->valor;
		}
		inf = new Info(filhos_mes.at(0)->info.at(i)->ID, soma); //
		info.push_back(inf);
		soma = 0;
	}
	Noh * noh_mes = inicializa(info, filhos_mes, mes);
	info.clear();
	filhos_mes.clear();

	
	return noh_mes;
}

Noh * preenche_ano(std::vector <struct Noh *> filhos_mes, std::vector<Info*> info, int ano, int ncol) {
	int soma = 0;
	Info* inf;
	for (int i = 0; i <= ncol; i++) { //
		for (int j = 0; j < (int)filhos_mes.size(); j++) {
			soma += filhos_mes.at(j)->info.at(i)->valor;
		}
		inf = new Info(filhos_mes.at(0)->info.at(i)->ID, soma); //
		info.push_back(inf);
		soma = 0;
	}

	return inicializa(info, filhos_mes, ano);
}
vector <int> numCol(char * arquivo) {
	int num;
	vector <int> numCol;
	ifstream arq;
	arq.open(arquivo);
	if (arq) {
		while (arq >> num)
		{

			numCol.push_back(num);
		}
		numCol.pop_back();
	}
	cout << "size: " << numCol.size() << endl;
	arq.close();
	return numCol;
}
Dia * Dados(char * arquivo, int c) {
	int num;
	float numf;
	char nume[25];
	Dia * dia = new Dia();
	string linha;
	vector <int> data;
	vector <float> dado;
	ifstream arq;
	arq.open(arquivo);
	if (arq) {
		getline(arq, linha);
		while (arq.good())
		{
			for (int j = 0; j < 3; j++) {
				arq.getline(nume, 256, '/');
				num = atoi(nume);
				data.push_back(num);
			}
			for (int i = 0; i < c; i++) {
				arq.getline(nume, 256, '/');
				numf = (float)atof(nume);

				dado.push_back(numf);
			}
			arq.ignore(1024, '\n');
			cout << "dados> " << num << endl;



		}
		dia->dado = dado;
		dia->data = data;
		//data.pop_back();
	}
	arq.close();
	cout << "size: " << dia->dado.size() << endl;
	return dia;
}

Noh * preencheArvore(Dia *dia, int ncol) {

	int d = 12, mes = 04, ano = 1989, soma = 0;
	
	std::vector <struct Noh *> filhos_mes;
	std::vector<Info*> info;

	Info* inf2 = new Info(0, 0);
	
	//---dia
	for (int km = 0; km < 2; km++) {//2 meses

		filhos_mes.push_back(preencheMes(info, inf2, mes + km, ncol));
	}

	//----ano--------
	Noh *noh_ano = preenche_ano(filhos_mes, info, ano, ncol);
	info.clear();
	filhos_mes.clear();
	return noh_ano;
}