#ifndef _KOPT_
#define _KOPT_

#include <route.hpp>

// Retira os cruzamentos de primeira ordem
double opt2( route *R) {

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
 return cust_route(*R);
}

std::vector<route> genetic_opt2( route* R) {

	//! initialization
	uint n=R->size();
	std::vector<route> Aux;
	for ( uint i=0; i<n; i++) {
		Aux.push_back(*R);
		swap(Aux[i].begin(),Aux[i].begin()+i);
		opt2(&Aux[i]);
	}

	//! selection
	for ( uint i=0; i<n; i++) 
		std::cout << cust_route(Aux[i]) << std::endl;
	return Aux;
}

route simple_step( route R) {

	uint n=R.size();
	route S(R);
	route Aux[n];
	double d[3];
	d[0]=d[1]=cust_route(S);
	for ( uint i=1; i<n; i++) {
		Aux[i]=route(S);
		swap(Aux[i].begin(),Aux[i].begin()+i);
		d[2]=cust_route(Aux[i]);
		if ( d[2] < d[1] ) {
			d[1]=d[2];
			S=Aux[i];
		}
	}
	return S;
}



#endif
