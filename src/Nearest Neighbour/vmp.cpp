#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <complex>
#include <algorithm>

#include <iterator>

using namespace std;

/*
 P: conjunto de pontos dados inicialmente
 A, B: Lista de pontos

 descrição:

 B<=P
 A recebe B(begin);
 remove-se B(begin) de B;
 para todo x em P;
 calcular distância x para A( dist(A,x));
 determinar a menor distância:=: dmin;
 tomar o ponto com dmin e acrescenta-lo a A;

 melhoramento:

 Podemos acrescentar mais de um ponto de cada vez.
 Tomando-se P com n pontos
 e um dado k<=n
 tomar dos primeiros k pontos um ponto x e aplicar o algoritmo para k-1 aos demais pontos.

 obs: quando k=n o algoritmo será a solução geral para o tsp.

// Outro método que se extendido pode resolver o Tsp, é o k-opt.

*/

typedef int unsigned num;
typedef std::complex<double> point;
double vmp( std::list<point> *A, std::list<point> *B, num k) {
 // A: conjunto fonte
 // B: conjunto souvedor

 if(k==1) {
  double d[3];
  d[2]=0;
  // simple step
  // for all "y" elements in (A-e)\cap B
  // calculate \Delta (x,y)=dist(x,y)+dist(x,y->next)-dist(y,y->next); 
  while( !A->empty() ) {
   d[1]=1e+30;
   std::list<point>::iterator closer;

   point p=*(A->begin());
   for( std::list<point>::iterator j=B->begin(); j!=B->end(); j++) {
 
    d[0]=std::abs(*j-p)+std::abs(p-*(++j))-std::abs(*j-*(++j));

    if(d[0]<d[1]) {
     d[1]=d[0];
     closer=j;
    }
   }

   d[0]=std::abs(*(B->end())-p)+std::abs(p-*B->begin())-std::abs(*(B->end())-*B->begin());

   if(d[0]<d[1]) {
    d[1]=d[0];
    closer=B->end();
   }

   d[2]+=d[1];

   B->insert(closer, p);
  
   A->pop_front();
  }
  return d[2];
 }
/*
 std::list<point> Aux[2];
 std::list<point>::iterator pos[2];

 for( std::list::point::iterator e=Aux[0].begin(); e!=Aux[0].end(); e++) {
  // copy first "k" elements from "A" to "Aux[0]" and remove it
  pos[0]=A->begin();
  for( int i=0; i<k; i++) {
   Aux[0].push_back(pos[0]);
   A->pop_front();
  }

  // copy "Aux[0]" elements less "e"
  pos[0]=Aux[0]->begin();
  for( int i=0; i<k-1; i++) {
   if(pos[0]==e) continue;
   Aux[1].push_back(pos[0]);
   pos[0]++;
  }

  // recursive step
  vmp(&Aux[1], B, k-1);
 }
*/
}


int main()
{
/*
 route A;

 for( int i=0; i<3; i++) {
  point aux(i,i+1);

  A.push_back(aux);

 }

 std::cout << tsp(&A) << std::endl;

 for( route::iterator i=A.begin(); i!=A.end(); i++) {
  std::cout << *i << " ";
 }
*/
 std::list<point> T, S;

 for( int i=0; i<3; i++) {
  point aux(i,i+1);
  T.push_back(aux);
 }

// std::cout << *(T.end()) << std::endl;
// std::cout << vmp(&T, &S, 1);
 point aux(101,102);
 T.insert(T.end(), aux);
 
// for( std::list<point>::iterator i=T.begin(); i!=T.end(); i++) {
//  std::cout << *i << "-" << *(std::next(i,1))<< " ";
// }

// std::cout << vmp(&T, &S, 1);
// point aux(1,2);
// T.insert(T.end(), aux);
 

 return 0;
}
