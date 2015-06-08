#include <base.hcl>

double int_product ( point A, point B ) {
 return (A.s0*B.s1+A.s1*B.s0);
}
double ext_product ( point A, point B ) {
 return (A.s0*B.s0-A.s1*B.s1 );
}

__kernel
void balance (
	global TYPE_IN_USE* test,
	global TYPE_IN_USE* mean,
	global TYPE_IN_USE* result,
	global uint* N,
	global int* index
)
{
 int gid = get_global_id(0);
 double sum, aux=0;
 int j=gid, i=j;

 sum=test[j];
 while ( sum+aux < *mean) {
  sum+=aux;
  if ( j >= *N ) {
   j-=*N;
  }
  i=j;
  j++;
  aux=test[j];
 }
 result[gid]=sum;
 index[gid]=i;
}
