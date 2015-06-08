#ifndef _KOPT_
#define _KOPT_

#include <train.hpp>

// Retira os cruzamentos de primeira ordem
double opt2( route *R) {

 //! Tomar dois pares de pontos dijuntos
 route::iterator aux[2];
 for( route::iterator i=R->begin(); i+2!=R->end(); i++) {
  aux[0]=i+1;
  for( route::iterator j=aux[0]+1; j+1!=R->end(); j++) {
   aux[1]=j+1;
  //! verificar se a cruzamento de rotas
  if( cross(*i, *aux[0], *j, *aux[1]))
   rotate( aux[0], j);
  }
  if(i==R->begin()) continue;

  //! executar para o último elemento 
  route::iterator j=R->end()-1;
  aux[1]=R->begin();

  //! verificar se a cruzamento de rotas
  if( cross(*i,*aux[0],*j,*aux[1]))
   rotate( aux[0], j);
 }
 return cust_route(*R);
}

route genetic_opt2( route R) {


	double d[2]={0,cust_route(R)};
	//! initialization
	uint n=R.size();
	route Aux, Aux1(R);

	for ( uint j=0; j<n-1; j++) {
		for ( uint i=j+1; i<n; i++) {
			Aux=route(Aux1);
			swap(Aux.begin()+j,Aux.begin()+i);
			d[0]=cust_route(Aux);
			if (d[0] < d[1]) {
			 d[1]=d[0];
			 Aux1=route(Aux);
			}
		}
	}
	}
	return Aux1;
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
