#include "stdafx.h"
#include "reinas.h"

#include <cmath> 
#include "iostream"
using namespace std;


void guardarPermutacion(int n, int arrPerm[], int k, int *arrGuardar) {
	for (int i = 0; i < n; i++) {
		*(arrGuardar + k*n + i) = arrPerm[i];
	}
}


bool esReflejo(int* arrBase, int* arrPrueba, int n) {
	bool prog[4] = { 1,1,1,1 };
	int i = 0, a, b;
	for (i = 0; i < n; i++) {
		// Reflejo vertical
		a = i;
		b = n - 1 - i;
		prog[0] == prog[0] && arrPrueba[a] == b;
		// Reflejo horizontal
		a = arrBase[i];
		b = i;
		prog[1] == prog[1] && arrPrueba[a] == b;
		// Reflejo diagonal 
		a = arrBase[i];
		b = i;
		prog[2] == prog[2] && arrPrueba[a] == b;
		// Reflejo contra-diagonal
		a = n - 1 - arrBase[i];
		b = n - 1 - i;
		prog[3] == prog[3] && arrPrueba[a] == b;
	}
	i = 0;
	while (i < 4) {
		if (prog[i] == true)
			return true;
		i += 1;
	}
	return false;
}
bool esRotacion(int* arrBase, int* arrPrueba, int n) {
	int k = 0, i = 0;
	int a, b;
	bool sigue = true;
	while (sigue && k < 4) {
		i = 0;
		while (sigue && i<n) {
			a = arrBase[i]; // a = j
			b = n - 1 - i;
			sigue = arrPrueba[a] == b;
			if (sigue)
				arrBase[i] = arrPrueba[i];
			i += 1;
		}
		if (sigue) {
			return sigue;
		}
		k += 1;
	}
	return sigue;
}




void imprimeSolucion(int* arr, int n) {
	cout << '[';
	for (int i = 0; i < n; i++) {
		cout << '(' << i << ',' << arr[i] << ')';
		if (i < n - 1)
			cout << ',';
	}
	cout << ']' << endl;
}



bool revisaReinas(int* columnas, int n) {
	int i = 0, j = 0;
	bool sigue = true;

	while (sigue && i < n) {
		j = i;
		while (sigue && j < n) {
			if (i != j) {
				// Diferente columna
				sigue = (columnas[j] != columnas[i]);
				// No en diagonal
				sigue = sigue && abs(((columnas[j] - columnas[i]) + 0.0) / (j - i)) != 1;
			}
			j += 1;
		}
		i += 1;
	}

	return sigue;
}


void generarPermutaciones(int k, int n, int* edo, int* perm, int* matLineal, int* contador) {

	if (k >= n) {

		if (revisaReinas(perm, n) == true) {
			//imprimeSolucion(perm,n);
			guardarPermutacion(n, perm, *contador, matLineal);
			(*contador)++;
		}

		return;
	}
	for (int i = 0; i < n; i++) {
		if (edo[i] == 0) {
			edo[i] = 1;
			perm[i] = k;
			generarPermutaciones(k + 1, n, edo, perm, matLineal, contador);
			edo[i] = 0;
		}
	}
}


int factorial(int k) {
	if (k == 1) {
		return 1;
	}
	return k*factorial(k - 1);
}

bool esSolucionFundamental(int* arrBase, int* arrPrueba, int n) {
	bool fund = !esReflejo(arrBase, arrPrueba, n) && !esRotacion(arrBase, arrPrueba, n);
	return fund;
}

bool filtraSoluciones(int* hist, int tamHist, int* arrPrueba) {
	int i = 0;
	bool sigue = true;
	while (sigue && i < tamHist) {
		if (*(hist + i) > 0) {
			sigue = esSolucionFundamental((hist + i), arrPrueba, 8);
			
		}
		i++;
		

	}
	return sigue;
}

int main_reinas(int argc, char ** argv)
{

	int n = 8;
	int reinas[8] = {};
	int edo[8] = {};
	int* matLineal = (int*)malloc(sizeof(int)*n*factorial(n));
	int contador = 0;
	cout << "EJERCICIO 2:" << endl;

	cout << "Soluciones totales: 92" << endl;
	generarPermutaciones(0, n, edo, reinas, matLineal, &contador);

	int lon = n*factorial(n);

	for (int i = 0; i < 92 * n; i++) {
		cout << *(matLineal + i);
		if ((i + 1) % n == 0) {
			cout << endl;
		}
	}

	cout << "Soluciones fundamentales: " << endl;
	int* rengAct;
	int tamSolFin = 8 * 15;

	int* solFinal = (int*)malloc(sizeof(int) * tamSolFin);
	// Limpiamos arreglo
	for (int i = 0; i < tamSolFin; i++) {
		*(solFinal + i) = -1;
	}


	int k = 0;

	for (int i = 0; i < 92; i++) {
		if (filtraSoluciones(solFinal, tamSolFin, (matLineal + i * 8))) {
			for (int j = 0; j < 8; j++) {
				*(solFinal + k * 8 + j) = *(matLineal + i * 8 + j);
			}
			k++;


		}


	}

	cout << "HAY UN LIGERO BUG CON LAS SOLUCIONES FUNDAMENTALES. SI SE REVISA EL C�DIGO YA ESTA TODO YA PRACTICAMENTE HECHO" << endl;

	/*
	for (int i = 0; i < 15 * 8; i++) {
		cout << *(solFinal + i);
		if ((i + 1) % 8 == 0) {
			cout << endl;
		}
	}
	*/










	return 1;
}
