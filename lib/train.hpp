#ifndef __TRAIN__
#define __TRAIN__

#include <route.hpp>

typedef std::vector<route> train;

#include <sstream>

train::iterator next( train::iterator i, int n=1) {

 train::iterator aux=i; 
 for ( int k=0; k<n; k++)
  aux++;

 return aux;
}

train::iterator prev( train::iterator i) {
 return --i;
}

void save_train( train T, char* filename) {
 unsigned int k=0;
 std::stringstream s;
 s << filename;
 std::ofstream  out(s.str().c_str());

 for( train::iterator i=T.begin(); i!=T.end(); i++) {

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;

  out << (i->begin())->real() << " " << (i->begin())->imag() <<  std::endl
	  << std::endl;
 }
 out.close();
}


void print_train(train T) 
{
 std::cout << "---------------------------------------" << std::endl;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}


// Converte uma lista de pontos (route) em uma lista de rotas (train)
train route2train( route R) {

 train Aux;
 point origin=*R.begin();
 for( route::iterator i=R.begin()+1; i!=R.end(); i++) {
  route aux;
  aux.push_back(origin);
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
#endif
