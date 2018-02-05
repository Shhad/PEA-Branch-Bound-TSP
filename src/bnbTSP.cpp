// pea_1.cpp : Defines the entry point for the console application.
//
//Projekt 1 na kurs: Projektowanie efektywnych algorytm�w - Projekt
//Problem komiwoja�era rozwi�zany algorytmem podzialu i ograniczen
//Autor: Filip Baszak

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <list>
#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct krawedz {
	int verP;
	int verK;
	int weight;
};

class TSP {//klasa reprezentuj�ca problem komiwoja�era
public:
	ifstream file;
	TSP();
	int verN;
	int **matrix;
	int *finalPath;
	int *minMax;
	int finalBorder;
	void doDataTSP(string txt);
	void doDataTSP2(string txt);
	void doDataTSP3(string txt);
	void doDataATSP(string txt);
	void findMinMax(int **matrix, int *minMax);
	void findMinMax2(int **matrix, int *minMax);
	int reduceMatrix(int **matrix);
	void colRowToInf(int **matrix, int row, int col);
	void colRowToInf2(int **matrix, int row, int col);
	void TSPBNB(int **matrix, int pastpath, int *path);
	void printMatrix();
	void printMatrix(int **matrix);
	int minMaxC(int **matrix, int col, int row);
	int minMaxR(int **matrix, int col, int row);
	void edgeToInf(int **matrix, int row, int col);
	bool goodCycle(int *luk, int *path);
	bool wholeCycle(int *path);
	void printPath(int *path);
	int pathScore(int **matrix, int *p);
	void reset();
};

TSP::TSP() {
	matrix = NULL;
	verN = 0;
	minMax = NULL;
	finalBorder = 999999;
	finalPath = NULL;
};

void TSP::doDataTSP(string txt) {
	string a;
	string b;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	float *x = new float[1];
	float *y = new float[1];
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			x = new float[verN];
			y = new float[verN];
			matrix = new int*[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			//vertices = new bool[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				//vertices[i] = false;
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "1") {
			for (int i = 2; i <= (verN * 3); i++) {
				file >> b;
				cout << b << endl;
				if (i % 3 == 2) {
					x[counter] = stof(b);
				}
				if (i % 3 == 0) {
					y[counter] = stof(b);
					counter++;
				}
			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	for (int i = 0; i < verN; i++) {
		cout << x[i] << " " << y[i] << endl;
	}
	file.close();
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			matrix[i][j] = 0;
			
		}
	}
	int xd = 0;
	int yd = 0;
	float dij = 0;
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			xd = abs(x[i] - x[j]);
			yd = abs(y[i] - y[j]);
			dij = nearbyint(xd + yd);
			
			if (i != j) {
				matrix[i][j] = dij;
			}
			else {
				matrix[i][j] = -1;
			}
		}
	}
	delete[] x;
	delete[] y;
}

void TSP::doDataTSP2(string txt) {
	string a;
	string b;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	float *x = new float[1];
	float *y = new float[1];
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			//vertices = new bool[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				//vertices[i] = false;
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			//vertices = new bool[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				//vertices[i] = false;
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "1") {
			for (int i = 2; i <= (verN * 3); i++) {
				file >> b;
				cout << b << endl;
				if (i % 3 == 2) {
					x[counter] = stof(b);
				}
				if (i % 3 == 0) {
					y[counter] = stof(b);
					counter++;
				}
			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	for (int i = 0; i < verN; i++) {
		cout << x[i] << " " << y[i] << endl;
	}
	file.close();

	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			matrix[i][j] = 0;
			
		}
	}
	float q1 = 0;
	float q2 = 0;
	float q3 = 0;
	float dij = 0;
	float PI = 3.141592;
	float min = 0;
	float deg = 0;
	float *latitude = new float[verN];
	float *longitude = new float[verN];
	float RRR = 6378.388;
	for (int i = 0; i < verN; i++) {
		deg = nearbyint(x[i]);
		min = x[i] - deg;
		latitude[i] = PI * (deg + 5.0 * min / 3.0) / 180.0;
		deg = nearbyint(y[i]);
		min = y[i] - deg;
		longitude[i] = PI * (deg + 5.0 * min / 3.0) / 180.0;
		cout << latitude[i]<<" "<<longitude[i]<<endl;
	}
	
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (i != j) {
				q1 = cos(longitude[i] - longitude[j]);
				q2 = cos(latitude[i] - latitude[j]);
				q3 = cos(latitude[i] + latitude[j]);
				dij = (int)(RRR * acos(0.5*((1.0 + q1)*q2 - (1.0 - q1)*q3)) + 1.0);
				matrix[i][j] = dij;
			}
			else {
				matrix[i][j] = -1;
			}
		}
	}
	cout << "/-------------------------------------------------\n";
	delete[] longitude;
	delete[] latitude;
	delete[] x;
	delete[] y;
}

void TSP::doDataTSP3(string txt) {
	//ifstream file;
	string a;
	string b;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	verN = 0;
	finalBorder = 999999;
	minMax = new int[3];
	minMax[0] = 0;
	minMax[1] = 0;
	minMax[2] = 0;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "EDGE_WEIGHT_SECTION") {
			while (a != "EOF") {
				for (int i = 0; i <= counter; i++) {
					file >> a;
					if (a != "EOF") {
						matrix[counter][i] = stoi(a);
						matrix[i][counter] = stoi(a);
					}
				}
				counter++;
			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (i == j) {
				matrix[i][j] = -1;
			}
		}
	}
	file.close();
}

void TSP::doDataATSP(string txt) {
	string a;
	string b;
	int z = 0;
	int stop = 0;
	int counter = 0;
	verN = 0;
	finalBorder = 999999;
	minMax = new int[3];
	minMax[0] = 0;
	minMax[1] = 0;
	minMax[2] = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			finalPath = new int[verN];
			//vertices = new bool[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				finalPath[i] = -1;
				//vertices[i] = false;
			}
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			verN = z;
			matrix = new int*[verN];
			finalPath = new int[verN];
			for (int i = 0; i < verN; i++) {
				matrix[i] = new int[verN];
				finalPath[i] = -1;
			}
			z = 0;
		}
		if (a == "EDGE_WEIGHT_SECTION") {
			while (a != "EOF") {
				for (int i = 0; i < verN; i++) {
					file >> a;
					if(a!="EOF")
					matrix[counter][i] = stoi(a);
				}
				counter++;
			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (i == j) {
				matrix[i][j] = -1;
			}
		}
	}
	file.close();
}

void TSP::TSPBNB(int **matrix, int pastpath, int *path) {
	//printPath(path);
	//sprawdzenie czy nie wykonal sie caly cykl - przeszlismy juz cale drzewo
	if (wholeCycle(path)) {
		if (pastpath < finalBorder) {
			finalBorder = pastpath;
			cout << "Sciezka o wartosci: " << pastpath << " jest lepsza!\n";
			printPath(path);
			//printMatrix(matrix);
		}
		return;
	}
	//jezeli mamy juz wgranice wyzsza niz gorna granica to wychodzimy b onie ma
	//sensu dalej sprawdzac
	if (pastpath > finalBorder) return;
	int *minMax=new int[3];
	int counter = 0, *toDelete;
	int *localPath, **helpMatrix;
	//zdefiniowanie lokalnej sciezki i macierzy
	toDelete = new int[2];
	localPath = new int[verN];
	helpMatrix = new int*[verN];
	for (int i = 0; i < verN; i++) {
		helpMatrix[i] = new int[verN];
		localPath[i] = path[i];
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] != -1 && i != j) {
				toDelete[0] = i;
				toDelete[1] = j;
				if (!goodCycle(toDelete, path)) 
					matrix[i][j] = -1;
			}
			helpMatrix[i][j] = matrix[i][j];
		}
	}
	//printMatrix(helpMatrix);
	//cout << endl;
	//cout << endl;
	//I redukujemy macierz
	pastpath = pastpath + reduceMatrix(helpMatrix);
	//II sprawdzamy max z min
	//printMatrix(helpMatrix);
	//cout << endl;
	//cout << "/----------------------------------------------------------------------------\n";
	bool ok = false;
	while (!ok) {
		//wyieramy krawedz ktora zwiekszy wartosc prawego poddrzewa o najwieksza wartosc
		findMinMax(helpMatrix,minMax);
		//sprawdzamy czy mozemy ja wybrac - czy nie tworzy zamknietego cyklu z innymi
		if (goodCycle(minMax,localPath)) {
			//jesli nie tworzy to
			//dodac do sciezki luk
			localPath[minMax[0]] = minMax[1];
			//colRowToInf w zaleznosci od luku - usuwamy z macierzy dany wiersz i kolumne
			colRowToInf2(helpMatrix, minMax[0], minMax[1]);
			ok = true;
		}
		//jesli nie mozna dodac tego luku to w macierzy zaznaczamy te krawedz jako inf
		else {
			helpMatrix[minMax[0]][minMax[1]] = -1;//OGARNIETE BLAD te krawedzie rowniez musza byc zaznaczane w macierzy ktora idzie do etapu 2
			matrix[minMax[0]][minMax[1]] = -1;
		}
	}
	//printPath(path);
	//III sprawdzmy czy max z min jest mozliwy jesli nie to II jesli tak to IV
	//printMatrix(helpMatrix);
	//cout << endl;
	//cout << "/----------------------------------------------------------------------------\n";
	//IV przechodzimy do kolejnej zredukowanej macierzy
	TSPBNB(helpMatrix, pastpath, localPath);
	for (int i = 0; i < verN; i++) {
		localPath[i] = path[i];
		for (int j = 0; j < verN; j++) {
			helpMatrix[i][j] = matrix[i][j];
		}
	}
	//printMatrix(helpMatrix);
	//cout << endl;
	//cout << pastpath;
	//cout << endl;
	//cout << minMax[2];
	//cout << endl;
	//V jesli max z min + border < min, czyli nie bierzemy tej krawedzi pod uwage
	if (pastpath + minMax[2] < finalBorder) {
		reduceMatrix(helpMatrix);
		//cout << "Sciezka alternatywna "<<pastpath<<" + "<<minMax[2]<<"\n";
		pastpath = pastpath + minMax[2];
		localPath[minMax[0]] = -1;
		edgeToInf(helpMatrix, minMax[0], minMax[1]);
		findMinMax2(helpMatrix, minMax);
		TSPBNB(helpMatrix, pastpath, localPath);
	}
	for (int i = 0; i < verN; i++) {
		delete[] helpMatrix[i];
	}
	delete[] helpMatrix;
	delete[] localPath;
	delete[] minMax;
	delete[] toDelete;
}

bool TSP::goodCycle(int *luk, int *path) {
	int v = path[luk[1]];
	int counter = 0;
	for (int i = 0; i < verN; i++) {
		if (path[i] == -1) counter++;
	}
	if (counter == 1) {
		return true;
	}
	for (int i = 0; i < verN; i++) {
		
		if (v == -1) {
			//cout << "luk " << luk[0] << " | " << luk[1] << " moze byc dodany\n";
			return true;

		}
		if (i == verN - 1) {
			return true;
		}
		if (v == luk[0]) {
			//cout << "luk " << luk[0] << " | " << luk[1] << " nie moze byc dodany\n";
			return false;
		}
		
		v = path[v];
	}
}

bool TSP::wholeCycle(int *path) {
	int v = path[0];
	int vp = 0;
	for (int i = 0; i < verN; i++) {
		if (v == -1) {
			return false;
		}
		if (v == 0) {
			return true;
		}
		v = path[v];
	}
}

int TSP::reduceMatrix(int **matrix) {
	int *row, *col;
	int min = 999999;
	bool zrobione = false;
	row = new int[verN];
	col = new int[verN];
	//redukcja wierszy
	for (int i = 0; i < verN; i++) {
		row[i] = min;
		zrobione = false;
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] != -1 && matrix[i][j] < row[i]) {
				row[i] = matrix[i][j];
				zrobione = true;
			}
			if ((j == (verN - 1)) && !zrobione) {
				row[i] = 0;
			}
		}
		//cout << "najmniejsza wartosc do zredukowania w wierszu " << i << "to "<<row[i] << endl;
		//min = 999999;
	}
	//odjecie zredukowanych wierszy
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] != -1) {
				matrix[i][j] = matrix[i][j]-row[i];
			}
		}
	}
	//cout << endl << "Otow po zredukowaniu wierszy:" << endl;
	//printMatrix(matrix);
	//redukcja kolumn
	for (int i = 0; i < verN; i++) {
		col[i] = min;
		zrobione = false;
		for (int j = 0; j < verN; j++) {
			if (matrix[j][i] != -1 && matrix[j][i] < col[i]) {
				col[i] = matrix[j][i];
				zrobione = true;
			}
			if ((j == (verN - 1)) && !zrobione) {
				col[i] = 0;
			}
		}
		//cout << "najmniejsza wartosc do zredukowania w kolumnie " << i << "to " << col[i] << endl;
		//min = 999999;
	}
	//odjecie zredukowanych kolumn
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[j][i] != -1) {
				matrix[j][i] = matrix[j][i]-col[i];
			}
		}
	}
	min = 0;
	//cout << endl << "Otow po zredukowaniu kolumn:" << endl;
	//printMatrix(matrix);
	for (int i = 0; i < verN; i++) {
		min = min + row[i] + col[i];
	}
	delete[] row;
	delete[] col;
	return min;
}

void TSP::colRowToInf2(int **matrix, int row, int col) {
	for (int i = 0; i < verN; i++) {
		matrix[row][i] = -1;
		matrix[i][col] = -1;
	}
	matrix[col][row] = -1;
}

void TSP::colRowToInf(int **matrix, int row, int col) {
	for (int i = 0; i < verN; i++) {
		matrix[row][i] = -1;
		matrix[i][col] = -1;
	}
}

void TSP::printPath(int *path) {
	//cout << "0--->";
	int v = path[0];
	cout << "0--->";
	//int v2 = 0;
	for (int i = 0; i < verN; i++) {
		cout << v << "--->";
		v = path[v];
	}
	cout << endl;
}

void TSP::printMatrix() {
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] == -1) {
				cout << matrix[i][j] << " ";
			}
			else {
				if(matrix[i][j] <10 && matrix[i][j]>=0)
				cout << matrix[i][j] << "  ";
				if (matrix[i][j] <100 && matrix[i][j]>9)
					cout << matrix[i][j] << " ";
				if (matrix[i][j] <1000 && matrix[i][j]>99)
					cout << matrix[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}

}

void TSP::printMatrix(int **matrix) {
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] == -1) {
				cout << matrix[i][j] << " ";
			}
			else {
				if (matrix[i][j] <10 && matrix[i][j] >= 0)
					cout << matrix[i][j] << "  ";
				if (matrix[i][j] <100 && matrix[i][j]>9)
					cout << matrix[i][j] << " ";
				if (matrix[i][j] <1000 && matrix[i][j]>99)
					cout << matrix[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}
}

void TSP::findMinMax(int **matrix, int *minMax) {
	int min = 99999;
	int minMaxx = 0;

	int verP = 0, verK = 0;
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] == 0) {
				if (minMaxR(matrix, j, i) + minMaxC(matrix, j, i)>minMaxx) {
					minMaxx = (minMaxR(matrix, j, i) + minMaxC(matrix, j, i));
					verP = i;
					verK = j;
				}
			}
		}
	}
	//gdy wszedzie jest 0 to wybieramy pierwsze lepsze
	if (verP == verK) {
		for (int i = 0; i < verN; i++) {
			for (int j = 0; j < verN; j++) {
				if (matrix[i][j] == 0) {
					verP = i;
					verK = j;
					break;
				}
			}
		}
	}
	if (minMaxx == 99999 || minMaxx == (99999 * 2)) minMaxx = 0;
	//cout << "Najwiekszy min max znajduje sie w " << verP << " | " << verK << " i wynosi " << minMaxx << endl;
	minMax[0] = verP;
	minMax[1] = verK;
	minMax[2] = minMaxx;
}

void TSP::findMinMax2(int **matrix, int *minMax) {
	int min = 99999;
	int minMaxx = 0, mmr=99999,mmc=99999;
	
	int verP=minMax[0], verK=minMax[1];
	for (int i = 0; i < verN; i++) {
		if (matrix[minMax[0]][i]<mmr && matrix[minMax[0]][i] != -1) {
			mmr = matrix[minMax[0]][i];
		}
		if (matrix[i][minMax[1]]<mmc && matrix[i][minMax[1]] != -1) {
			mmc = matrix[i][minMax[1]];
		}
	}

	for (int i = 0; i < verN; i++) {
		if (matrix[verP][i] != -1 && i != verP) {
			matrix[verP][i] = matrix[verP][i] - mmr;
		}
		if (matrix[i][verK] != -1 && i != verK) {
			matrix[i][verK] = matrix[i][verK] - mmc;
		}
	}
}

int TSP::minMaxR(int **matrix, int col, int row) {
	int minR = 99999;
	int minC = 99999;
	for (int i = 0; i < verN; i++) {
		if (matrix[row][i] < minR && i != col && matrix[row][i] != -1) {
			minR = matrix[row][i];
		}
		/*if (matrix[i][col] < minC && i != row && matrix[i][col] != -1) {
			minC = matrix[i][col];
		}*/
	}
	return minR;
}

int TSP::minMaxC(int **matrix, int col, int row) {
	int minR = 99999;
	int minC = 99999;
	for (int i = 0; i < verN; i++) {
		/*if (matrix[row][i] < minR && i != col && matrix[row][i] != -1) {
			minR = matrix[row][i];
		}*/
		if (matrix[i][col] < minC && i != row && matrix[i][col] != -1) {
			minC = matrix[i][col];
		}
	}
	return minC;
}

void TSP::edgeToInf(int **matrix, int row, int col) {
	matrix[row][col] = -1;
}

void TSP::reset() {
	for (int i = 0; i < verN; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] minMax;
	delete[] finalPath;
	verN = 0;
	finalBorder = 0;
	matrix = NULL;
	minMax = NULL;
	finalPath = NULL;
}

int TSP::pathScore(int **matrix, int *p) {
	int wynik = 0;
	int v = 0;
	for (int i = 0; i < verN; i++) {
		wynik = wynik + matrix[v][p[v]];
		v = p[v];
	}
	return wynik;
}

int main()
{
	

	srand(time(NULL));
	string plik;
	int opcja;
	cout << "Czy to bedzie 1 - TSP czy 2 - ATSP: ";
	cin >> opcja;
	if (opcja == 1) {
		cout << "Podaj nazwe pliku: ";
		cin >> plik;
		//plik = plik + ".tsp";
		cout << "1.EUC2D czy 2.GEO czy 3.MATRIX?";
		cin >> opcja;
		if (opcja == 1) {
			TSP p;
			p.doDataTSP(plik);
			p.printMatrix();
			p.TSPBNB(p.matrix, 0, p.finalPath);
			cout << "najlepsza sciezka to: " << p.finalBorder;
			getchar();
			//exit(10000);
		}
		if (opcja == 2) {
			TSP p;
			p.doDataTSP2(plik);
			p.printMatrix();
			p.TSPBNB(p.matrix, 0, p.finalPath);
			cout << "najlepsza sciezka to: " << p.finalBorder;
			getchar();
			//exit(10000);
		}
		if (opcja == 3) {
			TSP p;
			p.doDataTSP3(plik);
			p.printMatrix();
			//p.printPath(p.finalPath);
			p.TSPBNB(p.matrix, 0, p.finalPath);
			cout << "najlepsza sciezka to: " << p.finalBorder;
			
			getchar();
		}
		if (opcja == 4) {
			TSP p;
			p.doDataTSP3(plik);
			p.printMatrix();
			int *myPath = new int[p.verN];
			for (int i = 0; i < p.verN; i++) {
				cout << "Podaj po kolei sciezke - " << i << " : ";
				cin >> myPath[i];
			}
			cout << p.pathScore(p.matrix, myPath);
			getchar();
		}
		opcja = 10;
	}
	if (opcja == 2) {
		cout << "Podaj nazwe pliku: ";
		cin >> plik;
		//plik = plik + ".atsp";
		TSP p;
		p.doDataATSP(plik);
		p.printMatrix();
		p.TSPBNB(p.matrix, 0, p.finalPath);
		cout << "najlepsza sciezka to: " << p.finalBorder;
		getchar();
		//exit(10000);
	}
	opcja = 1;
	if (opcja != 2 && opcja != 1) {
		cout << endl << "Podales zly problem.\n";
		getchar();
		exit(10000);
		return 0;
	}
	
	
	getchar();

	exit(10000);
	return 0;
}
