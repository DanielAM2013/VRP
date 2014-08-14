#include "vrp.hpp"

double tsp(route *R) {
 double d[3];
 d[2]=0;

 route::iterator closer[2];

 for( route::iterator last=R->begin(); last+1!=R->end(); last++) {
  d[1]=1e+30;
  for( route::iterator i=last+1; i!=R->end(); i++) {
   for( route::iterator j=R->begin(); j!=last; j++) {

    d[0]=std::abs(*j-*i)+std::abs(*i-*(j+1))-std::abs(*j-*(j+1));
    if(d[0]<d[1]) {
     d[1]=d[0];
     closer[0]=i;
     closer[1]=j;
    }
   }

   d[0]=std::abs(*last-*i)+std::abs(*i-*R->begin())-std::abs(*last-*R->begin());
   if(d[0]<d[1]) {
    d[1]=d[0];
    closer[0]=i;
    closer[1]=last;
   }
  }

  d[2]+=d[1];

  point aux=*closer[0];
  R->erase(closer[0]);
  R->insert(closer[1]+1, aux);
 }
 return d[2];
}

int main()
{

 std::ifstream data("points.dat", std::ifstream::in);
 route Tsp;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  Tsp.push_back(aux);
 }

 std::cout << tsp(&Tsp) << std::endl;

 return 0;
}
