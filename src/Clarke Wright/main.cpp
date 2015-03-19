#include "../lib/train.cpp"

int main()
{
 char in[]="points.dat";
 route R = read_route(in);
// train T = route2train(R);
// train::iterator i=T.begin(), j=next(i);
 train T = cw(&R);
// std::cout << cust_train(T) << std::endl;
/*
 double dist[2];
 dist[1]=cust_train(T);
 train Aux[2];
 for ( int i=0; i<T.size()-1; i++) {
  Aux[0]=T;
  dist[0]=merge(next(Aux[0].begin(),i), next(Aux[0].begin(),i+1), Aux[0]);
  if( dist[0]<dist[1]) {
   dist[0]=dist[1];
   Aux[1]=Aux[0];
  }
 }
*/

// print(T); 
 save_train(T);
 return 0;
}
