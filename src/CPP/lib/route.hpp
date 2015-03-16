#include "base.hpp"

// Avança "n" posições numa lista encadeada
route::iterator next( route::iterator i, int n=1) {

 route::iterator aux=i;
 for ( int k=0; k<n; k++) 
  aux++;

 return aux;
}

// Recua "n" (default 1) numa lista duplamente encadeada
route::iterator prev( route::iterator i, int n=1) {

 route::iterator aux=i;
 for( int k=0; k<n; k++) 
  aux--;

 return aux;
}

// Lê uma rota: arquivo com uma lista de par de double ordenados
route read (char file[]) {

 std::ifstream data(file, std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 return first;
}

// Salva uma rota: arquivo com uma lista de par de double ordenados
void save_route(route* R, char name_file[])
{

 std::ofstream out(name_file);

 for( route::iterator x=R->begin(); x!=R->end(); x++) {
  out << x->real() << " " << x->imag() << std::endl;
 }
}

// Ordenação parcial do plano
bool operator<(std::complex<double> X, std::complex<double> Y) {
 if(std::arg(X)<std::arg(Y)) return true;
 if(std::arg(X)==std::arg(Y) & std::abs(X) < std::abs(Y)) return true;
 return false;
}

// Ordenar pontos da rota
void order( route *R) {

 point aux = *(R->begin());

 for( route::iterator i=R->begin(); i!=R->end(); i++) {
  *i-=aux;
 }

 std::sort(next(R->begin()), R->end(), operator<);

 for( route::iterator i=R->begin(); i!=R->end(); i++) {
  *i+=aux;
 }
}


// Custo da rota
double cust_route(route X) {
 double aux=0;

 for( route::iterator i=X.begin(); next(i)!=X.end(); i++) 
  aux+=std::abs(*i-*next(i));

 aux+=std::abs(*prev(X.end())-*X.begin());

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

 for( route::iterator i=x, j=y; i!=j & prev(i)!=j; i++, j--)
  swap(i,j);
}

void print_route( route R) {

 for( route::iterator i=R.begin(); i!=R.end(); i++)
  std::cout << *i << " ";

 std::cout << std::endl;

}




