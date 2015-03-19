//#include "../lib/basic.hpp"
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned num;

template< class A>
void print( A x) {
 cout << x;
}

template< class B>
void print( vector<B> X) {
 for( num k=0; k<X.size(); k++) {
  cout << " ";
  print<B>(X[k]);
 }
 cout << endl;
}

int main()
{
 vector<double> X;
 for( num k=0; k<10; k++)
  X.push_back(k+0.1);

 print<double >( X);

// std::cout << std::min(3,4);

 return 0;
}
