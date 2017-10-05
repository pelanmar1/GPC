#include "stdafx.h"
#include <iostream.h>
// ================================================================
class clsAsaNodoPolix;
// ================================================================
class clsNodoPolix
{
	friend clsAsaNodoPolix;
private:
	int           intExpo;
	double        dblCoef;
	clsNodoPolix* sig;

public:
    //-------------------------------------------
	clsNodoPolix(int unExpo )
	{
      intExpo = unExpo;
	  dblCoef = 0.0;
	  sig     = NULL;
	}
    //-------------------------------------------

	double& buscaAgrega( int unExpo )
	{
      clsNodoPolix *t;
      if( unExpo == intExpo )
		  return dblCoef;

      if( sig )
	  {
        if( unExpo > sig->intExpo )
		{ 
		  t      = new clsNodoPolix( unExpo );
		  t->sig = sig;
		  sig    = t;
          return t->dblCoef;
		}
		else
          return sig->buscaAgrega( unExpo );
	  }
	  else
	  { 
		  sig = new clsNodoPolix( unExpo );
		  return sig->dblCoef;
	  }
	}
    //-------------------------------------------

    friend ostream& operator <<( ostream& s, clsNodoPolix& n )
	{
      if( n.dblCoef >= 0.0 ) s << "+ ";
      s << n.dblCoef;
      s << " X ^ " << n.intExpo << " ";
	  if( n.sig ) s << *n.sig;
	  return s;
	}
};
// ================================================================
class clsAsaNodoPolix
{
private:
	clsNodoPolix *prim;
	char chrVar;
public:
    //-------------------------------------------
	clsAsaNodoPolix( char unChar )
	{
      chrVar = unChar;
      prim   = NULL;
	}
    //-------------------------------------------
    double& operator()(int unExpo )
	{
      clsNodoPolix *t;

      if( prim )
	  {
        if( unExpo > prim->intExpo )
		{ 
		  t      = new clsNodoPolix( unExpo );
		  t->sig = prim;
		  prim   = t;
          return t->dblCoef;
		}
		else
          return prim->buscaAgrega( unExpo );
	  }
	  else
	  { 
		  prim = new clsNodoPolix( unExpo );
		  return prim->dblCoef;
	  }
	}
    //-------------------------------------------   
	friend ostream& operator <<( ostream& s, clsAsaNodoPolix& a )
	{
      s << a.chrVar << "(x)= ";
	  if( a.prim )
        s << *a.prim << endl;
      else
		s << '0' << endl;
	  return s;
	}
};
// ================================================================
// ================================================================
// ================================================================
// ================================================================
void main(int argc, char* argv[])
{
  clsAsaNodoPolix p('P');
  clsAsaNodoPolix q('Q');

  cout << p;
  cout << q;
  cout << "----------------------------\n";
  p(2) = 4.0;
  p(1) = 2.0;
  p(0) = -1.0;
  cout << p;
  cout << "----------------------------\n";
  q(5) = 10.0;
  q(6) = -2.0;
  q(0) = 7.0;
  cout << p;
  cout << q;
}
// ================================================================
