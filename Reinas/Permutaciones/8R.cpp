// 8R.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "iostream"
using namespace std;

void imprimeArr(int arr[], int n) {
	for (int i = 0; i < n; i++)
		cout << arr[i];
	cout << endl;
}
void guardarPermutacion(int n, int arrPerm[], int k, int *arrGuardar) {
	for (int i = 0; i < n; i++) {
		*(arrGuardar + k*n + i) = arrPerm[i];
	}
}

void generarPermutaciones(int k, int n, int edo[], int perm[], int* matLineal, int* contador) {
	if (k > n) {
		guardarPermutacion(n, perm, *contador, matLineal);
		(*contador)++;
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



int main()
{
	int edo[] = { 0,0,0,0 };
	int perm[] = { 0,0,0,0 };
	int n = 4;
	int* matLineal = (int*)malloc(sizeof(int)*n*factorial(n));
	int contador = 0;
	generarPermutaciones(1, n, edo, perm, matLineal, &contador);
	for (int i = 0; i < n*factorial(n); i++) {
		cout << *(matLineal + i);
		if ((i + 1) % n == 0) {
			cout << endl;
		}
	}

	return 0;
}
