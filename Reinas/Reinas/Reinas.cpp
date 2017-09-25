// Reinas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "iostream"
#include <cmath> 
using namespace std;





void imprimeSolucion(int* arr, int n) {
	cout << '[';
	for (int i = 0; i < n; i++) {
		cout << '(' << i << ',' << arr[i] << ')';
		if (i < n - 1)
			cout << ',';
	}
	cout << ']' << endl;
}



bool revisaReinas(int* columnas,int n){
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


void generarPermutaciones(int k, int n, int* edo, int* perm) {

	if (k >= n) {
		if (revisaReinas(perm,n)==true) {
			imprimeSolucion(perm, n);
		}

		return;
	}
	for (int i = 0; i < n; i++) {
		if (edo[i] == 0) {
			edo[i] = 1;
			perm[i] = k;
			generarPermutaciones(k+1 , n, edo, perm);
			edo[i] = 0;
		}
	}
}

int main()
{	
	int k = 0;
	int n = 8;
	int reinas[8] = {};
	int edo[8] = {};
	cout << "Soluciones: " << endl;
	generarPermutaciones(0,n, edo, reinas);

    return 0;
}

