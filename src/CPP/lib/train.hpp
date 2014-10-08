#include "route.hpp"
#include <sstream>

train::iterator next( train::iterator i, int k=1) {
 
// for ( int i=0; i<k; i++) {
//  i++;

 return ++i;
}

train::iterator prev( train::iterator i) {
 return --i;
}
// Custo da frota
double cust_train( train X, double k=1) {
 double aux=0;

 for( train::iterator i=X.begin(); i!=X.end(); i++) 
  aux+=pow(cust_route(*i),k); 

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

// Converte uma lista de pontos (route) em uma lista de rotas (train)
train route2train( route R) {

 train Aux;
 for( route::iterator i=R.begin(); i!=R.end(); i++) {
  route aux;
  aux.push_back(*i);
  Aux.push_back(aux);
 }

 return Aux;
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






