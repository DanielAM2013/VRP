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
 aux+=std::abs(*X.end()-*X.begin());

 return aux;
}

double cust( train X) {
 double aux=0;
 for( int i=0; i<X.size()-1; i++) 
  aux+=cust_route(X[i]); 

 return aux;
}

