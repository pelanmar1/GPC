// planos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

#include <iostream.h>
// ============================================
class clsVector3D
{
private:
	double dbl_x, dbl_y, dbl_z ;
public:
	clsVector3D()
	{ 
      dbl_x = dbl_y = dbl_z = 0.0;
	}
	void x( double unX ) { dbl_x = unX; }
	double x() { return dbl_x; }

	void y( double unY ) { dbl_y = unY; }
	double y() { return dbl_y; }

	void z( double unZ ) { dbl_z = unZ; }
	double z() { return dbl_z; }

    friend ostream& operator <<( ostream& os, clsVector3D& p )
	{
      os << "( " << p.x() << "," << p.y() << "," << p.z() << " )";
	  return os;
	}

	friend clsVector3D operator +( clsVector3D a, clsVector3D b )
	{
      clsVector3D s;
      s.x( a.x() + b.x() );
	  s.y( a.y() + b.y() );
	  s.z( a.z() + b.z() );

	  return s;
	}

	friend clsVector3D operator * ( double esc, clsVector3D v )
	{
      clsVector3D w;

	  w.x( esc * v.x() );
	  w.y( esc * v.y() );
	  w.z( esc * v.z() );

	  return w;
	}

	friend clsVector3D operator * ( clsVector3D v, double esc )
	{
      return esc * v;
	}

   // EJER 1) operador de entrada del clsVector3D:
	friend istream& operator >>( istream& is, clsVector3D& v )
	{
      // por lo pronto solo es un dummy que regresa el (0,1.0,2.0)
      clsVector3D w;
	  w.y(1.0);
	  w.z(2.0);

	  v = w;
	  return is;
	}
  // EJER 2) operador Producto Cruz de dos clsVector3D
	friend clsVector3D operator *( clsVector3D& a, clsVector3D& b )
	{
      // por lo pronto un dummy que regresa el ( -1.0,-2.0,-3.0 )
      clsVector3D w;
      w.x( -1.0 );
	  w.y( -2.0 );
	  w.z( -3.0 );

	  return w;
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
   clsPlano3D( clsVector3D v1, clsVector3D v2, clsVector3D v3 )
   {  // por lo pronto un dummy que entrega el 5x + 5y + 5z + 5 = 0. 
	  dbl_A = dbl_B = dbl_C = dbl_D = 5.0;
   }
	  
   void A( double unA ) { dbl_A = unA; }
   double A() { return dbl_A; }

   void B( double unB ) { dbl_B = unB; }
   double B() { return dbl_B; }

   void C( double unC ) { dbl_C = unC; }
   double C() { return dbl_C; }

   // EJER 4) Impresión del plano A * x + B * y + c * z + D = 0.
   friend ostream& operator <<( ostream& os, clsPlano3D& p )
   {
     os << "Este es el dummy de la impresión del plano..." << endl;
     return os;
   }
   
   // EJER 5) Lectura del plano como A * x + B * y + c * z + D = 0. 
   friend istream& operator >>( istream& is, clsPlano3D& p )
   { 
     clsPlano3D w;
	 p = w;
	 return is;
   }

   // EJER 6) Obtener el punto que resulta de la intersección de tres planos 
   friend clsVector3D interseccion( clsPlano3D P1, clsPlano3D P2, clsPlano3D P3 )
   {
     // va el dummy con el ( 100.0 ,200.0, 300.0)
     clsVector3D a;
     a.x( 100.0 );
	 a.y( 200.0 );
	 a.z( 300.0 );
	 return a;
   }
};
// =============================================
void main()
{
  clsVector3D a,b,c;

  a.x( 1.0 );
  a.y( 2.0 );
  a.z( 3.0 );

  b.x( -2.0 );
  b.y( -5.0 );
  b.z( -7.0 );

  cout << a << " + " << b << " = " << a + b << endl;

  cout << 5.0 << " * " << a << " = " << 5.0 * a << endl;

  cout << a << " * " << 5.0 << " = " << a * 5.0 << endl;

  cin >> c;

  cout << "c = " << c << endl;

  cout << " a * b = " << a << " * " << b << " = " << a * b << endl;

  clsPlano3D q1,q2,q3;

  cout << q1 << endl;

  cout << "Interseccion " << interseccion( q1,q2,q3 ) << endl;

}
// ========================================================
