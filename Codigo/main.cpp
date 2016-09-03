//
//  analyzer.cpp
//  Implementation of the netList class to be used in the main program.
//
//	WINODWS: g++ -std=c++11 -Wall -o main main.cpp analyzer.cpp elements.cpp
//	LINUX: g++ -std=c++0x -Wall -D NOT_WINDOWS -o main main.cpp analyzer.cpp elements.cpp
//  

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#ifndef NOT_WINDOWS
#include <conio.h>
#endif

#include "analyzer.h"
#include "elements.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	string netlistFileName, commandLine, outputFileName;
	ifstream netlistFile;

	// Clear the console
	#ifndef NOT_WINDOWS
	system("cls");
	#endif

	cout << endl << "Trabalho de Circuitos Eletricos II - UFRJ - 2016.1" << endl;
	cout << "Analise nodal modificada de circuitos lineares" << endl << endl << endl;

	if (argc < 2) {
		cout << "Entre com o nome do arquivo de NETLIST: ";
		getline(cin, netlistFileName);
	}
	else {
		netlistFileName = string(argv[1]);
	}

	netlistFile.open(netlistFileName);
	while (!netlistFile) {
		cout << "Erro: nao foi possivel abrir o arquivo de entrada." << endl;
		cout << "Entre com um nome de arquivo valido: ";
		getline(cin, netlistFileName);
	}

	Analyzer analyzer(netlistFileName);

	if (argc >= 3) {
		commandLine = string(argv[2]);
		analyzer.initializeCommandLine(commandLine);
	}
	
	while (!analyzer.hasCommandLine) {
		cout << "Linha de comando invida ou nao encontrada." << endl;
		cout << "Digite uma linha de comando comecando de formato '.AC <LIN/OCT/DEC> <n_pontos> <freq_inicio> <freq_fim>': ";
		getline(cin, commandLine);
		analyzer.initializeCommandLine(commandLine);
	}

	cout << "Elementos inicializados para a analise nodal:" << endl << endl;
	for (unsigned int index = 0; index < analyzer.elementNetlist.size(); index++) {
		analyzer.elementNetlist.at(index)->print();
	}

	analyzer.writeOperatingPoint();
	
	cout << "Realizando analise em frequencia..." << endl << endl;
	
	analyzer.calculateFrequencyAnalysis();

	cout << "Programa terminado. Pressione uma tecla para fechar..." << endl;

	#ifndef NOT_WINDOWS
	getch();
	system("cls");
	#endif

	return 0;
}
