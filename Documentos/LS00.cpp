// LS00.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;


// =======================================
class NodoLS
{
	int     dato;
	NodoLS *sig;
public:
	NodoLS(int unDato)
	{
		dato = unDato;
		sig = NULL;
	}

	NodoLS(int unDato, NodoLS* ap)
	{
		dato = unDato;
		sig = ap;
	}

	void agregaAlFinal(int unDato)
	{
		if (sig)
			sig->agregaAlFinal(unDato);
		else
			sig = new NodoLS(unDato);
	}

	void imp()
	{
		cout << '(' << dato << ')';
		if (sig)
		{
			cout << ',';
			sig->imp();
		}
	}

	friend ostream& operator <<(ostream& os, NodoLS& n)
	{
		os << '(' << n.dato << ')';
		if (n.sig)
			os << ',' << *(n.sig);
		return os;
	}
};
// ======================================
class AsaLS
{
	NodoLS* prim;
public:
	AsaLS()
	{
		prim = NULL;
	}

	void agregaAlFinal(int unDato)
	{
		if (prim)
			prim->agregaAlFinal(unDato);
		else
			prim = new NodoLS(unDato);
	}

	void agregaAlInicio(int unDato)
	{
		prim = new NodoLS(unDato, prim);
	}

	void imp()
	{
		cout << '[';
		if (prim)
			prim->imp();
		cout << ']' << endl;
	}

	friend ostream& operator <<(ostream& os, AsaLS& a)
	{
		os << '[';
		if (a.prim)
			os << *(a.prim);
		os << ']' << endl;
		return os;
	}

	void leefin(istrstream f)
	{
		enum edo { S0, S1, S2, S3, S4, S5, SF, SError };
		enum edo s = S0;
		char c;
		int n;

		while ((s != SF) && (s != SError))
		{
			//f >> c;
			//f.eatwhite();
			f.get(c);
			cout << c;
			if (f.eof()) c = '\0';
			switch (s)
			{
			case S0:if (c == '[')
				s = S1;
					else
						s = SError;
				break;
			case S1:
			case S5:
				if (c == '(')
				{
					//s = S2;
					f >> n;
					s = S3;
				}
				else
					if (c == ']')
						s = SF;
					else
						s = SError;
				break;
			case S2:if ('0' <= c  && c <= '9')
			{
				//d = c;
				s = S3;
			}
					else
						s = SError;
				break;
			case S3:if (c == ')')
			{
				s = S4;
				cout << "Se agrega el nodo con id " << n << endl;
				agregaAlFinal(n);
			}
					else
						s = SError;
				break;
			case S4:if (c == ']')
				s = SF;
					else
						if (c == ',')
							s = S5;
						else
							s = SError;
				break;
				/*		case S5:if( c == '(' )
				s = S2;
				else
				s = SError;
				break;
				*/

			}
		}
		if (s == SF)
			cout << "todo ok\n";
		else
		{
			cout << "error en la cadena\n";
			throw 5;
		}
	}



};
// ======================================

// =======================================
void main(int argc, char* argv[])
{
	char c;
	AsaLS a;
	a.agregaAlFinal(100);
	a.agregaAlFinal(200);
	a.agregaAlFinal(300);
	a.agregaAlFinal(400);
	a.agregaAlFinal(500);

	a.agregaAlInicio(-500);
	a.agregaAlInicio(-200);

	cout << a;
	cout << "==============================\n";
	
	ofstream fo = ofstream("D:\\user\\Materias\\GPC\\archivo.txt",ios::out);
	fo << a;
/*
	fo << "Hola, este es un archivo de texto" << endl;
	fo << a;

	fo.close();
*/	
	//ifstream fin("C:\\user\\Materias\\EDA\\2003EneMay\\LS00\\datos.txt",ios::in);
	//istrstream fin("[(4),(3)]");
/*	
	while(!fin.eof() )
	{
	c = fin.get();
	cout << c;
	}

	try
	{
		a.leefin(fin);
	}
	catch (int x)
	{
		cout << "Se cacho un " << x << endl;
	}
	fin.close();
	cout << a;
*/

	char car;
	cin >> car;
}


