// Permutaciones.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

// ==============  NOTA ===================
// la variable global cuantas aloja 
// la cantidad de permutaciones que se van obteniendo
long GLOBAL_cuantas = 0;
// la variable global g es el apuntador a la 
// zona de memoria que guarda las permutaciones
int *GLOBAL_g;
// =================================
// el primer valor importante es ele cero!!!!!

void guarda(int n, int p[])
{
	int k;
	// NOTA: usa las variable ....
	long algo = (GLOBAL_cuantas - 1) * n;
	for (k = 0; k < n; k++)
		*(GLOBAL_g + algo++) = p[k];
}
void imp(int n)
{
	// NOTA: usa las variables globales ...
	long cual;
	int k;
    long algo = 0;
	for (cual = 1; cual <= GLOBAL_cuantas; cual++)
	{
		
		cout << cual << " => ";
		for (k = 0; k < n; k++)
			cout << *(GLOBAL_g + algo++) << " ";
		cout << endl;
	}
}
void permut(int k, int n, int p[], int d[])
{
	int i;
	if (k == n)
	{
		// ===== NOTA ======
		//  Actualización de la variable global cuantas
		GLOBAL_cuantas++;
		// =================
		//cout << GLOBAL_cuantas << " ... "; for (i = 0; i < n; i++) cout << p[i] << " "; cout << endl;
		guarda(n, p);
	}
	else
	{
		for (i = 0; i < n; i++)
			if (d[i])  // d[i] == 1 => disponible
			{
				p[i] = k;
				d[i] = 0;
				permut(k + 1, n, p, d);
				d[i] = 1;
			}
	}
}

long nfactn(int n)
{
	//int k;
	long r;
	r = n;
	while (n) r *= n--;
	//for (k = 2; k <= n; k++) r *= k;
	return r;
}

#define N 5
int main(int argc, char *argv[])
{
	char c;
	clock_t t0, t1;
	float deltaT_seg;
	long espacio;

	int *p;
	int *d;
	int i, n;

	if (argc > 1)
	{
		n = 5;//atoi(? ? ? ? );
	}
	else
		n = 8;
	p = (int*)malloc(sizeof(int)*n);
	d = (int*)malloc(sizeof(int)*n);
	espacio = nfactn(n);
	
	if ( !(GLOBAL_g = (int*)malloc(espacio * sizeof(int))) )
	{
		cout << "No hay memoria, llamar a los bomberos" << endl;
		cin >> c;
		return 1;
	}

	for (i = 0; i < n; i++)
		d[i] = 1;
	t0 = clock();
	permut(0, n, p, d);
	t1 = clock();
	imp(n);
	deltaT_seg = (float)(t1 - t0) / CLOCKS_PER_SEC;
	cout << "Para n:" << n << " tarda " << deltaT_seg << " seg." << endl;
	cout << "Se requiere " << espacio << endl;
	cin >> c;
    return 0;
}

