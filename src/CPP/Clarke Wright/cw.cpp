#include "../lib/train.hpp"

int N=2;

// Mesclar duas rotas indicadas
double merge( train::iterator i, train::iterator j, train &T) {

 for( route::iterator k=next(j->begin()); k!=j->end(); k++)
  i->push_back(*k);

 T.erase(j);

 return cust_train(T, N);
}

train cw( route *R)
{
 // Ordenar todos as rotas de "T" pelos pontos contidos
 // de modo que este fiquem adjacêntes
 order( R);

 // converter os pontos de "R" em rotas de "T"
 train Aux[3];
 Aux[2]= train(route2train(*R));

 double dist[2];
 // Varrer todas as rotas de T, e verificar se há melhoramento com mesclagem
 dist[1]=cust_train(Aux[2], N);
 Aux[1]=train(Aux[2]);
 int n=Aux[2].size()-1;
 for( int k=0; k<n; k++) {

  Aux[2]=Aux[0]=train(Aux[1]);
  // Varrer todas as rotas de "T"
  int m=Aux[2].size()-1;
  for( int i=0; i<m; i++) {

   dist[0]=merge(next(Aux[0].begin(),i), next(Aux[0].begin(),i+1), Aux[0]);

   // Verificar se há melhoramento
   if( dist[0]<dist[1]) {
    dist[1]=dist[0];
    Aux[1]=train(Aux[0]);
   }

   Aux[0]=train(Aux[2]);
  }

  dist[0]=merge(prev(Aux[0].end()), Aux[0].begin(), Aux[0]);

  // Verificar se há melhoramento
  if( dist[0]<dist[1]) {
   dist[1]=dist[0];
   Aux[1]=train(Aux[0]);
  }
 }
 Aux[2]=Aux[1];

 return Aux[2];
}

int main()
{
 char in[]="points.dat";
 route R = read_route(in);
// train T = route2train(R);
// train::iterator i=T.begin(), j=next(i);
 train T = cw(&R);
// std::cout << cust_train(T) << std::endl;
/*
 double dist[2];
 dist[1]=cust_train(T);
 train Aux[2];
 for ( int i=0; i<T.size()-1; i++) {
  Aux[0]=T;
  dist[0]=merge(next(Aux[0].begin(),i), next(Aux[0].begin(),i+1), Aux[0]);
  if( dist[0]<dist[1]) {
   dist[0]=dist[1];
   Aux[1]=Aux[0];
  }
 }
*/

// print(T); 
 save_train(T);
 return 0;
}
