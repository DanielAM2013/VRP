#include <iostream>
#include <fstream>

//#include <list>
#include <queue>
#include <vector>

#include <ctime>

#include <algorithm>
#include <complex>

using namespace std;

typedef unsigned int num;
typedef unsigned int vertex;
typedef double weight;
typedef std::complex<double> point;


// Ler um arquivo e retornar um vector de point
vector<point> read( char file[]) {
 ifstream data( file, ifstream::in);
 point aux;
 vector<point> Aux;
 while( data >> aux.real() >> aux.imag()) {
  Aux.push_back(aux);
 }
 return Aux;
}






/*
class edge
{
 private:
  point weight;
 public:  
  edge( double re=0, double im=0): weight(re, im) {}
 
  point getw( void) {
   return weight;
  }
  void nullw( void) {
   weight=point(0,0);
  }

}

class vertex
{
 private:
  double info;
 public:
  vertex( double I): info(I) {}

  double geti(void) {
   return info;
  }

}

class arcs;
class ladj;
class madj;
*/
