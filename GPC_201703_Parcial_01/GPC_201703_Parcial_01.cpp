// GPC_201703_Parcial_01.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "planos.h"
#include "reinas.h"
#include "ciclos.h"
#include <iostream>
using namespace std;



int main(int argc, char *argv[])
{
	int res_planos = -1;
	int res_reinas = -1;
	int res_ciclos = -1;

	res_planos = main_planos(argc, argv);

	res_reinas = main_reinas(argc, argv);

	//res_ciclos = main_ciclos(argc, argv);
	
	cout << endl << endl;
	cout << "============================================" << endl;
	cout << "Resultado:" << res_planos + 2 * res_reinas + 4 * res_ciclos << endl;
	cout << "============================================" << endl;

    return 0;
}


