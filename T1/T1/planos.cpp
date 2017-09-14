// planos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
using namespace std;
/* En este código usted debe agregar las sentencias
necesarias ( funciones, operadores y script de pruebas )
para:
// EJER 1) operador de entrada del clsVector3D
// EJER 2) operador Producto Cruz de dos clsVector3D
// EJER 3) Construir el plano a partir de los tres puntos v1, v2 y v3.
// EJER 4) Impresión del plano A * x + B * y + C * z + D = 0.
// EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
// EJER 6) Obtener el punto que resulta de la intersección de tres planos

En los casos de los operadores de lectura agregue lectura de input streams
definidos en base a cadenas de caracteres, de tal forma que pueda probar
de manera rápida sus operadores.

*/

using namespace std;
#include <iostream>
// ============================================
class clsVector3D
{
private:
	double dbl_x, dbl_y, dbl_z;
public:
	clsVector3D()
	{
		dbl_x = dbl_y = dbl_z = 0.0;
	}
	clsVector3D(double unX, double unY, double unZ) {
		dbl_x = unX;
		dbl_y = unY;
		dbl_z = unZ;

	}
	void x(double unX) { dbl_x = unX; }
	double x() { return dbl_x; }

	void y(double unY) { dbl_y = unY; }
	double y() { return dbl_y; }

	void z(double unZ) { dbl_z = unZ; }
	double z() { return dbl_z; }

	friend ostream& operator <<(ostream& os, clsVector3D& p)
	{
		os << "( " << p.x() << "," << p.y() << "," << p.z() << " )";
		return os;
	}

	friend clsVector3D operator +(clsVector3D a, clsVector3D b)
	{
		clsVector3D s;
		s.x(a.x() + b.x());
		s.y(a.y() + b.y());
		s.z(a.z() + b.z());

		return s;
	}
	// RESTA
	friend clsVector3D operator -(clsVector3D a, clsVector3D b)
	{
		clsVector3D s;
		s.x(a.x() - b.x());
		s.y(a.y() - b.y());
		s.z(a.z() - b.z());

		return s;
	}

	friend clsVector3D operator * (double esc, clsVector3D v)
	{
		clsVector3D w;

		w.x(esc * v.x());
		w.y(esc * v.y());
		w.z(esc * v.z());

		return w;
	}

	friend clsVector3D operator * (clsVector3D v, double esc)
	{
		return esc * v;
	}

	// EJER 1) operador de entrada del clsVector3D:
	friend istream& operator >>(istream& is, clsVector3D& v)
	{
		v = lecturaAVector(is,v);
		return is;
	}
	// EJER 2) operador Producto Cruz de dos clsVector3D
	friend clsVector3D operator *(clsVector3D& a, clsVector3D& b)
	{
		// por lo pronto un dummy que regresa el ( -1.0,-2.0,-3.0 )
		clsVector3D w;
		w.x(a.dbl_y * b.dbl_z - b.dbl_y * a.dbl_z);
		w.y(b.dbl_x * a.dbl_z - a.dbl_x * b.dbl_z);
		w.z(a.dbl_x * b.dbl_y - a.dbl_y * b.dbl_x);

		return w;
	}

	// PRODUCTO PUNTO
	friend double operator ^(clsVector3D& a, clsVector3D& b)
	{
		double w;
		w = a.dbl_x*b.dbl_x + a.dbl_y*b.dbl_y + a.dbl_z*b.dbl_z;
		return w;
	}

	 

	// LECTURA DE UN INPUT STREAM Y CARGA A VECTOR
	static clsVector3D lecturaAVector(istream& is, clsVector3D vector){
		enum edo { S0, S1, SF, SError };
		enum edo s = S0;
		char c;
		double componente;
		int n=0;
		double dec = 0;
		bool tieneDec = false;
		int signo = 1;
		int i=0;
		int j = 1;

		
		while ((s != SF) && (s != SError))
		{
			is.get(c);
			if (is.eof()) {
				c = '\0';
			}

			switch (s) {
				case S0:
					if (c == '(' || c == '[') {
						s = S1;
					}
					else {
						s = SError;
					}
					break;
				case S1:
					if (c == ',' || c==')' || c==']' || c==' ') {
						componente = (n + dec)*signo;
						switch (i)
						{
						case 0:
							vector.x(componente);
							break;
						case 1:
							vector.y(componente);
							break;
						case 2:
							vector.z(componente);
						}
						i += 1;
						n = 0;
						dec = 0;
						tieneDec = false;
						signo = 1;
						j = 1;
						if (c == ')' || c==']')
							s = SF;
					}
					else if (c == '.') {
						tieneDec = true;
					}
					else if(c == '-'){
						signo = -1;
					}
					else {

						if (tieneDec) {
							dec = dec + ((double)((int)(c - '0'))) / (pow(10, j));
							j+=1;
						}
						else {
							n = n * 10 + (c - '0');
						}
					}
					break;

				}

		}
		if (s == SError) {
			cout << endl << "Hubo un error en el formato de entrada." << endl;
		}
		
		return vector;
		
	}
	double det(clsVector3D h1, clsVector3D h2, clsVector3D h3) {
		return h1.dbl_x * (h2.dbl_y * h3.dbl_z - h2.dbl_z * h3.dbl_y) 
			- h1.dbl_y * (h2.dbl_x*h3.dbl_z - h2.dbl_z*h3.dbl_x) 
			+ h1.dbl_z*(h2.dbl_x*h3.dbl_y-h2.dbl_y*h3.dbl_x);

	}
	

};
// =============================================
class clsPlano3D
{
private:
	double dbl_A, dbl_B, dbl_C, dbl_D; // representa el plano Ax + By + Cz + D = 0.
public:
	clsPlano3D()
	{
		dbl_A = dbl_B = dbl_C = dbl_D = 0.0;
	}

	// EJER 3)  Construir el plano a partir de los tres puntos v1, v2 y v3.
	clsPlano3D(clsVector3D v1, clsVector3D v2, clsVector3D v3)
	{  
		//dbl_A = dbl_B = dbl_C = dbl_D = 5.0;
		clsVector3D u, v, n;
		u = v2 - v1;
		v = v3 - v1;
		n = u*v;
		dbl_D = (n^v1)*-1;
		dbl_A = n.x();
		dbl_B = n.y();
		dbl_C = n.z();

		
	}

	void A(double unA) { dbl_A = unA; }
	double A() { return dbl_A; }

	void B(double unB) { dbl_B = unB; }
	double B() { return dbl_B; }

	void C(double unC) { dbl_C = unC; }
	double C() { return dbl_C; }

	void D(double unD) { dbl_D = unD; }
	double D() { return dbl_D; }


	// EJER 4) Impresión del plano A * x + B * y + c * z + D = 0.
	friend ostream& operator <<(ostream& os, clsPlano3D& p)
	{
		os <<"("<< p.dbl_A << ")*x + (" << p.dbl_B << ")*y + (" << p.dbl_C << ")*z = "  << -1*p.dbl_D << endl;
		return os;
	}

	// EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0. 
	friend istream& operator >>(istream& is, clsPlano3D& p)
	{
		p = lecturaAPlano(is, p);
		return is;
	}

	// LECTURA DE UN INPUT STREAM Y CARGA A VECTOR
	static clsPlano3D lecturaAPlano(istream& is, clsPlano3D plano) {
		enum edo { S0, S1, SF, SError };
		enum edo s = S0;
		char c;
		double componente;
		int n = 0;
		double dec = 0;
		bool tieneDec = false;
		int signo = 1;
		int i = 0;
		int j = 1;


		while ((s != SF) && (s != SError))
		{
			is.get(c);
			while (c == ' ' || isalpha(c) || c == '*') {
				is.get(c);
			}
			if (is.eof()) {
				c = '\0';
			}

			switch (s) {
			case S0:
				if (c == '+' || c == '=') {
					componente = (n + dec)*signo;
					switch (i)
					{
					case 0:
						plano.A(componente);
						break;
					case 1:
						plano.B(componente);
						break;
					case 2:
						plano.C(componente);
						break;
					case 3:
						plano.D(componente);
						break;
					}
					i += 1;
					n = 0;
					dec = 0;
					tieneDec = false;
					signo = 1;
					j = 1;
					if (c == '=')
						s = SF;
				}
				else if (c == '.') {
					tieneDec = true;
				}
				else if (c == '-') {
					signo = -1;
				}
				else {

					if (tieneDec) {
						dec = dec + ((double)((int)(c - '0'))) / (pow(10, j));
						j += 1;
					}
					else {
						n = n * 10 + (c - '0');
					}
					
				}
				break;

			}

		}
		if (s == SError) {
			cout << endl << "Hubo un error en el formato de entrada." << endl;
		}

		return plano;

	}

	// EJER 6) Obtener el punto que resulta de la intersección de tres planos 
	friend clsVector3D interseccion(clsPlano3D P1, clsPlano3D P2, clsPlano3D P3)
	{
		// va el dummy con el ( 100.0 ,200.0, 300.0)
		clsVector3D a;
		a.x(100.0);
		a.y(200.0);
		a.z(300.0);
		return a;
	}


};
// =============================================
void main()
{
	clsVector3D a, b, c;
	a = clsVector3D(1, 2, 3);
	b = clsVector3D(-2, -5, -7);

	/*
	cout << "SUMA: " << endl;
	cout << a << " + " << b << " = " << a + b << endl;
	cout << "MULT. X ESC.: " << endl;
	cout << 5.0 << " * " << a << " = " << 5.0 * a << endl;
	cout << a << " * " << 5.0 << " = " << a * 5.0 << endl;
	cout << "P. CRUZ: " << endl;
	cout << " a * b = " << a << " * " << b << " = " << a * b << endl;
	cout << "P. PUNTO: " << endl;
	cout << " a ^ b = " << a << " ^ " << b << " = " << (a ^ b) << endl;

	cout << "INGESTION DE CADENA" <<  endl;
	cin >> c;
	cout << "c = " << c << endl;
	*/
	
	clsPlano3D  q2, q3;
	clsVector3D p1 = clsVector3D(3, 2, 1);
	clsVector3D p2 = clsVector3D(-4, -1, 1);
	clsVector3D p3 = clsVector3D(-5, -3, -1);

	clsPlano3D q1 = clsPlano3D(p1, p2, p3);

	cout << "PLANO: " << q1 << endl;

	cout << "INGESTION DE CADENA" << endl;
	cin >> q2;
	cout << "p = " << q2 << endl;

	//cout << "Interseccion " << interseccion(q1, q2, q3) << endl;
	
}
