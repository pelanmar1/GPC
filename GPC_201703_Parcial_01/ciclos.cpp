#include "stdafx.h"
#include "ciclos.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void asignaMatrizCostos(int n, double *costos)
{
	int i, j;

	if (n == 4)
	{
		for (i = 1; i <= 4; i++)
			for (j = 1; j <= 4; j++) *(costos++) = (i == j ? 0.0 : (double)(10 * i) + j );
	}
	else
	{
		// PONGA AQUI SU CODIGO
	}
}

void imprimeCostos(int n, double* c)
{
	int i, j;

	cout << "===================================" << endl;
	cout << "      Costos para n: " << n << endl;
	cout << "===================================" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << ' ' << (*c++);
		cout << endl;
	}
}

int main_ciclos(int argc, char ** argv)
{
	/*
	int n = 5;
	double *costos = (double*) malloc( n * n * sizeof(double)); // no me preocupo por el espacio...

	asignaMatrizCostos(n, costos);
	cout << "-----------------------------------------" << endl;
	cout << "       INICIA IMPRESION DE CICLOS" << endl;
	cout << "-----------------------------------------" << endl;

	imprimeCostos(n, costos);

	cout << "=========================================" << endl;
	cout << "============= FIN DE CICLOS =============" << endl;
	cout << "=========================================" << endl << endl;
	*/
	return 1;
}
