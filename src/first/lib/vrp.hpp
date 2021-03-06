#include "base.hpp"

bool operator<(std::complex<double> X, std::complex<double> Y) {
 if(std::arg(X)<std::arg(Y)) return true;
 if(std::arg(X)==std::arg(Y) & std::abs(X) < std::abs(Y)) return true;
 return false;
}

double cust_route(route X) {
 double aux=0;
 for( int i=0; i<X.size()-1; i++) 
  aux+=std::abs(X[i]-X[i+1]);
 aux+=std::abs(X[X.size()-1]-X[0]);

 return aux;
}

double cust( train X) {
 double aux=0;

 double k=2;
 for( int i=0; i<X.size(); i++) 
  aux+=pow(cust_route(X[i]),k); 

 return pow(aux,1/k);

}

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
