#include "base.hpp"

int main()
{
// Estrutura List
 Route route;
// Ler ponto de um arquivo

 std::ifstream ifs ("points.dat", std::ifstream::in);

 point aux(0,0);

 while (ifs >> aux.real() >> aux.imag()) { 
  route.push_back(aux);
 }

 ifs.close();

// List teste

// Algoritmo
// Step 1: Calcular as poupanças sij=ci0+c0j-cij para i,j=1,...mn i!=j. Criar n rotas de veículos
// (0,i,0) para i=1,...,n. Ordenar as economias num modo não crescente.
 int n=route.size();
 double s[n][n-1];
 point origin=*route.begin();
 Route Aux;
 Subroute Sb; 

 for (Route::iterator i=++route.begin(); i!=route.end(); ++i) {
  Aux.push_back(*i);
  Sb.push_back(Aux);
  for ( Route::iterator j=i; j!=route.end(); ++j) {
   if( i!=j) {
     s[i][j]( std::abs(*i-origin)+std::abs(origin-*j)-std::abs(*i-*j) );
   }
  }
  Aux.clear();
 }

 std::cout << Sb.size() << std::endl;

 s.sort();

 for (std::list<double>::iterator i=s.begin(); i!=s.end(); ++i) 
	std::cout << *i << std::endl;

// Step 2: Iniciar do topo da lista de economias, executando o seguinte. Dada a economia sij,
// determine se há duas rotas, uma contendo arco ou aresta (0,j) e a outra contendo o arco ou aresta
// (i,0), que pode ser mescladas. Se então, combine essas duas rotas deletando (0,j) e (i,0) e
// introduzindo (i,j).

 
 // Mesclar rotas
 for(Subroute::iterator I=Sb.end(); I!=Sb.begin(); --I) {
  
 }

 return 0;
}
