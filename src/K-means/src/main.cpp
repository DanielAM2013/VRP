#include <route.hpp>
#include <convexo.hpp>
#include <cstdlib>
#include <limits>

typedef std::complex<double> point;
typedef std::vector<point> means;
typedef std::vector<means> cluster;

point center( const means& M) {
 point aux(0,0);
 for ( int i=0; i<M.size(); i++)
  aux+=M[i];
 
 return aux/((double) M.size());
}

double cust_means( const means& M, double (*DIST) ( point A, point B)) {

 point C(0,0);
 for ( int i=0; i<M.size(); i++)
  C+=M[i];
 C/=M.size();

 double aux=0;
 for ( int i=0; i<M.size(); i++) {
  aux+=(*DIST)(M[i],C);
 }

 return aux;
}

double dist( point A, point B) {
 return pow(std::abs(std::arg(A/B)),1);
}

double Inf=std::numeric_limits<double>::infinity();

cluster kmeans( means ALL, int k, double (*DIST)( point , point ) ) {

 int n=ALL.size();

 point centers[k];

 for ( int i=0; i<k; i++) {
  centers[i]=ALL[i*n/k+rand()%(n/k)];  
 }

 int Classes[n];
 double sum=Inf;
 double err=1;
 int size[k];
 double Cust[k];
 double CUST;

 cluster C(k);

 while ( err>1e-10) {

  for ( int i=0; i<k; i++) {
   Cust[i]=0;
   size[i]=0;
  }

  for ( int j=0; j<n; j++) {
   
   double d[2]={(*DIST)(ALL[j],centers[0]),0};
   Classes[j]=0;

   for ( int i=1; i<k; i++) {
    d[1]=(*DIST)(ALL[j],centers[i]);
    if ( d[1] < d[0] ) {
     d[0]=d[1];
     Classes[j]=i;
    }
   }
   size[Classes[j]]++;
   Cust[Classes[j]]+=d[1];
  }

  
  for ( int i=0; i<k; i++) 
   centers[i]=point(0,0);

  for ( int j=0; j<n; j++) {
   centers[Classes[j]]+=ALL[j];
  }

  CUST=0;
  for ( int i=0; i<k; i++) {
   CUST+=Cust[i];
   if ( size[i]!=0 )
    centers[i]/=size[i];
  }

  err = sum - CUST;
  sum=CUST;
 }

 for ( int j=0; j<n; j++)
  C[Classes[j]].push_back(ALL[j]);

 return C;
}

int main(int argc, char** argv) {

 std::ifstream input( argv[1], std::ios::in);

 int k=5;
 point aux;
 means ALL;

 while( input >> aux.real() >> aux.imag() ) {
  ALL.push_back(aux);  
 }

 order(&ALL);

 cluster Test=kmeans(ALL, k, dist);

 for ( int i=0; i<k; i++) {
  char output[17];
  int k=sprintf(output, "out/output%d.dat",i);
  std::ofstream out( output, std::ios::out);
  for ( int j=0; j<Test[i].size(); j++)
    out << Test[i][j].real() << " " << Test[i][j].imag() << std::endl;
  out.close();
 }

  std::ofstream out( "out/output.dat", std::ios::out);
 for ( int i=0; i<k; i++) {
  out << center(Test[i]).real() << " " << center(Test[i]).imag() << std::endl;
  out << 0 << " " << 0 << std::endl;
 }
 out.close();

 for ( int i=0; i<k; i++)
  std::cout << Test[i].size()  << " " << cust_means(Test[i],dist) << std::endl;

 cluster convexo(k);
 for ( int i=0; i<k; i++)
  convexo[i]=bordo_convexo(Test[i]);

 for ( int i=0; i<k; i++) {
  char output[18];
  int k=sprintf(output, "out/convexo%d.dat",i);
  std::ofstream out( output, std::ios::out);
  for ( int j=0; j<convexo[i].size(); j++)
    out << convexo[i][j].real() << " " << convexo[i][j].imag() << std::endl;
  out << convexo[i][0].real() << " " << convexo[i][0].imag() << std::endl;
  out.close();
 }

 for ( int i=0; i<k; i++)
  std::cout << convexo[i].size() << std::endl;

 std::cout << Test[2][3] << std::endl;

 return 0;
}
