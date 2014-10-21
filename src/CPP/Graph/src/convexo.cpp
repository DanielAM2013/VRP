#include "../lib/grafo.hpp"

int Teste=200;

double sign( point A, point B) {
 return (A.real()*B.imag()-A.imag()*B.real());
}

bool In( vector<point> V, point X) {

 for( num k=0; k<V.size()-1; k++) {
  if( sign(V[k+1]-V[k], X-V[k]) > 0) {
   return false;
  }
 }

 if(sign( V[0]-V[V.size()-1], X-V[V.size()-1]) > 0) return false;

 return true;
}


num positive( vector<point> V, point X) {
 num P=0;

 for( num k=1; k<V.size()-1; k++)
  if( sign(V[k]-V[k-1], X-V[k-1]) <0 & sign(V[k+1]-V[k], X-V[k])>=0)
   P=k;

 if( sign(V[V.size()-1]-V[V.size()-2], X-V[V.size()-2]) <0 & sign( V[0]-V[V.size()-1],
X-V[V.size()-1])>= 0)
  P=V.size()-1;
 
 return P;
}

num negative( vector<point> V, point X) {
 num P=0;
 for( num k=1; k<V.size()-1; k++) {
//  cout << sign(V[k]-V[k-1], X-V[k-1]) << " " <<  sign(V[k+1]-V[k], X-V[k]) << endl;
  if( sign(V[k]-V[k-1], X-V[k-1]) > 0 & sign(V[k+1]-V[k], X-V[k]) <= 0) {
   P=k;
  }
 }
// cout << sign(V[V.size()-1]-V[V.size()-2], X-V[V.size()-2]) << " " << sign( V[0]-V[V.size()-1],
//X-V[V.size()-1]) << endl;

 if( sign(V[V.size()-1]-V[V.size()-2], X-V[V.size()-2]) >0 & sign( V[0]-V[V.size()-1],
X-V[V.size()-1]) <= 0) {
  P=V.size()-1;
 }
 return P;
}


void apagar( vector<point>& V,  num P, num N) {
 if( N==P+1) return;
 if( N>=V.size()) return;
 
 if( P+1<N ) {
  // caso 1: k<t
  V.erase(V.begin()+P+1, V.begin()+N);
 }
 else {
  V.erase(V.begin()+P+1, V.end());
  V.erase(V.begin(), V.begin()+N);
 }
}


// Dado um conjunto de pontos "points.dat" determinar quais pontos pertencem ao bordo convexo
vector<point> bordo_convexo( vector<point> X ) {
 // Tomar três pontos quaisquer do conjunto
 // Aplicar analisar o sinal do produto vetorial da diferença do primeiro para o segundo e do
 // primenrio pra o terceiro
 vector<point> fecho;
 vector<point> AUX(X);

 fecho.push_back(AUX[0]);
 fecho.push_back(AUX[1]);

 AUX.erase(AUX.begin(), AUX.begin()+2);

 // Passo inicial
 for( num k=2; k<AUX.size(); k++)
  if( sign(AUX[k]-fecho[0],fecho[1]-fecho[0]) >0) {
   fecho.push_back(AUX[k]);
   AUX.erase(AUX.begin()+k);
  break;
 }

 // Passo indutivo
 for( num k=2; k<Teste; k++) {
   // Determinar o ponto tangente positivo
   if( In(fecho, AUX[k])) continue;
   num v=positive( fecho, AUX[k]), w=negative( fecho, AUX[k]);
   apagar(fecho, v, w);
   if( w>v) {
//    cout << "-" << v << " " << w << endl;
    fecho.insert(fecho.begin()+v+1, AUX[k]);
   }
   else {
//    cout << "+" << v << " " << w << endl;
    fecho.insert(fecho.begin(), AUX[k]);
   }
  }

 return fecho;
}

int main()
{
 char file[]="points.dat";
 vector<point> X=read(file);
 vector<point> Aux=bordo_convexo(X);

 cout << "-----" << endl;


 for( num k=0; k<Aux.size(); k++)
  cout << Aux[k];
 cout << endl;
 Aux.insert(Aux.end(), Aux[0]);

// cout << In( Aux, X[16]) << X[16] << endl; 

// num v=positive( Aux, X[16]), w=negative( Aux, X[16]);
// apagar( Aux, v, w);
 
// Aux.insert(Aux.begin()+v+1, X[16]);

// for( num k=0; k<Aux.size(); k++)
//  cout << Aux[k];
// cout << endl;

 char out[]="output.dat";
 write(Aux,out);



// cout << negative( Aux, X[4]) << " " << positive( Aux, X[4]) << " " << X[4] << endl;
// cout << sign(Aux[Aux.size()-1]-Aux[Aux.size()-2], X[4]-Aux[Aux.size()-2]) << endl;
// cout << sign( Aux[0]-Aux[Aux.size()-1], X[4]-Aux[Aux.size()-1]) << endl;

// cout << In(Aux, X[4]) << endl;

 return 0;
}
