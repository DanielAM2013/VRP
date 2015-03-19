#ifndef _KOPT_
#define _KOPT_

#include "route.hpp"

// Retira os cruzamentos de primeira ordem
void opt2( route *R) {

 //! Tomar dois pares de pontos dijuntos
 route::iterator aux[2];
 for( route::iterator i=R->begin(); next(i,2)!=R->end(); i++) {
  aux[0]=next(i);
  for( route::iterator j=next(aux[0]); next(j)!=R->end(); j++) {
   aux[1]=next(j);
  //! verificar se a cruzamento de rotas
  if( cross(*i, *aux[0], *j, *aux[1]))
   rotate( aux[0], j);
  }
  if(i==R->begin()) continue;

  //! executar para o último elemento 
  route::iterator j=prev(R->end());
  aux[1]=R->begin();

  //! verificar se a cruzamento de rotas
  if( cross(*i,*aux[0],*j,*aux[1]))
   rotate( aux[0], j);
 }
}

#endif
