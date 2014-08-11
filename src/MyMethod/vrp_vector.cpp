#include "vrp.hpp"

route read_file(char file[]) {

 std::ifstream data(file, std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 return first;
}

int main()
{
// Ler Arquivo
 char test[]="points.dat";

 route first=read_file(test); 
 std::cout << first.size() << std::endl;

/*
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
