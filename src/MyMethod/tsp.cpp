#include "vrp.hpp"
//#include <tuple>


//std::tuple<double, route::iterator> 
double closer(point P, route R, int& aux)
{
 double d[2];
 d[1]=1e+32;
// int aux;

 int i;
 for( i=0; i<R.size()-1; i++) {
  d[0]=std::abs(P-R[i])+std::abs(P-R[i+1])-std::abs(R[i]-R[i+1]);
  if(d[0]<d[1]) {
   d[1]=d[0];
   aux=i;
  }
 }
 d[0]=std::abs(P-R[R.size()-1])+std::abs(P-R[0])-std::abs(R[R.size()-1]-R[0]);
 if(d[0]<d[1]) {
  d[1]=d[0];
  aux=R.size()-1;
 }

 return d[1];

};

double closer(route P, route R, int& aux, int &pos) {

 double d[2];

 for( int i=0; i<R.size(); i++) {
  d[0]=closer(P[i], R, aux);
  if(d[0]<d[1]) {
   d[1]=d[0];
   pos=i;
  }
 }

 return d[1];
}


double tsp(route R, route& aux) 
{
 route Aux=R;

 *aux.begin()=*R.begin();

 int pos[2];
 double dist;

 dist=closer(R, aux, pos[0], pos[1]);

 aux.push_back(R[pos[1]]);
  


}




int main()
{

 std::ifstream data("points.dat", std::ifstream::in);
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 

 point X(-0.001,0.999);
 double dist;
 int x;


// std::sort (first.begin(), first.end(), operator<);

// for ( int i = 0; i < first.size(); i++) std::cout << first[i] << std::endl;



 route test;
 test.push_back(first[0]);
 test.push_back(first[1]);
 test.push_back(first[2]);

 for ( int i = 0; i < test.size(); i++) std::cout << test[i] << std::endl;

 dist= closer(X, test, x);
 std::cout << dist << test[x] << X << std::endl;

 









 return 0;
}
