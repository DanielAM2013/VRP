#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <limits>

typedef std::complex<double> point;
typedef std::vector<point> means;
typedef std::vector<means> cluster;

double cust_means( const means& M, const point& C) {

 double aux=0;
 for ( int i=0; i<M.size(); i++) {
  aux+=pow(std::abs(M[i]-C),2);
 }

 return aux;
}


double Inf=std::numeric_limits<double>::infinity();
int k=5;

int main(int argc, char** argv) {

 std::ifstream input( argv[1], std::ios::in);

 point aux;
 means ALL;

 while( input >> aux.real() >> aux.imag() ) {
  ALL.push_back(aux);  
 }

 int n=ALL.size();

 int initial[5]={204,71,75,359,234};

 point centers[k];

 for ( int i=0; i<k; i++)
  centers[i]=ALL[initial[i]];  

 int Classes[n];
 double sum=Inf;
 double err=1;
 while ( err>1e-4) {

  double Cust[k];
  int size[k];

  for ( int i=0; i<k; i++) {
   Cust[i]=0;
   size[i]=0;
  }

  for ( int j=0; j<n; j++) {
   
   double d[2]={pow(std::abs(ALL[j]-centers[0]),2),0};
   Classes[j]=0;

   for ( int i=1; i<k; i++) {
    d[1]=pow(std::abs(ALL[j]-centers[i]),2);
    if ( d[1] < d[0] ) {
     d[0]=d[1];
     Classes[j]=i;
     Cust[i]+=d[1];
     size[i]++;
    }
   }
  }

  double CUST=0;

  for ( int i=0; i<k; i++) {
   CUST+=Cust[i];
   if ( size[i]!=0 )
    centers[i]/=size[i];
  }

  err /= sum - CUST;
  sum=CUST;
 }


 for ( int i=0; i<n; i++)
  std::cout << ALL[i] << " " << Classes[i] << std::endl;



 for ( int i=0; i<k; i++) {
  char output[15]=
  std::ofstream out( "out/output.dat", std::ios:out);
  out <<  
 }

 return 0;
}
