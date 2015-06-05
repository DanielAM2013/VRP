#include "../lib/k-opt.hpp"

/*
 Basicamente o algoritmo utiliza a mesma ideia do 2-opt, rodar a ordem original entre os indixes
fixados. O problema principal é fazer com que a lista seja virtualmente circular.

*/

int main()
{
 char in[]="points.dat";  
 route r=read_route(in);
 // opt3:
 for( route::iterator i=r.begin(); next(i,4)!=r.end(); i++) {
  route::iterator aux[3];
  aux[0]=next(i);
  for( route::iterator j=next(aux[0]); next(j,2)!=r.end(); j++) {
   aux[1]=next(j);
   for( route::iterator k=next(aux[1]); next(k)!=r.end(); k++) {
    aux[2]=next(k);
    // Verificar todas as três possibilidades;
    if( cross( i, aux[0], j, aux[1]))
     rotate(aux[0],j);
    if( cross( j, aux[1], k, aux[2]))
     rotare( aux[1], k);
   }

  }
 }
 char out[]="route.dat";
 save_route(r);

 return 0;
}
