#include <base.hcl>

double ext_product( const point A, const point B){
 return (A.s0*B.s1-A.s1*B.s0);
}

double int_product( const point A, const point B) {
 return (A.s0*B.s0+A.s1*B.s1);
}

double module ( const point A) {
 return sqrt(A.s0*A.s0+A.s1*A.s1);
}

__kernel
void mean ( global point* P, global point* M, global uint* B, global uint* N)
{
 int gid=get_global_id(0);
  point aux[3];
  double test[2];

  aux[0]=P[gid]-*M;

  test[1]=0;
  int i;
  i=0;
  while( i<*N) {
   if ( i==gid) {
    i++;
	continue;
   }
   aux[1]=P[i]-P[gid];
   test[0]=ext_product(aux[0],aux[1]);
   if( test[1] < test[0]) {
    test[1]=test[0];
    B[gid]=i;
   }
   i++;
  }
}
