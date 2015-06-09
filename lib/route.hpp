#ifndef INCLUDE_ROUTE
#define INCLUDE_ROUTE

#include <base.hpp>
typedef std::vector<point> route;

#include <iostream>
#include <fstream>
#include <algorithm>
/*
//! Avança "n" posições numa lista encadeada
route::iterator next( route::iterator i, int n=1) {

 route::iterator aux=i;
 for ( int k=0; k<n; k++) 
  aux++;

 return aux;
}


//! Recua "n" (default 1) numa lista duplamente encadeada
route::iterator prev( route::iterator i, int n=1) {

 route::iterator aux=i;
 for( int k=0; k<n; k++) 
  aux--;

 return aux;
}
*/

// Lê uma rota: arquivo com uma lista de par de double ordenados
route read_route (char* file) {

 std::ifstream data( file, std::ios::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }
 data.close();

 return first;
}


//! Salva uma rota: arquivo com uma lista de par de double ordenados
void save_route( route R, char* filename)
{

 std::ofstream out(filename, std::ios::out);

 uint n=R.size();
 for( uint i=0; i<n; i++) {
  out << R[i].real() << " " << R[i].imag() << std::endl;
 }
 out << R[0].real() << " " << R[0].imag() << std::endl;

 out.close();
}

// Ordenação parcial do plano
bool operator<(std::complex<double> X, std::complex<double> Y) {
 if(std::arg(X)<std::arg(Y)) return true;
 if(std::arg(X)==std::arg(Y) & std::abs(X) < std::abs(Y)) return true;
 return false;
}

//! Order points of route in counterclockwise
void order( route *R) {

 point aux = (*R)[0];

 uint n=R->size();
 for( uint i=0; i<n; i++) {
  (*R)[i]-=aux;
 }

 std::sort(R->begin()+1, R->end(), operator<);

 for( uint i=0; i<n; i++) {
  (*R)[i]+=aux;
 }
}


//! Cust of route
double cust_route(route X) {

 double aux=0;
 uint n=X.size();
 for( uint i=0; i<n-1; i++) 
  aux+=std::abs(X[i]-X[i+1]);
 aux+=std::abs(X[n]-X[0]);

 return aux;
}

// Troca dois elementos de posição numa rota
void swap( route::iterator x, route::iterator y) {
 point s=*x;
 *x=*y;
 *y=s;
}

// Verifica se duas arestas ( aresta:=par de vertices ordenados) estão se cruzando
bool cross( point xi, point xf, point yi, point yf) {
 if( std::abs(xf-xi)+std::abs(yf-yi) >= std::abs(yi-xi)+std::abs(yf-xf)) return true;
 else return false;
}

// Inverte a ordem dos elementos entre os interadores
void rotate( route::iterator x, route::iterator y) {
 for( route::iterator i=x, j=y; i!=j && i-1!=j; i++, j--)
  swap(i,j);
}

void print_route( route R) {

 uint n=R.size();
 for( uint i=0; i<n; i++)
  std::cout << R[i] << " ";
 std::cout << std::endl;

}

#endif
