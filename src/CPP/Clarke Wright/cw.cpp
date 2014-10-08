#include "../lib/train.hpp"

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
 dist[1]=cust_train(Aux[2]);
 Aux[1]=train(Aux[2]);
 for( int k=0; k<R->size(); k++) {
  Aux[2]=train(Aux[1]);
  Aux[0]=train(Aux[2]);
  // Varrer todas as rotas de "T"
  for( train::iterator i=Aux[0].begin(); i!=Aux[0].end(); i++) {

   // Mesclar rota com sucessora
   for( route::iterator k=next(i)->begin(); k!=next(i)->end(); k++)
    i->push_back(*k);

   Aux[2].erase(next(i));

   // Avaliar custo total
   dist[0]=cust_train(Aux[0]);

   // Verificar se há melhoramento
   if( dist[0]<dist[1]) {
    dist[1]=dist[0];
    Aux[1]=train(Aux[0]);
   }

   Aux[0]=train(Aux[2]);
  }

  // Mesclar rota com sucessora
  for( route::iterator k=(Aux[0].begin())->begin(); k!=(Aux[0].begin())->end(); k++)
   (prev(Aux[0].end()))->push_back(*k);

  Aux[0].erase(Aux[0].begin());

  // Avaliar custo total
  dist[0]=cust_train(Aux[0]);

  // Verificar se há melhoramento
  if( dist[0]<dist[1]) {
   dist[1]=dist[0];
   Aux[1]=train(Aux[0]);
  }

  Aux[0]=train(Aux[2]);
 }

 return Aux[2];
}

int main()
{
 char in[]="points.dat";
 route R = read_route(in);
// train T = route2train(R);
/*
 train::iterator k=T.begin(), i=next(k);

 for( int t=0; t<10; t++) {
  for( route::iterator l=i->begin(); l!=i->end(); l++) {
   k->push_back(*l);
  }

  T.erase(i);
 }
 print(T);
*/
 train T = cw(&R);
 print( T); 




 return 0;
}
