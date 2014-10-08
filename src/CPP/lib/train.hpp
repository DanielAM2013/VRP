#include "route.hpp"
#include <sstream>




// Custo da frota
double cust_train( train X, double k=1) {
 double aux=0;

 for( int i=0; i<X.size(); i++) 
  aux+=pow(cust_route(X[i]),k); 

 return aux;
}

void print( train T) 
{
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}
/*
void read_train( train *T) {

 int k=0;
 for (;;) {
  std::stringstrem s;
  s << k << ".points";
  T->push_back(read_route(s));
  k++;
 }

}
*/
// Salva train: conjunto de arquivos numerados com listas de pares de doubles
void save_train( train T) {
 unsigned int k=0;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  std::stringstream s;
  s << k << ".test";
  std::ofstream  out(s.str().c_str());

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;
  out.close();
  k++;
 }
}






