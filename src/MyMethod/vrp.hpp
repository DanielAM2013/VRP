#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <algorithm>

typedef std::complex<double> point;
typedef std::vector<point> route;
typedef std::vector<route> train;
typedef std::vector<double> list;

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
/*
 for( int i=0; i<X.size(); i++) 
  aux+=cust_route(X[i]); 
 return aux;
*/

 double k=3;
 for( int i=0; i<X.size(); i++) 
  aux+=pow(cust_route(X[i]),k); 

 return pow(aux,1/k);

/*
 double d[2]={0,cust_route(X[0])};
 for( int i=1; i<X.size(); i++) {
  d[0]=cust_route(X[i]);

//  std::cout << d[0] << std::endl;
  if(d[0]>d[1]) {
   d[1]=d[0];
  }
 }
// std::cout << d[1] << std::endl;
 aux=pow(pow(aux,2)+pow(d[1],2),0.5);
*/
}

