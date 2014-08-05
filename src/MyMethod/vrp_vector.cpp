#include "vrp.hpp"

int main()
{
// Ler Arquivo
 std::ifstream data("points.dat", std::ifstream::in);
 
 route first;
 point aux;

// data >> aux.real() >> aux.imag();
 data >> std::double >> aux.real();




/*
 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 int N=first.size();


// Ordenar
 std::sort( first.begin(), first.end(), operator<);
// Alocar
 train second;
 for( int i=0; i<N; i++) {
  route aux;
  aux.push_back(first[i]);
  second.push_back(aux);
  aux.clear();
 }

 std::cout << cust(second);
*/






























 return 0;
}
