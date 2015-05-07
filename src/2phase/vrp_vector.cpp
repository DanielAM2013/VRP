#include "../lib/base.hpp"

int
main ( int argc, char* argc[])
{
// Ler Arquivo
 std::ifstream data("points.dat", std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 int n=first.size();

// Calcular sij
 point origin=first[0];
 std::vector< std::vector<double> > s;

 // Retornar posição do maior sij
 for( int i=1; i<n-1; i++) {
  std::vector< double> Aux;  
  for( int j=i+1; j<n; j++) {
   Aux.push_back(std::abs(first[i]-origin)+std::abs(origin-first[j])-std::abs(first[i]-first[j]));
  }
  s.push_back(Aux);
 }

 std::vector<std::vector<double>::iterator> Aux; 
 Aux.clear();

 for(int i=0; i<n-2; i++) {
  Aux.push_back(std::max_element(s[i].begin(),s[i].end()));
 }
 std::vector<double>::iterator Max=std::max_element(Aux[0],Aux[n-3]);

 int k, t;
 for( int i=0; i<n-2; i++) {
  for( int j=0; j<n-2-i; j++) {
   if(s[i][j]=*Max){ k=i; t=j;}
  }
 }

 std::cout << s[k][t] << std::endl;

 subroute secund;

 route Auxiliar;
 Auxiliar.push_back(origin);
 Auxiliar.push_back(first[k]);
 Auxiliar.push_back(first[t]);
 Auxiliar.push_back(origin);

 secund.push_back(Auxiliar);




 













 return 0;
}
