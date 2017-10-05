#include "stdafx.h"
#include "planos.h"
#include <iostream>
using namespace std;

// planos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/* En este código usted debe agregar las sentencias
necesarias ( funciones, operadores y script de pruebas )
para:
// EJER 1) operador de entrada del clsVector3D
// EJER 2) operador Producto Cruz de dos clsVector3D
// EJER 3) Construir el plano a partir de los tres puntos v1, v2 y v3.
// EJER 4) Impresión del plano A * x + B * y + c * z + D = 0.
// EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0.
// EJER 6) Obtener el punto que resulta de la intersección de tres planos

En los casos de los operadores de lectura agregue lectura de input streams
definidos en base a cadenas de caracteres, de tal forma que pueda probar
de manera rápida sus operadores.

*/

#include <iostream>
#include <strstream>
#include <allocators>>

using namespace std;
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

	clsVector3D(double x, double y, double z)
	{
		dbl_x = x;
		dbl_y = y;
		dbl_z = z;
	}

	void x(double unX) { dbl_x = unX; }
	double x() { return dbl_x; }

	void y(double unY) { dbl_y = unY; }
	double y() { return dbl_y; }

	void z(double unZ) { dbl_z = unZ; }
	double z() { return dbl_z; }

	friend ostream& operator <<(ostream& os, clsVector3D& p)
	{
		os << "Punto3D( " << p.x() << "," << p.y() << "," << p.z() << " )";
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
	friend istream& operator >> (istream& is, clsVector3D& v)
	{
		// por lo pronto solo es un dummy que regresa el (0,1.0,2.0)
		clsVector3D w;
		w.y(1.0);
		w.z(2.0);

		v = w;
		return is;
	}
	// operador Producto Cruz de dos clsVector3D
	friend clsVector3D operator *(clsVector3D& a, clsVector3D& b)
	{
		clsVector3D w;
		w.x(a.y() * b.z() - b.y() * a.z());
		w.y(b.x() * a.z() - a.x() * b.z());
		w.z(a.x() * b.y() - a.y() * b.x());

		return w;
	}
};
// =============================================
//      Funciones de utilería para el cálculo de intersecciones de planos
// =============================================
void copia_t(double *t, double *m)
{
	int i;
	for (i = 0; i < 9; i++) *(t++) = *(m++);
}

void sustCol(int kol, double t[3][3], double c[3])
{
	t[0][kol] = c[0];
	t[1][kol] = c[1];
	t[2][kol] = c[2];
}

double calcDet(double m[3][3])
{
	return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
		- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}
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

	// Construir el plano a partir de los tres puntos v1, v2 y v3.
	clsPlano3D(clsVector3D v1, clsVector3D v2, clsVector3D v3)
	{
		clsVector3D w;
		//
		// utilizando el * (sobrecargado) para el producto cruz
		//
		// w es wl vector perpendicular al plano, se utiliza el punto 1 para calcular D
		//
		w = (v2 - v1) * (v3 - v1);
		dbl_A = w.x();
		dbl_B = w.y();
		dbl_C = w.z();
		dbl_D = -(dbl_A * v1.x() + dbl_B * v1.y() + dbl_C * v1.z());
	}

	void A(double unA) { dbl_A = unA; }
	double A() { return dbl_A; }

	void B(double unB) { dbl_B = unB; }
	double B() { return dbl_B; }

	void C(double unC) { dbl_C = unC; }
	double C() { return dbl_C; }

	void D(double unD) { dbl_D = unD; }
	double D() { return dbl_D; }


	friend double* obtenMatrix(int n, clsPlano3D planos[])
	{
		int k;
		double *ap;
		double *m = (double*)(malloc((n * 4 * sizeof(double))));
		if (m == NULL)
		{
			cout << "Fracaso al tratar de alojar memoria en obtenMatrix para " << n << " planos " << endl;
			throw 5;
		}
		ap = m;
		for (k = 0; k < n; k++)
		{
			(*ap++) = planos[k].A();
			(*ap++) = planos[k].B();
			(*ap++) = planos[k].C();
			(*ap++) = planos[k].D();
		}
		return m;
	}



	// Impresión del plano A * x + B * y + c * z + D = 0.
	friend ostream& operator <<(ostream& os, clsPlano3D& p)
	{
		double xA, xB, xC, xD;
		char sa, sb, sc, sd;
		xA = p.dbl_A;
		xB = p.dbl_B;
		xC = p.dbl_C;
		xD = p.dbl_D;

		sa = xA >= 0 ? '+' : '-';
		sb = xB >= 0 ? '+' : '-';
		sc = xC >= 0 ? '+' : '-';
		sd = xD >= 0 ? '+' : '-';

		xA = fabs(xA);
		xB = fabs(xB);
		xC = fabs(xC);
		xD = fabs(xD);

		os << "[" << sa << ' ' << xA << " * X " << sb << ' ' << xB << " * Y " << sc << ' ' << xC << " * Z " << sd << ' ' << xD << " = 0 ]" << endl;
		return os;
	}

	// Lectura del plano como [ A * x + B * y + c * z + D ] 

	void static leedoble(istream& is, bool * ban, char *c, double *w)
	{
		while (!is.eof() && (((*c = is.get()) != '+') && (*c != '-')));
		if (*ban) is >> *w;
		if (*ban) *w *= *c == '-' ? -1.0 : 1.0;
		if (*ban) while (!is.eof() && ((*c = is.get()) == ' '));
		*ban = *ban && !is.eof();
		if (*c != '*') *ban = false;
		while (!is.eof() && ((*c = is.get()) == ' '));
		*ban = *ban && !is.eof();
	}

	friend istream& operator >> (istream& is, clsPlano3D& p)
	{
		clsPlano3D w;
		double A, B, C, D;
		bool ban = true;
		char c;

		A = 0.0;
		B = 0.0;
		C = 0.0;
		D = 0.0;

		while (!is.eof() && ((c = is.get()) == ' '));
		ban = ban && !is.eof();
		if (c != '[') ban = false;

	clsPlano3D:leedoble(is, &ban, &c, &A); // NOTA: primer uso y declaración de uso en esta rutina
		if (c != 'x') ban = false;

		leedoble(is, &ban, &c, &B);
		if (c != 'y') ban = false;

		leedoble(is, &ban, &c, &C);
		if (c != 'z') ban = false;

		if (ban) while (!is.eof() && (((c = is.get()) != '+') && (c != '-')));
		if (ban) is >> D;
		if (ban) D *= c == '-' ? -1.0 : 1.0;
		if (ban) while (!is.eof() && ((c = is.get()) == ' '));
		ban = ban && is.eof();
		if (ban) while (!is.eof() && ((c = is.get()) != '='));
		ban = ban && is.eof();
		if (ban) while (!is.eof() && ((c = is.get()) != '0'));
		ban = ban && is.eof();
		if (c != '0') ban = false;
		if (ban) while (!is.eof() && ((c = is.get()) != ']'));
		if (c != ']') ban = false;

		w.dbl_A = A;
		w.dbl_B = B;
		w.dbl_C = C;
		w.dbl_D = D;

		p = w;
		return is;
	}


	// Obtiene el punto que resulta de la intersección de tres planos 
	friend clsVector3D interseccion(clsPlano3D P1, clsPlano3D P2, clsPlano3D P3)
	{
		double x, y, z, det;
		double m[3][3];
		double t[3][3];
		double d[3];

		clsVector3D a;

		m[0][0] = P1.A();
		m[0][1] = P1.B();
		m[0][2] = P1.C();

		m[1][0] = P2.A();
		m[1][1] = P2.B();
		m[1][2] = P2.C();

		m[2][0] = P3.A();
		m[2][1] = P3.B();
		m[2][2] = P3.C();

		d[0] = -P1.D();
		d[1] = -P2.D();
		d[2] = -P3.D();

		det = calcDet(m);
		if (fabs(det) > 1e-3)
		{
			copia_t(&t[0][0], &m[0][0]);
			sustCol(0, t, d);
			a.x(calcDet(t) / det);

			copia_t(&t[0][0], &m[0][0]);
			sustCol(1, t, d);
			a.y(calcDet(t) / det);

			copia_t(&t[0][0], &m[0][0]);
			sustCol(2, t, d);
			a.z(calcDet(t) / det);
		}
		else
		{
			// regreso un punto inexistente...
			a.x(NAN);
			a.y(NAN);
			a.z(NAN);
		}

		return a;
	}
};
// =============================================
int main_planos(int argc, char * argv[])
{
	clsVector3D a, b, c;

	a.x(1.0);
	a.y(2.0);
	a.z(3.0);

	b.x(-2.0);
	b.y(-5.0);
	b.z(-7.0);
	cout << "-----------------------------------------" << endl;
	cout << "       INICIA IMPRESION DE PLANOS" << endl;
	cout << "-----------------------------------------" << endl;
	cout << a << " + " << b << " = " << a + b << endl;

	cout << 5.0 << " * " << a << " = " << 5.0 * a << endl;

	cout << a << " * " << 5.0 << " = " << a * 5.0 << endl;

	cin >> c;

	cout << "c = " << c << endl;

	cout << " a * b = " << a << " * " << b << " = " << a * b << endl;

	clsPlano3D q1, q2;
	
	istrstream ist1("[ + 1 * x + 1 * y + 1 * z - 3 = 0 ]");
	ist1 >> q1;
	istrstream ist2("[ + 0 * x + 0 * y + 1 * z +  = 0 ]");
	ist2 >> q2;
    clsPlano3D q3 = clsPlano3D(a, b, c);
	

	cout << "=========================================" << endl;
	cout << q1 << endl;
	cout << q2 << endl;
	cout << q3 << endl;

	cout << "=========================================" << endl;
	cout << "Interseccion " << interseccion(q1, q2, q3) << endl;
	cout << "=========================================" << endl;
	cout << "============= FIN DE PLANOS =============" << endl;
	cout << "=========================================" << endl << endl;
	return 1;

}
// ========================================================
