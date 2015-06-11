#ifndef __CONVEXO__
#define __CONVEXO__

#include <route.hpp>

//! this function return cross product to vectors A and B
//! which is the area of retangle gerate for deslocation A along of B signalized:
//! positive if A is counterclockwise B, and negative otherwise
//! cust: O(1)
double sign( point A, point B) {
 return (A.real()*B.imag()-A.imag()*B.real());
}


//! this function return true if X is inside of V concex
//! cust: O(size(V))
bool In ( route V, point X) {

 uint n=V.size();

 for ( uint k=0; k<n-1; k++)
  if ( sign(V[k+1]-V[k], X-V[k]) > 0)
   return false;

 if(sign( V[0]-V[n-1], X-V[n-1]) > 0)
   return false;

 return true;
}

//! 
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

 for( uint k=1; k<n-1; k++) 
  if( sign(V[k]-V[k-1], X-V[k-1]) >= 0 && sign(V[k+1]-V[k], X-V[k]) < 0)
   P=k;
  
 if( sign(V[n-1]-V[n-2], X-V[n-2]) >= 0 && sign( V[0]-V[n-1], X-V[n-1]) < 0)
  P=n-1;

 return P;
}

void apagar( route& V, uint P, uint N) {

 if( N==P+1) return;

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

 //! this get two first points
 fecho.push_back(AUX[0]);
 fecho.push_back(AUX[1]);

 //! this erase two first points
 AUX.erase(AUX.begin(), AUX.begin()+2);


 //! add point if that is in out of convex
 for( uint k=0; k<AUX.size(); k++)
  if( sign(AUX[k]-fecho[0],fecho[1]-fecho[0])>0 ) {
   fecho.push_back(AUX[k]);
   break;
  }

 //! add points if that is out of convex
 for( uint k=0; k<AUX.size(); k++) {
   //! check if point k is inside of convex
   if( In(fecho, AUX[k])) continue;
   //! this get the index v of last point from left and 
   //! firt point from right to edge
   uint v=positive( fecho, AUX[k]), w=negative( fecho, AUX[k]);

   //! erase point between points v and w
   apagar(fecho, v, w);

   //! add out point at v+1 position 
   if( w>v )
    fecho.insert(fecho.begin()+v+1, AUX[k]);
   else
    fecho.insert(fecho.begin(), AUX[k]);
  }

 return fecho;
}
#endif
