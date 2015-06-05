#ifndef __CONVEXO__
#define __CONVEXO__

#include <route.hpp>

double sign( point A, point B) {
 return (A.real()*B.imag()-A.imag()*B.real());
}

bool In ( route V, point X) {

 uint n=V.size();
 for ( uint k=0; k<n-1; k++)
  if ( sign(V[k+1]-V[k], X-V[k]) > 0)
   return false;

 if(sign( V[0]-V[n-1], X-V[n-1]) > 0)
   return false;

 return true;
}

uint positive( route V, point X) {

 uint n=V.size();
 uint P=0;

 for( uint k=1; k<n-1; k++)
  if( sign(V[k]-V[k-1], X-V[k-1]) <0 &&
      sign(V[k+1]-V[k], X-V[k])>=0)
   P=k;

 if( sign(V[n-1]-V[n-2], X-V[n-2]) < 0 && 
     sign( V[0]-V[n-1], X-V[n-1])>= 0)
  P=n-1;
 
 return P;
}

uint negative( route V, point X) {

 uint n=V.size();
 uint P=0;

 for( uint k=1; k<V.size()-1; k++) 
  if( sign(V[k]-V[k-1], X-V[k-1]) > 0 && sign(V[k+1]-V[k], X-V[k]) <= 0)
   P=k;
  
 if( sign(V[n-1]-V[n-2], X-V[n-2]) >0 & sign( V[0]-V[n-1], X-V[n-1]) <= 0)
  P=n-1;

 return P;
}

void apagar( route& V, uint P, uint N) {

 if( N==P+1) return;
 if( N>=V.size()) return;
 
 if( P+1<N ) {
  V.erase(V.begin()+P+1, V.begin()+N);
 }
 else {
  V.erase(V.begin()+P+1, V.end());
  V.erase(V.begin(), V.begin()+N);
 }
}

route bordo_convexo( route X ) {

 route fecho;
 route AUX(X);

 fecho.push_back(AUX[0]);
 fecho.push_back(AUX[1]);

 AUX.erase(AUX.begin(), AUX.begin()+2);

 for( uint k=2; k<AUX.size(); k++)
  if( sign(AUX[k]-fecho[0],fecho[1]-fecho[0]) >0) {
   fecho.push_back(AUX[k]);
   AUX.erase(AUX.begin()+k);
   break;
  }

 for( uint k=2; k<AUX.size(); k++) {
   if( In(fecho, AUX[k])) continue;
   uint v=positive( fecho, AUX[k]), w=negative( fecho, AUX[k]);
   apagar(fecho, v, w);
   if( w>v)
    fecho.insert(fecho.begin()+v+1, AUX[k]);
   else
    fecho.insert(fecho.begin(), AUX[k]);
  }

 return fecho;
}
#endif
